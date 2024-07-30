cmake_minimum_required(VERSION 3.22.1)

project("gles_cube")

add_library(${CMAKE_PROJECT_NAME} SHARED
        cube.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/libraries/include)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        GLESv3
        )
