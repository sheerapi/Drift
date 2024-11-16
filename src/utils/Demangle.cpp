#include "utils/Demangle.h"
#include "utils/StringUtils.h"
#include <memory>

#if defined(__GNUG__) || defined(__clang__)
#include <cxxabi.h>
#elif defined(_MSC_VER)
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")
#endif

auto demangle(const char* name) -> std::string {
#if defined(__GNUG__) || defined(__clang__)
    int status = -4; // some arbitrary value to eliminate the compiler warning
    std::unique_ptr<char, void(*)(void*)> res{
        abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;

#elif defined(_MSC_VER)
    // MSVC-specific demangling using UnDecorateSymbolName from DbgHelp
    char undecorated_name[256]; // Adjust size as needed
    if (UnDecorateSymbolName(name, undecorated_name, sizeof(undecorated_name), UNDNAME_COMPLETE)) {
        return std::string(undecorated_name);
    } else {
        return name; // Return original name if demangling fails
    }

#else
    // If the compiler is not supported, just return the original name
    return name;
#endif
}

auto getNamespaceFreeName(const std::string& name) -> std::string
{
    return stringSplit(name, "::").back();
}