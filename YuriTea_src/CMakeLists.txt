# 要求 cmake 的最低版本
cmake_minimum_required(VERSION 3.20)

# 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置构建类型
set(CMAKE_BUILD_TYPE Release)

# 使用 vcpkg 的工具链文件
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

# 定义项目名称和语言
project(YuriTea LANGUAGES CXX)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
    set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")
else()
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif()



if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
# 寻找所需的包
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(RTTR CONFIG REQUIRED) 
find_package(FMT CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
else()

endif()



set(INCLUDE_DIRS
  Publics
)
set(SRC_DIRS
  Privates
)

# 递归添加所有源文件和头文件
file(GLOB_RECURSE SRC_FILES
  ${SRC_DIRS}/*.cpp
  ${SRC_DIRS}/*.c

)

file(GLOB_RECURSE HEADER_FILES
  ${INCLUDE_DIRS}/*.hpp
  ${INCLUDE_DIRS}/*.h
)


# 设置安装目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/YuriTeaDLL)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib)

# 创建 YuriTea 库
add_library(YuriTea SHARED ${SRC_FILES})


#设定宏定义
target_compile_definitions(YuriTea PRIVATE YuriTea_DEBUG)
target_compile_definitions(YuriTea PRIVATE YuriTea_ENABLE_ASSERTS)
target_compile_definitions(YuriTea PRIVATE YuriTea_DLL)
target_compile_definitions(YuriTea PRIVATE YuriTea_Platform_Windows)


# 设置PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/Publics/YuriTea/Core/core.hpp)



# 设置库属性
set_target_properties(YuriTea PROPERTIES
  LINKER_LANGUAGE CXX
  # RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
  OUTPUT_NAME "YuriTea"
  PREFIX "" # 去除生成的 dll 文件名前缀
)



set(DEPENDENCIES_DIRS

  ${SDL2_INCLUDE_DIR}

  ${RTTR_INCLUDE_DIR}

  ${FMT_INCLUDE_DIR}

  ${SPDLOG_INCLUDE_DIR}

)




# 添加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
  
  ${INCLUDE_DIRS}
  ${DEPENDENCIES_DIRS}
)


if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
  
  SDL2::SDL2
  SDL2::SDL2main
  SDL2_image::SDL2_image
  RTTR::Core
  spdlog::spdlog_header_only
)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE
  
)

endif()

#====================================================================================================



#install sdl2 and sdl2_image and rttr 的头文件
install(DIRECTORY 
  ${DEPENDENCIES_DIRS}
  DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/Publics
)

# 安装头文件到 include 目录，保持原始文件夹结构
install(DIRECTORY 

  ${INCLUDE_DIRS}

  DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL
)

# 安装 YuriTea 库
install(TARGETS ${PROJECT_NAME}
        

        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib

        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib

        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib

)



