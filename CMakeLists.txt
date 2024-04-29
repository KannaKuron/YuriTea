#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(YuriTeaTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

ADD_SUBDIRECTORY(./YuriTea_scr)


add_executable(${PROJECT_NAME}
  ./YuriTea.cpp
)
# 添加对 YuriTea DLL 的链接
target_link_libraries(${PROJECT_NAME} PUBLIC YuriTea)



