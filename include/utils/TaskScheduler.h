#pragma once
#include <functional>
#include <queue>

namespace Drift::Threading
{
	using Task = std::function<void()>;

	enum class TaskPriority
	{
		Blocking,
		NonBlocking,
		Auto
	};

	struct ScheduledTask
	{
	public:
		Task Task;
		double Remaining;
		double Interval;
		unsigned int ID;
		TaskPriority Priority;

		auto operator>(const ScheduledTask& rhs) const -> bool
		{
			return Remaining > rhs.Remaining;
		}
	};

	class TaskScheduler
	{
	public:
        auto IsBusy() -> bool;
        
	private:
		std::priority_queue<ScheduledTask, std::vector<ScheduledTask>, std::greater<>>
			_taskQueue;

		friend class WorkManager;
	};
}