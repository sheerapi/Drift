#pragma once
#include "../core/Macros.h"
#define _GNU_SOURCE 1
#include <cstdint>
#include <link.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Drift
{
	class dt_api Library
	{
	public:
		Library(void* handle) : _handle(handle) {};
		~Library();

		auto HasSymbol(const std::string& name) -> bool;
		auto GetSymbol(const std::string& name) -> void*;

		auto GetPath() -> std::string;
		auto GetName() -> std::string;
		[[nodiscard]] auto GetAddress() const -> uint64_t;
		[[nodiscard]] auto IsCoreLibrary() const -> bool;

		auto ToString() -> std::string;

	private:
		void* _handle;
		ElfW(Addr) _addr;
		bool _core{false};

		friend class LibraryManager;
	};

	class dt_api LibraryManager
	{
	public:
		static auto LoadLibrary(const std::string& name) -> std::shared_ptr<Library>;
		static auto HasLibrary(const std::string& name) -> bool;
		static void UnloadLibrary(const std::string& name);
		static auto AddRefToLibrary(struct dl_phdr_info* info, size_t size,
									void* data) -> int;

		static auto GetLoadedLibraries() -> std::vector<std::shared_ptr<Library>>;

	private:
		inline static std::unordered_map<std::string, std::shared_ptr<Library>> libraries;
		static void Init();
		inline static bool firstTimeRan{true};

		friend class Application;
	};
}