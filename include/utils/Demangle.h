#pragma once
#include "core/Logger.h"
#include <string>
#include <typeinfo>

/**
 * @brief Tries to demangle a name, used internally
 *
 * @param name Name to demangle, usually by typeid().name()
 * @return std::string Demangled name, if using GCC/Clang/MSVC, otherwise the mangled one
 */
auto demangle(const char* name) -> std::string;

#define dt_type(type) demangle(typeid(type).name())

auto getNamespaceFreeName(const char* name) -> std::string;

template <typename T1, typename T2> auto typeCheck() -> bool
{
	if (!std::is_base_of<T1, T2>())
	{
		dt_coreError("Expected {}, got {}", dt_type(T1), dt_type(T2));
		return false;
	}

	return true;
}