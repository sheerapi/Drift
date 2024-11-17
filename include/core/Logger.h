#pragma once
#include <memory>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_COMPILED 1
#define SPDLOG_COMPILED_LIB 1
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

namespace Drift
{
	/**
	 * @brief Simple class for logging with pretty colors, and fast
	 *
	 * Used only by Drift, as it has the huge "Drift" name on it.
	 * For normal logging, use the "dt_" related macros
	 */
	class Logger
	{
	public:
		/**
		 * @brief Logs with an "info" level, and green
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Info(const std::string& msg, Args&&... args)
		{
			logger->info(msg, args...);
		}

		/**
		 * @brief Logs with a "warn" level, and yellow
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Warn(const std::string& msg, Args&&... args)
		{
			logger->warn(msg, args...);
		}

		/**
		 * @brief Logs with an "error" level, and red
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Error(const std::string& msg, Args&&... args)
		{
			logger->error(msg, args...);
		}

		/**
		 * @brief Logs with a "critical" level, and *bold* red
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Fatal(const std::string& msg, Args&&... args)
		{
			logger->critical(msg, args...);
		}

#ifdef DEBUG
		/**
		 * @brief Logs with a "debug" level, and cyan
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Debug(const std::string& msg, Args&&... args)
		{
			logger->debug(msg, args...);
		}
#endif

		/**
		 * @brief Logs with a "trace" level, and no color. crazy, right?
		 *
		 * @tparam Args Any fmt formattable type
		 * @param msg Message to log
		 * @param args Arguments to format the message with
		 */
		template <typename... Args>
		static void Trace(const std::string& msg, Args&&... args)
		{
			logger->trace(msg, args...);
		}

#ifdef DEBUG
		/**
		 * @brief Used only internally by Drift, but still available
		 *
		 * @param condition Condition to check, the message will only print if this
		 * evaluates to @code {.cpp} false
		 * @endcode
		 *
		 * @param conditionStr Basically the condition, but in string format
		 * @param file Filename where the assert came from
		 * @param msg Message to print if it evaluates to false
		 * @param line Line number where the assert came from

		 * This is supposed to be used in macros, don't expect simplicity
		 */
		static void Assert(bool condition, const std::string& conditionStr,
						   const std::string& file, const std::string& msg, int line)
		{

			if (!condition)
			{
				logger->info("Assertion \"{}\" failed ({}:{}): {}", conditionStr, file,
							 line, msg);
			}
		}
#endif

		/**
		 * @brief Simply initialize the loggers, with their patterns, names, and stuff
		 *
		 * Done automatically by @see Application when initializing, don't worry
		 */
		static void Init()
		{
			if (logger == nullptr)
			{
				logger = spdlog::stdout_color_mt("Drift");
				logger->set_pattern("[%^%n%$][%T][%l] %v");
				logger->set_level(spdlog::level::trace);

				std::shared_ptr<spdlog::logger> def = spdlog::stdout_color_mt("App");
				def->set_pattern("[%^%n%$][%T][%l][%s:%# %!()] %v");
				def->set_level(spdlog::level::trace);

				spdlog::set_default_logger(def);
			}
		}

	private:
		inline static std::shared_ptr<spdlog::logger> logger{nullptr};
	};
}

#define dt_info(msg, ...) SPDLOG_INFO(msg, ##__VA_ARGS__)
#define dt_warn(msg, ...) SPDLOG_WARN(msg, ##__VA_ARGS__)
#define dt_error(msg, ...) SPDLOG_ERROR(msg, ##__VA_ARGS__)
#define dt_fatal(msg, ...) SPDLOG_CRITICAL(msg, ##__VA_ARGS__)
#define dt_trace(msg, ...) SPDLOG_TRACE(msg, ##__VA_ARGS__)

#ifdef DEBUG
#	define dt_debug(msg, ...) SPDLOG_DEBUG(msg, ##__VA_ARGS__)
#	define dt_assert(condition, msg)                                                    \
		{                                                                                \
			if (!static_cast<bool>(condition))                                           \
				SPDLOG_INFO("Assertion \"{}\" failed: {}", #condition, msg);             \
		}
#	define dt_verbose(msg, ...)                                                         \
		{                                                                                \
			if (Drift::Application::main->GetEnvironmentInfo().Verbose)                         \
				SPDLOG_INFO(msg, ##__VA_ARGS__);                                         \
		}
#else
#	define dt_debug(msg, ...)
#	define dt_assert(condition, msg)
#	define dt_verbose(msg, ...)
#endif

#define dt_coreInfo(msg, ...) Drift::Logger::Info(msg, ##__VA_ARGS__)
#define dt_coreWarn(msg, ...) Drift::Logger::Warn(msg, ##__VA_ARGS__)
#define dt_coreError(msg, ...) Drift::Logger::Error(msg, ##__VA_ARGS__)
#define dt_coreFatal(msg, ...) Drift::Logger::Fatal(msg, ##__VA_ARGS__)
#define dt_coreTrace(msg, ...) Drift::Logger::Trace(msg, ##__VA_ARGS__)

#ifdef DEBUG
#	define dt_coreDebug(msg, ...) Drift::Logger::Debug(msg, ##__VA_ARGS__)
#	define dt_coreAssert(condition, msg)                                                \
		Drift::Logger::Assert(static_cast<bool>(condition), #condition, __FILENAME__,    \
							  msg, __LINE__)
#	define dt_coreVerbose(msg, ...)                                                     \
		{                                                                                \
			if (Drift::Application::main->GetEnvironmentInfo().Verbose)                         \
				Drift::Logger::Trace(msg, ##__VA_ARGS__);                                 \
		}
#else
#	define dt_coreDebug(msg, ...)
#	define dt_coreAssert(condition, msg)
#	define dt_coreVerbose(msg, ...)
#endif