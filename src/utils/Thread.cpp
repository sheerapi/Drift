#include "utils/Thread.h"
#include "core/Logger.h"

namespace Drift::Threading
{
	void Thread::Start()
	{
		_thread = new std::thread(
			[this]()
			{
				std::unique_lock<std::mutex> lock((_sharedMutex));
				_cv.wait(lock, [this] { return _running.load(); });

				lock.unlock();

				try
				{
					_callback();
				}
				catch (const std::exception& err)
				{
					dt_coreError("An exception occurred at thread {}: {}", Name(),
								 err.what());
				}

				try
				{
					if (_cleanup != nullptr)
					{
						_cleanup();
					}
				}
				catch (const std::exception& err)
				{
					dt_coreError("An exception occurred when cleaning up thread {}: {}",
								 Name(), err.what());
				}

				_running.store(false);
			});

		if (_detached)
		{
			_thread->detach();
		}

		_running.store(true);
	}

	Thread::~Thread()
	{
		if (_running.load() && !_detached)
		{
			_thread->join();
		}

		_running.store(false);
	}

	void Thread::Join()
	{
		if (_thread != nullptr)
		{
			if (_thread->joinable())
			{
				_thread->join();
			}
			else
			{
				dt_coreError("Thread is not joinable after being detached! ({})", Name());
			}
		}
	}

	auto Thread::IsRunning() -> bool
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		return _running.load();
	}

	auto Thread::IsRunning(bool running) -> Thread*
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		_running.store(running);
		return this;
	}

	auto Thread::Detach() -> Thread*
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);

		_detached = true;
		if (_thread != nullptr)
		{
			_thread->detach();
		}

		return this;
	}

	auto Thread::Detached() -> bool
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		return _detached;
	}

	auto Thread::CleanupCallback(const std::function<void()>& callback) -> Thread*
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		_cleanup = callback;
		return this;
	}

	auto Thread::Name() -> std::string
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		return _name;
	}

	auto Thread::Name(const std::string& name) -> Thread*
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		_name = name;
		return this;
	}

	auto Thread::GetID() -> std::thread::id
	{
		std::lock_guard<std::mutex> lock(_sharedMutex);
		if (_thread != nullptr)
		{
			return _thread->get_id();
		}
		return {};
	}
}