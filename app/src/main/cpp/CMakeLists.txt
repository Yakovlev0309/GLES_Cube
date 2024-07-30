cmake_minimum_required(VERSION 3.22.1)

project("gles_cube")

add_library(${CMAKE_PROJECT_NAME} SHARED
        cube.cpp
        cube.h
        shaders.h
        vao.h
        vao.cpp
        vbo.h
        vbo.cpp
        ebo.h
        ebo.cpp
        globject.h
        shader.h
        shader.cpp
        )

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/libraries/include)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        GLESv3
        )
