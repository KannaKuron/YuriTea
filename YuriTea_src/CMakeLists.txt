# 要求 cmake 的最低版本
cmake_minimum_required(VERSION 3.20)

# 导出编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置构建类型
set(CMAKE_BUILD_TYPE Release)

# 使用 vcpkg 的工具链文件
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# 定义项目名称和语言
project(YuriTea LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 寻找所需的包
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(rttr CONFIG REQUIRED)

# 定义所有代码文件夹
set(INCLUDE_DIRS
  tool
  glad
  window
  basic
)

# 递归添加所有源文件和头文件
file(GLOB_RECURSE SRC_FILES
  ./glad/glad.c

  ./tool/*.cpp
  ./window/*.cpp
  ./basic/*.cpp

)
file(GLOB_RECURSE HEADER_FILES
  ./glad/glad.h
  
  ./window/*.hpp
  ./basic/*.hpp
  ./tool/*.hpp
  
)

# 指定dll输出目录
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./YuriTeaDLL/lib) 

# 指定可执行文件输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/YuriTeaDLL) 

# 指定静态库输出目录
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./YuriTeaDLL/lib) 

# 设置安装目录
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# 创建 YuriTea 库
add_library(YuriTea SHARED ${SRC_FILES})
#add_library(YuriTea STATIC ${SRC_FILES})

install(TARGETS YuriTea
        # RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/bin

        LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib

        ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib
)

# 安装头文件到 include 目录，保持原始文件夹结构
install(DIRECTORY ${INCLUDE_DIRS} DESTINATION ${CMAKE_SOURCE_DIR}/YuriTeaDLL/include
         FILES_MATCHING           # 仅匹配文件
        PATTERN "*.hpp"          # 匹配以 .hpp 结尾的文件
        PATTERN "*.h"            # 匹配以 .h 结尾的文件
        PATTERN "*.cpp" EXCLUDE  # 排除以 .cpp 结尾的文件
        PATTERN "*.c" EXCLUDE   # 排除以 .c 结尾的文件
)

# 设置库属性
set_target_properties(YuriTea PROPERTIES
  LINKER_LANGUAGE CXX
  # RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/YuriTeaDLL/lib
  OUTPUT_NAME "YuriTea"
  PREFIX "" # 去除生成的 dll 文件名前缀
)

# 添加头文件路径
target_include_directories(YuriTea PUBLIC
  ${INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS}
  ${RTTR_INCLUDE_DIR}
)

# 链接库
target_link_libraries(YuriTea PRIVATE
  SDL2::SDL2
  SDL2::SDL2main
  SDL2_image::SDL2_image
  RTTR::Core
)

