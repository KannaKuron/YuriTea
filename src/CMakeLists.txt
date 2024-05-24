cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe" CACHE STRING "")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe" CACHE STRING "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义项目名称和语言
project(YuriTea LANGUAGES CXX)

set(PUBLICS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Publics)
set(PRIVATES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Privates)
set(DEPENDENCIES_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)

# 明确指定源文件类型
file(GLOB_RECURSE SRC_FILES
  ${PRIVATES_DIR}/*.*
  ${PUBLICS_DIR}/*.*
  ${DEPENDENCIES_HEADERS_DIR}/*.*
)

# 创建 YuriTea 库
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# 设定宏定义
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Platform_Windows)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_BUILD_DLL)

#如果是release 则不执行下面的宏添加
if(CMAKE_BUILD_TYPE MATCHES Debug)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_DEBUG)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_ENABLE_ASSERTS)
endif()

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
find_library(SPDLOG spdlog HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2 SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2_MAIN SDL2main HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2_IMAGE SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(RTTR_CORE rttr_core HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(FMT fmt HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)

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

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
  ${SPDLOG}
  ${SDL2}
  ${SDL2_MAIN}
  ${SDL2_IMAGE}
  ${RTTR_CORE}
  ${FMT}
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
