#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(YuriTea LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_Package(SDL2_image REQUIRED)
find_package(rttr CONFIG REQUIRED)

#find_program(GLSLC_PROGRAM glslc REQUIRED)

#message(STATUS "run glslc to compile shaders ...")
#execute_process(COMMAND ${GLSLC_PROGRAM} ${CMAKE_SOURCE_DIR}/shader/shader2d.vert -o ${CMAKE_SOURCE_DIR}/shader/vert2d.spv)
#execute_process(COMMAND ${GLSLC_PROGRAM} ${CMAKE_SOURCE_DIR}/shader/shader2d.frag -o ${CMAKE_SOURCE_DIR}/shader/frag2d.spv)
#message(STATUS "compile shader OK")


#递归添加所有源文件
file(GLOB_RECURSE SRC_FILES
  ./tool/*.cpp
  ./glad/*.cpp
  ./window/*.cpp
  ./basic/*.cpp
)

set(LIBYURITEA_SRC ${SRC_FILES})

add_executable(${PROJECT_NAME}
  ./YuriTea.cpp
  ${SRC_FILES}
  
)


target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${RTTR_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ./tool)
target_include_directories(${PROJECT_NAME} PUBLIC ./glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC ./window)
target_include_directories(${PROJECT_NAME} PUBLIC ./basic)


target_link_libraries(${PROJECT_NAME} PUBLIC
  SDL2::SDL2
  SDL2::SDL2main
  SDL2_image::SDL2_image
  RTTR::Core
  )
