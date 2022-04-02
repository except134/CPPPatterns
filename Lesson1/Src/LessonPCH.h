#pragma once

//////////////////////////////////////////////////////////////////////////
// STL part

// STL common
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <chrono>
#include <atomic>
#include <cmath>
#include <mutex>
#include <thread>
#include <filesystem>
#include <typeinfo>
#include <optional>
#include <type_traits>
#include <utility>
#include <system_error>
#include <stdexcept>
#include <new>
#include <cwchar>
#include <exception>

// STL containers
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <tuple>
#include <initializer_list>
#include <iterator>
#include <future>

// STL algorithms & functions
#include <algorithm>
#include <limits>
#include <iterator>
#include <numeric>
#include <numbers>
#include <functional>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////
// Windows part
#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <conio.h>

#endif

//////////////////////////////////////////////////////////////////////////
// Common part
#include "Common/Common.h"
#include "Common/Singleton.h"
#include "Common/ILogger.h"
#include "Common/LoggerFile.h"
#include "Common/LoggerProxy.h"
#include "Common/Input.h"

//////////////////////////////////////////////////////////////////////////
// Graphics part
#include "Graphics/IScreen.h"
#include "Graphics/ScreenConsolePlain.h"
#include "Graphics/ScreenConsoleBuffered.h"

//////////////////////////////////////////////////////////////////////////
// Game part
#include "Game/GameObject.h"
#include "Game/DynamicObject.h"
#include "Game/DestroyableGroundObject.h"
#include "Game/LevelGUI.h"
#include "Game/Iterator.h"
#include "Game/Bomb.h"
#include "Game/Ground.h"
#include "Game/Plane.h"
#include "Game/Tank.h"
#include "Game/House.h"
#include "Game/Command.h"
#include "Game/ObjectCommand.h"
#include "Game/SBomber.h"

