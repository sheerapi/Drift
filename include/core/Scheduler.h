#pragma once
#include "core/Macros.h"
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

namespace Drift
{
	using Task = std::function<void()>;
	using TaskCheck = std::function<bool()>;

	class dt_api Scheduler
	{
	public:
		struct ScheduledTask
		{
		public:
			Task Callback;
			TaskCheck Check{[](){ return false; }};

			long Remaining;
			long Interval;
		};

		enum class TaskPriority
		{
			Blocking,
			NonBlocking,
			Auto
		};

		static void AddInterval(const Task& task, long interval,
								TaskPriority priority = TaskPriority::Auto);

		static void AddTimeout(const Task& task, long timeout,
							   TaskPriority priority = TaskPriority::Auto);

		static void AddCustomChecked(const Task& task, const TaskCheck& check,
									 TaskPriority priority = TaskPriority::Auto);

		static void Update();
		static void Shutdown();

	private:
		inline static std::vector<ScheduledTask> mainTasks;
		inline static std::vector<ScheduledTask> workerThreadTasks;
		inline static std::thread workerThread;
		inline static bool running = true;
		inline static std::mutex taskMutex;
		inline static std::condition_variable taskCondition;

		static void WorkerRun();
		static auto ChooseTaskList(TaskPriority priority) -> std::vector<ScheduledTask>*;
	};
}

#define dt_setInterval Drift::Scheduler::AddInterval
#define dt_setTimeout Drift::Scheduler::AddTimeout
#define dt_setChecker Drift::Scheduler::AddCustomChecked