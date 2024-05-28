#pragma once

//PCH for YuriTea

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
#include <fcntl.h>
#include <io.h>
#include <glad/glad.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <fmt/fmt.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <imgui/imgui.h>



#include "YuriTea/Core/basicstruct.hpp"
#include "YuriTea/Core/base.hpp"

#include "YuriTea/Core/log.hpp"

#ifdef YuriTea_Platform_Windows
#include <Windows.h>
#endif
