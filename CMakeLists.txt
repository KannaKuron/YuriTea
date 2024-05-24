#要求cmake的最低版本 3.20
cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(YuriTeaTest LANGUAGES CXX)

set(YURITEA_DLL_PATH "${CMAKE_CURRENT_SOURCE_DIR}\\src\\lib\\Debug")

add_executable(${PROJECT_NAME}
  ./SandBox.cpp
)

target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_DEBUG)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_ENABLE_ASSERTS)
target_compile_definitions(${PROJECT_NAME} PRIVATE YuriTea_Platform_Windows)

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE 
  src/Publics
  src/vendor/include
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
add_custom_command(TARGET YuriTeaTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${YURITEA_DLL_PATH}\\YuriTea.dll"
    "$<TARGET_FILE_DIR:YuriTeaTest>"
    COMMENT "Copying YuriTea.dll to output directory"

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


