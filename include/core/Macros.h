#pragma once

#define dt_verboseFlag Drift::Application::main->GetEnvironmentInfo().Verbose

#if defined _WIN32 || defined __CYGWIN__
#	ifdef DT_IMPORT
#		ifdef __GNUC__
#			define dt_api __attribute__((dllimport))
#		else
#			define dt_api                                                               \
				__declspec(dllimport) // Note: actually gcc seems to also supports this
									  // syntax.
#		endif
#	else
#		ifdef __GNUC__
#			define dt_api __attribute__((dllexport))
#		else
#			define dt_api                                                               \
				__declspec(dllexport) // Note: actually gcc seems to also supports this
									  // syntax.
#		endif
#	endif
#	define dt_apiLocal
#else
#	if __GNUC__ >= 4
#		define dt_api __attribute__((visibility("default")))
#		define dt_apiLocal __attribute__((visibility("hidden")))
#	else
#		define dt_api
#		define dt_apiLocal
#	endif
#endif