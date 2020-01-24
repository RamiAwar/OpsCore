#pragma once


#ifdef OC_PLATFORM_WINDOWS

	#ifdef OC_BUILD_DLL
		#define OPSCORE_API __declspec(dllexport)
	#else 
		#define OPSCORE_API __declspec(dllimport)
	#endif
#else 
	#error OpsCore only support Windows platforms.
#endif

#define BIT(x) (1<<x)

#ifdef OC_DEBUG
	#define OC_ENABLE_ASSERTS
#endif

#ifdef OC_ENABLE_ASSERTS

	#define OC_ASSERT(x, ...) { if(!(x)){ OC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

	#define OC_ASSERT(x, ...)

#endif 

