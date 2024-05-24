#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>


#include <array>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <glad/glad.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>
#include <SDL2/SDL_opengl.h>

#include "YuriTea/Core/basicstruct.hpp"
#include "YuriTea/Core/base.hpp"

#include "YuriTea/Core/log.hpp"

#ifdef YuriTea_Platform_Windows
#include <Windows.h>
#endif
