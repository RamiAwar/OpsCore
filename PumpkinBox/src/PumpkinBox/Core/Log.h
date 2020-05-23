#pragma once

#include <memory>

#include "Core.h"
#include <stdio.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace pb {

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

#define PB_TRACE(...)    ::pb::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PB_INFO(...)     ::pb::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PB_WARN(...)     ::pb::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PB_ERROR(...)    ::pb::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PB_CRITICAL(...) ::pb::Log::GetCoreLogger()->critical(__VA_ARGS__)

// ---------------------------------------------------------------------------
#define PB_CLIENT_TRACE(...)	::pb::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PB_CLIENT_INFO(...)		::pb::Log::GetClientLogger()->info(__VA_ARGS__)
#define PB_CLIENT_WARN(...)		::pb::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PB_CLIENT_ERROR(...)	::pb::Log::GetClientLogger()->error(__VA_ARGS__)
#define PB_CLIENT_CRITICAL(...)	::pb::Log::GetClientLogger()->critical(__VA_ARGS__)

