#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(DEFINED ENV{VCPKG_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_TOOLCHAIN_FILE}")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
endif()

project(YuriTeaTest LANGUAGES CXX)


set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")


set(CMAKE_BUILD_TYPE Debug)

set(DLL_DIR ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib)


add_subdirectory(YuriTea_src)

add_executable(${PROJECT_NAME}
  ./SandBox.cpp
)

target_compile_definitions(YuriTeaTest PRIVATE YuriTea_DEBUG)
target_compile_definitions(YuriTeaTest PRIVATE YuriTea_ENABLE_ASSERTS)
target_compile_definitions(YuriTeaTest PRIVATE YuriTea_Platform_Windows)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE YuriTeaDLL/Publics)


# 如果需要，复制DLL到可执行文件的输出目录
add_custom_command(TARGET YuriTeaTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${DLL_DIR}/YuriTea.dll"
    $<TARGET_FILE_DIR:YuriTeaTest>
)
message("Copy YuriTea.dll to output directory.")
# 拷贝sdl2.dll
add_custom_command(TARGET YuriTeaTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${DLL_DIR}/SDL2.dll"
    $<TARGET_FILE_DIR:YuriTeaTest>
)

# 链接动态导入库
link_directories(${DLL_DIR})
target_link_libraries(${PROJECT_NAME} YuriTea)

