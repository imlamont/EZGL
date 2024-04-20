cmake_minimum_required(VERSION 3.25)
project(ezgl)

# main build files
set(HEADER_FILES 
    Camera.hpp
    Drawable.hpp
    InstancedDrawable.hpp
    ShaderProgram.hpp
    )

set(CPP_FILES
    Camera.cpp
    Drawable.cpp
    InstancedDrawable.cpp
    ShaderProgram.cpp
    )

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_library(${EXECUTABLE_NAME} STATIC "${CPP_FILES};${HEADER_FILES}")

# include glm
add_subdirectory(./lib/glm)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ./lib/glm/glm)
target_link_libraries(${EXECUTABLE_NAME} glm)
include_directories(./lib/glm/)

# glew
add_subdirectory(./lib/glew)
target_link_directories(${EXECUTABLE_NAME} PRIVATE ./lib/glew/Debug)
target_link_libraries(${PROJECT_NAME} glew_static)
include_directories(./lib/glew/include/)