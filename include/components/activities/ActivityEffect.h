#pragma once
#include "core/Macros.h"
#include "utils/Color.h"

namespace Drift
{
    class dt_api Activity;
}

namespace Drift::Components::Activities
{
	class dt_api ActivityEffect
    {
    public:
        virtual void BeginDraw(){};
        virtual void EndDraw(){};
        
        virtual void Present(Activity* activity){};
        virtual void Shutdown(Activity* activity){};

        virtual auto GetPriority() -> int { return 0; }
    };

	class dt_api FadeEffect : public ActivityEffect
	{
	public:
		FadeEffect(float alpha = 0.5F, Color fadeColor = {0,0,0,0})
			: _color(fadeColor), _alpha(alpha) {};
            
		void Present(Activity* activity) override;
		void Shutdown(Activity* activity) override;
		void BeginDraw() override;
        void EndDraw() override;

		auto GetPriority() -> int override
		{
			return 10;
		}

	private:
        Color _color;
        float _alpha{0.5};
	};
}