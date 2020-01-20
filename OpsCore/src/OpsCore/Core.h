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


