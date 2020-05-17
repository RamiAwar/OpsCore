#pragma once

#define _CRT_SECURE_NO_WARNINGS // TODO: Remove when ImGui fixes their deprecated functions

// ---- STL includes -------
#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cstdint>


#include "PumpkinBox/Core/Log.h"

#ifdef PB_PLATFORM_WINDOWS

	#include <Windows.h>

#endif