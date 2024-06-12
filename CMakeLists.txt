#要求cmake的最低版本 3.20
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


project(YuriTeaTest LANGUAGES CXX)

set(PUBLICS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Publics)
set(DEPENDENCIES_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/include)
set(source_file_path "${CMAKE_CURRENT_SOURCE_DIR}/SandBox.cpp")

#如果是debug模式
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
message(STATUS "Setting Debug Mode")
set(YURITEA_DLL_PATH "${CMAKE_CURRENT_SOURCE_DIR}\\src\\lib\\Debug")
else()
 message(STATUS "Setting Release Mode")
set(YURITEA_DLL_PATH "${CMAKE_CURRENT_SOURCE_DIR}\\src\\lib\\Release")
endif()



if(WIN32)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_executable(${PROJECT_NAME}
    ${source_file_path}
  )
  else()
  add_executable(${PROJECT_NAME} WIN32
    ${source_file_path}
  )
  endif()
else()
add_executable(${PROJECT_NAME} 
  ${source_file_path}
)
endif()

if(WIN32)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Platform_Windows)
# 添加子系统标志
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTeaEngine)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Graphics_API_OpenGL)


target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<CONFIG:Debug>:YuriTea_DEBUG>
  PRIVATE $<$<CONFIG:Release>:YuriTea_RELEASE>
  PRIVATE $<$<CONFIG:Debug>:YuriTea_ENABLE_ASSERTS>
)


# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${PUBLICS_DIR}
  ${DEPENDENCIES_HEADERS_DIR}
)


# 链接动态导入库
find_library(YURITEA YuriTea HINTS "${YURITEA_DLL_PATH}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${YURITEA})


find_library(SPDLOG spdlog HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)
find_library(SDL2 SDL2 HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)
find_library(SDL2_MAIN SDL2main HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)
find_library(SDL2_IMAGE SDL2_image HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)
find_library(RTTR_CORE rttr_core HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)
find_library(FMT fmt HINTS ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/libs REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  ${SPDLOG}
  ${SDL2}
  ${SDL2_MAIN}
  ${SDL2_IMAGE}
  ${RTTR_CORE}
  ${FMT}
)


# 如果文件不同则复制

add_custom_target(copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${YURITEA_DLL_PATH}\\YuriTea.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}\\src\\vendor\\libs\\SDL2.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}\\src\\vendor\\libs\\SDL2_image.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"
    
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}\\src\\vendor\\libs\\fmt.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}\\src\\vendor\\libs\\rttr_core.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}\\src\\vendor\\libs\\spdlog.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"
)

# 确保在每次构建时都执行 copy_files 目标
set_target_properties(copy_files PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD FALSE)


