#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include "core/Macros.h"

namespace Drift
{
    using Task = std::function<void()>;

    class dt_api Scheduler
    {
    public:
        struct ScheduledTask
        {
        public:
            Task Callback;
            long Remaining;
            long Interval;
        };

        enum class TaskPriority
        {
            Blocking,
            NonBlocking,
            Auto
        };

        static void AddInterval(const Task& task, long longerval, TaskPriority priority = TaskPriority::Auto);
        static void AddTimeout(const Task& task, long timeout, TaskPriority priority = TaskPriority::Auto);

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