#pragma once
#include "core/Macros.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

namespace Drift::Threading
{
    class dt_api Thread
    {
    public:
		Thread(const std::function<void()>& callback,
			   const std::function<void()>& cleanup = nullptr)
			: _cleanup(cleanup), _callback(callback) {};
            
        ~Thread();

		auto IsRunning() -> bool;
        auto IsRunning(bool running) -> Thread*;

        auto Detach() -> Thread*;
        auto Detached() -> bool;

		auto CleanupCallback(const std::function<void()>& callback) -> Thread*;

		auto Name() -> std::string;
        auto Name(const std::string& name) -> Thread*;

        auto GetID() -> std::thread::id;

        void Start();
        void Join();

    private:
        std::thread* _thread;
        std::atomic<bool> _running{false};
        bool _detached;
        std::function<void()> _cleanup;
		std::function<void()> _callback;
		std::condition_variable _cv;
		std::mutex _sharedMutex;
        std::string _name{"Unknown"};
    };
}