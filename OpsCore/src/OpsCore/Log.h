#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"


namespace oc {

	class OPSCORE_API Log
	{
	
	public:
		
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;

	};

}


// --------- CORE LOGGING MACROS ---------------------------------------------

#define OC_TRACE(...)    ::oc::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OC_INFO(...)     ::oc::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OC_WARN(...)     ::oc::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OC_ERROR(...)    ::oc::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OC_CRITICAL(...) ::oc::Log::GetCoreLogger()->critical(__VA_ARGS__)

// ---------------------------------------------------------------------------