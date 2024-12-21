#include "utils/Scheduler.h"
#include "core/Application.h"
#include "core/Logger.h"
#include "utils/Time.h"

namespace Drift
{
	void Scheduler::AddInterval(const Task& task, long longerval,
									TaskPriority priority)
	{
		std::lock_guard<std::mutex> lock(taskMutex);
		auto* taskList = ChooseTaskList(priority);
		taskList->push_back({task, longerval, longerval});

        if (taskList == &workerThreadTasks)
        {
            workerThread = std::thread(WorkerRun);
        }

        dt_coreVerbose("Scheduled timeout task in {} thread", taskList == &mainTasks ? "main" : "worker");
	}

	void Scheduler::AddTimeout(const Task& task, long timeout,
							   TaskPriority priority)
	{
		std::lock_guard<std::mutex> lock(taskMutex);
		auto* taskList = ChooseTaskList(priority);
		taskList->push_back({task, timeout, 0});

		if (taskList == &workerThreadTasks)
		{
			workerThread = std::thread(WorkerRun);
		}

		dt_coreVerbose("Scheduled timeout task in {} thread",
					   taskList == &mainTasks ? "main" : "worker");
	}

	void Scheduler::Update()
	{
		std::lock_guard<std::mutex> lock(taskMutex);

		for (auto& task : mainTasks)
		{
			task.Remaining -= static_cast<long>(Time::GetDeltaTime() * 1000);
            
			if (task.Remaining <= 0)
			{
				task.Callback();
				task.Remaining = task.Interval;
			}
		}

		mainTasks.erase(std::remove_if(mainTasks.begin(), mainTasks.end(),
									   [](const ScheduledTask& task)
									   { return task.Remaining <= 0; }),
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