#include "core/WorkerScheduler.h"
#include "core/Application.h"
#include "core/Logger.h"
#include <algorithm>
#include <mutex>

namespace Drift::Internals
{
	void WorkerScheduler::AddTask(const std::function<void()>& task)
	{
		auto* thread = GetAvailableThread();
		
		if (thread != nullptr)
		{
			std::lock_guard<std::mutex> lock{thread->Mutex};
			thread->Tasks.push_back({.Task = task, .Waiting = false});
			thread->Condition.notify_all();
		}
		else
		{
			waitingTasks.push_back({task});
		}
	}

	auto WorkerScheduler::GetAvailableThread() -> WorkerThread*
	{
		for (auto& thread : threads)
		{
			if (!thread->Busy.load())
			{
				return thread;
			}
		}

		return (unsigned int)threads.size() < std::thread::hardware_concurrency() * 2
				   ? CreateWorkerThread()
				   : nullptr;
	}

	auto WorkerScheduler::CreateWorkerThread() -> WorkerThread*
	{
		dt_coreVerbose("Allocating new worker thread...");
		
		auto* thread = new WorkerThread();
		thread->Thread = std::thread([thread]() { RunThread(thread); });
		return thread;
	}

	void WorkerScheduler::RunThread(WorkerThread* thread)
	{
		while (thread->Running.load())
		{
			std::unique_lock<std::mutex> lock{thread->Mutex};
			thread->Condition.wait(
				lock, [thread]() { return !thread->Tasks.empty() || !thread->Running; });

			for (auto& task : thread->Tasks)
			{
				thread->Busy.store(true);
				task.Task();
				task.Done = true;
				thread->Busy.store(false);
			}

			thread->Tasks.erase(std::remove_if(thread->Tasks.begin(), thread->Tasks.end(),
											   [](const WorkerTask& task)
											   { return task.Done; }),
								thread->Tasks.end());
		}
	}

	void WorkerScheduler::Update()
	{
		for (auto& task : waitingTasks)
		{
			auto* thread = GetAvailableThread();

			if (thread == nullptr)
			{
				break;
			}

			AddTask(task.Task);
			task.Waiting = false;
		}

		if (waitingTasks.size() != 0)
		{
			waitingTasks.erase(std::remove_if(waitingTasks.begin(), waitingTasks.end(),
											  [](const WorkerTask& task)
											  { return !task.Waiting; }),
							   waitingTasks.end());
		}
	}
}