#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(DEFINED ENV{VCPKG_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_TOOLCHAIN_FILE}")
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
else()
    # 对于非Windows系统，可以选择不设置CMAKE_TOOLCHAIN_FILE
    # 或者设置为默认的工具链文件路径，这里选择不设置
    # 如果需要为其他系统指定默认路径，可以取消注释下面的行
    # set(CMAKE_TOOLCHAIN_FILE "/path/to/default/toolchain/file")
endif()

project(YuriTeaTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

ADD_SUBDIRECTORY(YuriTea_src)


add_executable(${PROJECT_NAME}
  YuriTea.cpp
)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE YuriTeaDLL/Publics)




# 添加对 YuriTea DLL 的链接
#target_link_libraries(${PROJECT_NAME} PRIVATE ./YuriTeaDLL/lib/YuriTea)
