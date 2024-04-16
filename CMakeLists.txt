cmake_minimum_required(VERSION 3.25)
project(EZGL)

# main build files
set(HEADER_FILES 
    Camera.h
    Drawable.h
    InstancedDrawable.h
    ShaderProgram.h
    )

set(CPP_FILES
    Camera.cpp
    Drawable.cpp
    InstancedDrawable.cpp
    ShaderProgram.cpp
    )

add_library(${PROJECT_NAME} STATIC "${CPP_FILES};${HEADER_FILES}")

# include glm
add_subdirectory(./lib/glm)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/glm/)
target_link_libraries(${PROJECT_NAME} glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm/)