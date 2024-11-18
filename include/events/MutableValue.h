#pragma once
#include "core/Macros.h"
#include <functional>
#include <memory>

namespace Drift::Events
{
	template <typename T> class dt_api MutableValue
	{
	public:
		MutableValue(T value) : _value(std::make_unique<T>(value)) {};

		void OnMutate(std::function<void(T old, T newVal)> callback)
		{
			_callback = callback;
		}

		auto operator=(T val) -> MutableValue<T>&
		{
			_callback(*_value, val);
			*_value = val;
		}

		auto operator+(T val) -> T&
		{
			return *_value + val;
		}

		auto operator-(T val) -> T&
		{
			return *_value - val;
		}

		auto operator*(T val) -> T&
		{
			return *_value * val;
		}

		auto operator/(T val) -> T&
		{
			return *_value / val;
		}

		auto operator+=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value + val);
			*_value += val;
			return *this;
		}

		auto operator-=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value - val);
			*_value -= val;
			return *this;
		}

		auto operator*=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value * val);
			*_value *= val;
		}

		auto operator/=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value / val);
			*_value /= val;
			return *this;
		}

		auto operator%=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value % val);
			*_value %= val;
			return *this;
		}

		auto operator&=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value & val);
			*_value &= val;
			return *this;
		}

		auto operator|=(T val) -> MutableValue<T>&
		{
			_callback(*_value, *_value | val);
			*_value |= val;
			return *this;
		}

		auto operator++() -> MutableValue<T>&
		{
			_callback(*_value, ++*_value);
			return *this;
		}

		auto operator--() -> MutableValue<T>&
		{
			_callback(*_value, --*_value);
			return *this;
		}

		operator T()
		{
			return *_value;
		}

	private:
		std::unique_ptr<T> _value;
		std::function<void(T old, T newVal)> _callback{[](auto old, auto val) {}};
	};
}