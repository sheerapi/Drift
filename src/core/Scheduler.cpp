#include "core/Scheduler.h"
#include "utils/Time.h"

namespace Drift
{
	void Scheduler::AddInterval(const Task& task, long interval,
									TaskPriority priority)
	{
		std::lock_guard<std::mutex> lock(taskMutex);
		auto* taskList = ChooseTaskList(priority);
		auto stask = ScheduledTask();
		stask.Callback = task;
		stask.Interval = interval;
		stask.Remaining = interval;
		taskList->push_back(stask);

        if (taskList == &workerThreadTasks)
        {
            workerThread = std::thread(WorkerRun);
        }
	}

	void Scheduler::AddTimeout(const Task& task, long timeout,
							   TaskPriority priority)
	{
		std::lock_guard<std::mutex> lock(taskMutex);
		auto* taskList = ChooseTaskList(priority);
		auto stask = ScheduledTask();
		stask.Callback = task;
		stask.Remaining = timeout;
		taskList->push_back(stask);

		if (taskList == &workerThreadTasks)
		{
			workerThread = std::thread(WorkerRun);
		}
	}

	void Scheduler::AddCustomChecked(const Task& task, const TaskCheck& check,
									 TaskPriority priority)
	{
		std::lock_guard<std::mutex> lock(taskMutex);
		auto* taskList = ChooseTaskList(priority);
		auto stask = ScheduledTask();
		stask.Check = check;
		stask.Callback = task;
		stask.Remaining = LONG_MAX;
		stask.Interval = LONG_MAX;

		if (taskList == &workerThreadTasks)
		{
			workerThread = std::thread(WorkerRun);
		}
	}

	void Scheduler::Update()
	{
		std::lock_guard<std::mutex> lock(taskMutex);

		for (auto& task : mainTasks)
		{
			task.Remaining -= static_cast<long>(Time::GetDeltaTime() * 1000);
            
			if (task.Remaining <= 0 || task.Check())
			{
				task.Callback();
				task.Remaining = task.Interval;
			}
		}

		mainTasks.erase(std::remove_if(mainTasks.begin(), mainTasks.end(),
									   [](const ScheduledTask& task)
									   { return task.Remaining <= 0 || task.Check(); }),
						mainTasks.end());
	}

	void Scheduler::Shutdown()
	{
		running = false;
		taskCondition.notify_all();
		
        if (workerThread.joinable())
        {
			workerThread.join();
		}
	}

	void Scheduler::WorkerRun()
	{
		while (running)
		{
			std::unique_lock<std::mutex> lock(taskMutex);

			taskCondition.wait(lock,
							   [] { return !workerThreadTasks.empty() || !running; });

			for (auto& task : workerThreadTasks)
			{
				task.Remaining -= static_cast<long>(Time::GetDeltaTime() * 1000);

				if (task.Remaining <= 0)
				{
					task.Callback();
					task.Remaining = task.Interval;
				}
			}

			workerThreadTasks.erase(std::remove_if(workerThreadTasks.begin(),
												   workerThreadTasks.end(),
												   [](const ScheduledTask& task)
												   { return task.Remaining <= 0; }),
									workerThreadTasks.end());
		}
	}

	auto Scheduler::ChooseTaskList(TaskPriority priority) -> std::vector<ScheduledTask>*
	{
		if (priority == TaskPriority::Blocking)
		{
			return &mainTasks;
		}

		if (priority == TaskPriority::NonBlocking)
		{
			return &workerThreadTasks;
		}

		if (workerThreadTasks.size() < 48 && mainTasks.size() > 48)
		{
			return &workerThreadTasks;
		}

		return &mainTasks;
	}
}