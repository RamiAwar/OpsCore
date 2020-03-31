#pragma once

#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace oc {

	class Log
	{
	
	public:
		
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}


// --------- CORE LOGGING MACROS ---------------------------------------------

#define OC_TRACE(...)    ::oc::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OC_INFO(...)     ::oc::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OC_WARN(...)     ::oc::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OC_ERROR(...)    ::oc::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OC_CRITICAL(...) ::oc::Log::GetCoreLogger()->critical(__VA_ARGS__)

// ---------------------------------------------------------------------------
#define OC_CLIENT_TRACE(...)	::oc::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OC_CLIENT_INFO(...)		::oc::Log::GetClientLogger()->info(__VA_ARGS__)
#define OC_CLIENT_WARN(...)		::oc::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OC_CLIENT_ERROR(...)	::oc::Log::GetClientLogger()->error(__VA_ARGS__)
#define OC_CLIENT_CRITICAL(...)	::oc::Log::GetClientLogger()->critical(__VA_ARGS__)

