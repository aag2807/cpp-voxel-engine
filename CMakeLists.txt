cmake_minimum_required(VERSION 3.28)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(/opt/homebrew/include /opt/homebrew/include/glm)

# Add the executable
add_executable(VoxelEngine main.cpp
        src/Voxel.cpp
        src/Voxel.h
        src/Chunk.cpp
        src/Chunk.h
        src/Renderer.cpp
        src/Renderer.h
        src/InputHandler.cpp
        src/InputHandler.h
        src/Camera.cpp
        src/Camera.h
        src/Context.cpp
        src/Context.h
)

# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(VoxelEngine ${OPENGL_LIBRARIES})

# Find and include GLFW
find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(VoxelEngine glfw)

# Find and include GLEW
find_path(GLEW_INCLUDE_DIR NAMES GL/glew.h PATHS /opt/homebrew/include)
find_library(GLEW_LIBRARY NAMES GLEW glew PATHS /opt/homebrew/lib)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(VoxelEngine ${GLEW_LIBRARY})

# Use the macOS system frameworks for GLUT
target_link_libraries(VoxelEngine "-framework GLUT")

# Ensure linking with OpenGL framework on macOS
target_link_libraries(VoxelEngine "-framework OpenGL")