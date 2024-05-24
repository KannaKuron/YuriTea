#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(YuriTeaTest LANGUAGES CXX)

add_subdirectory(src)

add_executable(${PROJECT_NAME}
  ./SandBox.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_DEBUG)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_ENABLE_ASSERTS)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Platform_Windows)
target_compile_definitions(${PROJECT_NAME} PRIVATE   YuriTea_BUILD_DLL)

#复制文件夹
file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/Publics)
file(COPY src/Publics DESTINATION ${CMAKE_SOURCE_DIR})


# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
  Publics
  src/vendor/include
)



# 链接动态导入库
link_directories(${CMAKE_SOURCE_DIR}/lib
  YuriTea
)

find_library(YuriTea YuriTea HINTS ${CMAKE_SOURCE_DIR}/lib/Debug)
target_link_libraries(${PROJECT_NAME} YuriTea)



