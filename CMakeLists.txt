cmake_minimum_required(VERSION 3.7)
project(buildingLighting)

set(CMAKE_CXX_STANDARD 14)

# Including directories

# OpenGL search
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif(OPENGL_FOUND)

# GLEW seacrh
find_package(glew REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

# GLFW search
include(CMake/FindGLFW.txt)
if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIR})
endif(GLFW_FOUND)

# GLM search
include(CMake/FindGLM.txt)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif(GLM_FOUND)

# Assimp search
include(CMake/FindAssimp.txt)
if (ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIRS})
endif(ASSIMP_FOUND)

file(GLOB_RECURSE SOURCE_FILES
        src/*.cpp
        src/*.c
        src/*.hpp
        src/*.h
        SOIL2/*.c
        SOIL2/*.h
		imgui/*.cpp
		imgui/*.h)

file(GLOB_RECURSE SHADER_FILES
        resources/shaders/*.frag
        resources/shaders/*.vert)

add_executable(buildingLighting ${SOURCE_FILES} ${SHADER_FILES})

# Linking libraries

if (OPENGL_FOUND)
    target_link_libraries(buildingLighting ${OPENGL_gl_LIBRARY})
endif(OPENGL_FOUND)

if (GLEW_FOUND)
    target_link_libraries(buildingLighting ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

if (GLFW_FOUND)
    target_link_libraries(buildingLighting ${GLFW_LIBRARIES})
endif(GLFW_FOUND)

if (ASSIMP_FOUND)
    target_link_libraries(buildingLighting ${ASSIMP_LIBRARIES})
endif(ASSIMP_FOUND)