#pragma once

//PCH for YuriTea

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>


#ifdef YuriTea_Platform_Windows
#include <io.h>
#endif
#include <exception>
#include <cstdlib>
#include <array>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fcntl.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>

//glad
#include <glad/glad.hpp>

//SDL
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

//fmt
#include <fmt/fmt.h>

//spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>



#include "YuriTea/Core/basicstruct.hpp"
#include "YuriTea/Core/base.hpp"

#include "YuriTea/Core/log.hpp"
#include "YuriTea/Events/event.hpp"
#include "YuriTea/Events/applicationEvent.hpp"
#include "YuriTea/Events/keyEvent.hpp"
#include "YuriTea/Events/controller.hpp"
#include "YuriTea/Events/mouseEvent.hpp"
#include "YuriTea/Core/input.hpp"
#include "YuriTea/Core/window.hpp"
#include "YuriTea/Core/application.hpp"

//imgui
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#ifdef YuriTea_Graphics_API_OpenGL
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui_impl_opengl3.h>
#endif
#include <imgui/imgui_impl_sdl2.h>


#ifdef YuriTea_Platform_Windows
#include <Windows.h>
#endif
