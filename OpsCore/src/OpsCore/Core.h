#pragma once


#ifdef OC_PLATFORM_WINDOWS

	//#ifdef OC_BUILD_DLL
	//	#define  __declspec(dllexport)
	//#else 
	//	#define  __declspec(dllimport)
	//#endif

#endif


#define BIT(x) (1<<x)
#define OC_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)

#ifdef OC_DEBUG
	#define OC_ENABLE_ASSERTS
#endif

#ifdef OC_ENABLE_ASSERTS

	#define OC_ASSERT(x, ...) { if(!(x)){ OC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else

	#define OC_ASSERT(x, ...)

#endif 

