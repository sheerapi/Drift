#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace Drift::Internals
{
    struct WorkerTask
    {
    public:
        std::function<void()> Task;
        bool Done{false};
        bool Waiting{true};
    };
    struct WorkerThread
    {
    public:
        std::thread Thread;
        std::mutex Mutex;
        std::condition_variable Condition;
        std::vector<WorkerTask> Tasks;
        std::atomic<bool> Running;
        std::atomic<bool> Busy;

        void Run();
    };

    class WorkerScheduler
    {
    public:
		static void AddTask(const std::function<void()>& task);
        static void Update();

    private:
        inline static std::vector<WorkerThread*> threads;
		inline static std::vector<WorkerTask> waitingTasks;
		static auto GetAvailableThread() -> WorkerThread*;
        static auto CreateWorkerThread() -> WorkerThread*;
        static void RunThread(WorkerThread* thread);
	};
}