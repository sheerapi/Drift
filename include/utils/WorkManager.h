#pragma once
#include "utils/TaskScheduler.h"

namespace Drift::Threading
{
    class WorkManager
    {
    public:
    private:
        inline static TaskScheduler scheduler;
	};
}