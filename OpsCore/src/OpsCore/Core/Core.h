#pragma once
#include "OpsCore/Utils/debugbreak.h"


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
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif 


#define BIT(x) (1<<x)
#define OC_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)



#ifdef OC_DEBUG
	#define OC_ENABLE_ASSERTS
#endif



#ifdef OC_ENABLE_ASSERTS

	#define OC_ASSERT(x, ...) { if(!(x)){ OC_ERROR("Assertion Failed: {0}", __VA_ARGS__); debug_break(); } }

#else

	#define OC_ASSERT(x, ...)

#endif 
