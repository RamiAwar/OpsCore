#pragma once
#include "OpsCore/Utils/debugbreak.h"
#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define OC_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define OC_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define OC_PLATFORM_MACOS
	#else 
		#error "Unknown Apple platform!"
	#endif
	
/* Check android before linux since it has __linux__ defined */
#elif defined(__ANDROID__)
	#define OC_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define OC_PLATFORM_LINUX
#else
	#error "Unknown platform!"
#endif 


#define BIT(x) (1<<x)
#define OC_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

namespace oc {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#ifdef OC_DEBUG
	#define OC_ENABLE_ASSERTS
#endif



#ifdef OC_ENABLE_ASSERTS

	#define OC_ASSERT(x, ...) { if(!(x)){ OC_ERROR("Assertion Failed: Error below:");OC_ERROR(__VA_ARGS__); debug_break(); } }

#else

	#define OC_ASSERT(x, ...)

#endif 

