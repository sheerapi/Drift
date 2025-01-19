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
        virtual void BeginDraw(Activity* activity){};
        virtual void EndDraw(Activity* activity){};
        
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
		void BeginDraw(Activity* activity) override;
        void EndDraw(Activity* activity) override;

		auto GetPriority() -> int override
		{
			return 10;
		}

	private:
        Color _color;
        float _alpha{0.5};
	};

	class dt_api SlideEffect : public ActivityEffect
	{
	public:
		enum class Direction
		{
			Left,
			Right,
			Top,
			Bottom
		};

		SlideEffect(Direction direction)
			: _direction(direction) {};

		void Present(Activity* activity) override;
		void Shutdown(Activity* activity) override;
		void BeginDraw(Activity* activity) override;
		void EndDraw(Activity* activity) override;

		auto GetPriority() -> int override
		{
			return 9;
		}

	private:
		float _xPos;
		float _yPos;
		Direction _direction;
	};

	class dt_api RotateEffect : public ActivityEffect
	{
	public:
		RotateEffect(float degrees = 360) : _oldDegrees(degrees) {};

		void Present(Activity* activity) override;
		void Shutdown(Activity* activity) override;
		void BeginDraw(Activity* activity) override;
		void EndDraw(Activity* activity) override;

		auto GetPriority() -> int override
		{
			return 8;
		}

	private:
		float _degrees;
		float _oldDegrees;
	};

	class dt_api ScaleEffect : public ActivityEffect
	{
	public:
		ScaleEffect(float scale = 0.0F) : _oldDegrees(scale) {};

		void Present(Activity* activity) override;
		void Shutdown(Activity* activity) override;
		void BeginDraw(Activity* activity) override;
		void EndDraw(Activity* activity) override;

		auto GetPriority() -> int override
		{
			return 7;
		}

	private:
		float _degrees;
		float _oldDegrees;
	};
}