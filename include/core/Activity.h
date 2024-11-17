#pragma once
#include "core/Element.h"

namespace Drift
{
    class View;

    class Activity
    {
    public:
        enum class Status
        {
            Active,
            Paused,
            Destroyed
        };

        virtual ~Activity() = default;
        Activity();

        auto GetActivityID() -> std::string;

        virtual void OnCreate() {};
        virtual void OnPause() {};
        virtual void OnResume() {};
        virtual void OnDestroy() {};

        void Finish();
        void PrintElementTree();

        void SetStatus(Status status);
		void SetContainingView(View* view);

        auto GetStatus() -> Status;
        auto GetContainingView() -> View*;

    protected:
        std::shared_ptr<Element> Root;

	private:
        Status _status{Activity::Status::Active};
        View* _containingView;
    };
}