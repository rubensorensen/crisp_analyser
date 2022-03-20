cmake_minimum_required(VERSION 3.20)
project(crispr_analysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS=ON)
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(glew-cmake_BUILD_STATIC OFF)
set(GLFW_LIBRARY_TYPE "SHARED")

add_subdirectory(${PROJECT_DIR}/extern/glfw)
add_subdirectory(${PROJECT_DIR}/extern/glew)
add_subdirectory(${PROJECT_DIR}/extern/glm)

set(GLFW_DIR ${PROJECT_DIR}/extern/glfw)
set(GLEW_DIR ${PROJECT_DIR}/extern/glew)
set(GLEW_DIR ${PROJECT_DIR}/extern/glm)

set(GLFW_INCLUDE_DIRS ${GLFW_DIR}/include)
set(GLEW_INCLUDE_DIRS ${GLEW_DIR}/include)
set(GLM_INCLUDE_DIRS ${GLEW_DIR})

set(PROJECT_HDR
        ${PROJECT_DIR}/include/window.hpp
        ${PROJECT_DIR}/include/raw_model.hpp
        ${PROJECT_DIR}/include/loader.hpp
        ${PROJECT_DIR}/include/renderer.hpp
        ${PROJECT_DIR}/include/shader.hpp
        ${PROJECT_DIR}/include/math.hpp
        ${PROJECT_DIR}/include/particle.hpp
)

set(PROJECT_SRC
        ${PROJECT_DIR}/src/main.cpp
        ${PROJECT_DIR}/src/window.cpp
        ${PROJECT_DIR}/src/raw_model.cpp
        ${PROJECT_DIR}/src/loader.cpp
        ${PROJECT_DIR}/src/renderer.cpp
        ${PROJECT_DIR}/src/shader.cpp
        ${PROJECT_DIR}/src/math.cpp
        ${PROJECT_DIR}/src/particle.cpp
)

add_executable(crispr_simulator "")

target_sources(crispr_simulator
        PRIVATE
        ${PROJECT_SRC}
        PUBLIC
        ${PROJECT_HDR}
)

target_include_directories(crispr_simulator
        PUBLIC
        ${PROJECT_DIR}/include
        ${OPENCV_INCLUDE_DIRS}
        ${PROJECT_DIR}/build
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(crispr_simulator
        PUBLIC
        glfw
        libglew_shared
        glm
)
