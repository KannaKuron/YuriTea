cmake_minimum_required(VERSION 3.20.0)


set(CMAKE_GENERATOR "Ninja Multi-Config" CACHE INTERNAL "" FORCE)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
  message(STATUS "Setup ccache for the project.")
  message(STATUS "Found ccache: ${CCACHE_PROGRAM}")
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
else()
  message(STATUS "ccache not found.")
endif()



set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)




set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义项目名称和语言
project(YuriTea LANGUAGES CXX)


set(PUBLICS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Publics)
set(PRIVATES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Privates)
set(DEPENDENCIES_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)
set(DEPENDENCIES_SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/src)

# 明确指定源文件类型
file(GLOB_RECURSE SRC_FILES
  ${PRIVATES_DIR}/*.*
  ${DEPENDENCIES_SRCS_DIR}/*.*
)

# 创建 YuriTea 库
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# 设定宏定义
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTeaEngine)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Platform_Windows)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_BUILD_DLL)

#如果编译模式为Debug，定义 YuriTea_DEBUG 和 YuriTea_ENABLE_ASSERTS
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_DEBUG)
  target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_ENABLE_ASSERTS)
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Graphics_API_OpenGL)

# 设置 include 目录
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${PUBLICS_DIR}
  ${DEPENDENCIES_HEADERS_DIR}
)


# 设置PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Publics/YuriTea/Core/core.hpp
)

# 设置用到的其他的动态库和其对应的动态导入库
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs) # 设置动态库目录

# 寻找动态库
find_library(SDL2 NAMES SDL2 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2_MAIN NAMES SDL2main PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2_IMAGE NAMES SDL2_image PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(RTTR_CORE NAMES rttr_core PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(FMT NAMES fmt PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(GLAD NAMES glad PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SPDLOG NAMES spdlog PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)

# 检查库是否找到
if(NOT SPDLOG)
  message(FATAL_ERROR "spdlog library not found.")
endif()
if(NOT SDL2)
  message(FATAL_ERROR "SDL2 library not found.")
endif()
if(NOT SDL2_IMAGE)
  message(FATAL_ERROR "SDL2_image library not found.")
endif()
if(NOT RTTR_CORE)
  message(FATAL_ERROR "rttr_core library not found.")
endif()
if(NOT FMT)
  message(FATAL_ERROR "fmt library not found.")
endif()
if(NOT GLAD)
  message(FATAL_ERROR "glad library not found.")
endif()

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SPDLOG}
  ${SDL2}
  ${SDL2_MAIN}
  ${SDL2_IMAGE}
  ${RTTR_CORE}
  ${FMT}
  ${GLAD}
)


# 设置库属性
set_target_properties(YuriTea PROPERTIES
  LINKER_LANGUAGE CXX
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
  OUTPUT_NAME "YuriTea"
  PREFIX "" # 去除生成的 dll 文件名前缀
)
