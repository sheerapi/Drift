#include "utils/LibraryManager.h"
#include "core/Logger.h"
#include "utils/PerformanceTimer.h"
#include "utils/StringUtils.h"
#include <cstring>
#include <filesystem>
#include <vector>

#ifdef DEBUG
#	include "core/Application.h" // IWYU pragma: keep
#endif

auto libManagerInitCallback(struct dl_phdr_info* info, size_t size, void* data) -> int
{
	return Drift::LibraryManager::AddRefToLibrary(info, size, data);
}

namespace Drift
{
	auto Library::GetPath() -> std::string
	{
		auto** lmap = (link_map**)malloc(sizeof(link_map));

		if (dlinfo(_handle, RTLD_DI_LINKMAP, lmap) != 0)
		{
			dt_coreError("Failed to load library path (library = {}): {}", _handle,
						 dlerror());
			return "";
		}

		return (*lmap)->l_name;
	}

	auto Library::GetAddress() const -> ElfW(Addr)
	{
		return _addr;
	}

	auto Library::IsCoreLibrary() const -> bool
	{
		return _core;
	}

	auto Library::GetName() -> std::string
	{
		return stringSplit(std::filesystem::path(GetPath()).filename(), ".so")[0] + ".so";
	}

	void LibraryManager::Init()
	{
		dt_stopwatch();

		dl_iterate_phdr(libManagerInitCallback, nullptr);

		if (firstTimeRan)
		{
			dt_coreVerbose("Loaded {} dynamic libraries", libraries.size());
		}

		firstTimeRan = false;
	}

	auto LibraryManager::GetLoadedLibraries() -> std::vector<std::shared_ptr<Library>>
	{
		std::vector<std::shared_ptr<Library>> result;
		for (auto it = result.begin(); it != result.end(); ++it)
		{
			result.push_back(*it);
		}

		return result;
	}

	auto LibraryManager::HasLibrary(const std::string& name) -> bool
	{
		return libraries.contains(name);
	}

	auto LibraryManager::LoadLibrary(const std::string& name) -> std::shared_ptr<Library>
	{
		dt_stopwatch();

		if (HasLibrary(name))
		{
			return libraries[name];
		}

		auto* lib = dlopen(name.c_str(), RTLD_LAZY | RTLD_LOCAL);

		auto** lmap = (link_map**)malloc(sizeof(link_map));

		if (dlinfo(lib, RTLD_DI_LINKMAP, lmap) != 0)
		{
			dt_coreError("Failed to load library address (library = {}): {}", lib,
						 dlerror());
			return nullptr;
		}

		auto libWrapper = std::make_shared<Library>(lib);
		libWrapper->_addr = (*lmap)->l_addr;
		libraries[libWrapper->GetName()] = libWrapper;

		dt_coreVerbose("Dynamically loaded {}", libWrapper->ToString());
		Init();

		return libWrapper;
	}

	auto LibraryManager::AddRefToLibrary(struct dl_phdr_info* info, size_t size,
										 void* data) -> int
	{
		int status = 0;

		if (libraries.contains(info->dlpi_name))
		{
			return status;
		}

		auto* lib = dlopen(info->dlpi_name, RTLD_LAZY | RTLD_LOCAL);

		if (lib == nullptr)
		{
			return 1;
		}

		auto libWrapper = std::make_shared<Library>(lib);
		libWrapper->_addr = info->dlpi_addr;
		libraries[libWrapper->GetName()] = libWrapper;

		if (firstTimeRan)
		{
			libWrapper->_core = true;
		}

		return status;
	}

	void LibraryManager::UnloadLibrary(const std::string& name)
    {
        if (!HasLibrary(name))
        {
            dt_coreError("Library {} is not loaded!");
            return;
        }
        
        libraries.erase(name);
    }

	auto Library::ToString() -> std::string
	{
		return std::format("{} at {:#x} [ path = {}, core = {} ]", GetName(),
						   GetAddress(), GetPath(), IsCoreLibrary());
	}

	auto Library::HasSymbol(const std::string& name) -> bool
	{
		dlerror();
		static_cast<void>(dlsym(_handle, name.c_str()));
		return dlerror() == nullptr;
	}

	auto Library::GetSymbol(const std::string& name) -> void*
	{
		if (HasSymbol(name))
		{
			return dlsym(_handle, name.c_str());
		}

		dt_coreError("Symbol {} does not exist at {} ({})!", name, GetName(), _addr);
		return nullptr;
	}

	Library::~Library()
	{
		dlclose(_handle);
	}
}