# 要求 cmake 的最低版本
cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 定义项目名称和语言
project(YuriTea LANGUAGES CXX)


# 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



set(PUBLICS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Publics)
set(PRIVATES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Privates)
set(DEPENDENCIES_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include)

file(GLOB_RECURSE SRC_FILES ${PUBLICS_DIR}/*.*)

# 创建 YuriTea 库
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

# 设定宏定义
target_compile_definitions(${PROJECT_NAME} PRIVATE   YuriTea_Platform_Windows)
target_compile_definitions(${PROJECT_NAME} PRIVATE   YuriTea_DEBUG)
target_compile_definitions(${PROJECT_NAME} PRIVATE   YuriTea_ENABLE_ASSERTS)
target_compile_definitions(${PROJECT_NAME} PRIVATE   YuriTea_BUILD_DLL)



# 设置 include 目录
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${PUBLICS_DIR}
  ${DEPENDENCIES_HEADERS_DIR}
)


# 设置用到的其他的动态库和其对应的动态导入库
# 文件都在vendor/libs目录下
#target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs) # 设置动态库目录

# 寻找动态库
find_library(SPDLOG spdlog HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2 SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(SDL2_IMAGE SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(GLAD glad HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)
find_library(RTTR_CORE rttr_core HINTS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libs REQUIRED)


target_link_libraries(${PROJECT_NAME} PUBLIC
  ${SPDLOG}
  ${SDL2}
  ${SDL2_IMAGE}
  ${GLAD}
  ${RTTR_CORE}
)

# 设置PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Publics/YuriTea/Core/core.hpp
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
