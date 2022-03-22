cmake_minimum_required(VERSION 3.20)
project(crispr_analysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS=ON)
set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(glew-cmake_BUILD_STATIC OFF)
set(GLFW_LIBRARY_TYPE "SHARED")

SET(BUILD_LIST "core,imgproc" CACHE STRING "" FORCE)
set(BUILD_SHARED_LIBS ON)

add_subdirectory(${PROJECT_DIR}/extern/glfw)
add_subdirectory(${PROJECT_DIR}/extern/glew)
add_subdirectory(${PROJECT_DIR}/extern/glm)
add_subdirectory(${PROJECT_DIR}/extern/opencv)

set(GLFW_DIR ${PROJECT_DIR}/extern/glfw)
set(GLEW_DIR ${PROJECT_DIR}/extern/glew)
set(GLEW_DIR ${PROJECT_DIR}/extern/glm)
set(PERLIN_DIR ${PROJECT_DIR}/extern/PerlinNoise)
set(IMGUI_DIR ${PROJECT_DIR}/extern/imgui)
set(OPENCV_DIR ${PROJECT_DIR}/extern/opencv)

set(GLFW_INCLUDE_DIRS ${GLFW_DIR}/include)
set(GLEW_INCLUDE_DIRS ${GLEW_DIR}/include)
set(GLM_INCLUDE_DIRS ${GLEW_DIR})
set(PERLIN_INCLUDE_DIRS ${PERLIN_DIR})
set(IMGUI_INCLUDE_DIRS 
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
set(OPENCV_INCLUDE_DIRS
        ${PROJECT_DIR}/build
        ${OPENCV_DIR}/include
        ${OPENCV_DIR}/modules/core/include
        ${OPENCV_DIR}/modules/imgcodecs/include
        ${OPENCV_DIR}/modules/highgui/include
        ${OPENCV_DIR}/modules/imgproc/include
)

set(IMGUI_SRC
        ${PROJECT_DIR}/extern/imgui/imgui.cpp
        ${PROJECT_DIR}/extern/imgui/imgui_demo.cpp
        ${PROJECT_DIR}/extern/imgui/imgui_draw.cpp
        ${PROJECT_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_DIR}/extern/imgui/imgui_tables.cpp
        ${PROJECT_DIR}/extern/imgui/imgui_widgets.cpp
)

set(PROJECT_HDR
        ${PROJECT_DIR}/include/window.hpp
        ${PROJECT_DIR}/include/raw_model.hpp
        ${PROJECT_DIR}/include/loader.hpp
        ${PROJECT_DIR}/include/renderer.hpp
        ${PROJECT_DIR}/include/shader.hpp
        ${PROJECT_DIR}/include/math.hpp
        ${PROJECT_DIR}/include/particle.hpp
        ${PROJECT_DIR}/include/simulator.hpp
        ${PROJECT_DIR}/include/frame_buffer.hpp
        ${PROJECT_DIR}/include/gui.hpp
        ${PROJECT_DIR}/include/analyser.hpp
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
        ${PROJECT_DIR}/src/simulator.cpp
        ${PROJECT_DIR}/src/frame_buffer.cpp
        ${PROJECT_DIR}/src/gui.cpp
        ${PROJECT_DIR}/src/analyser.cpp
        ${IMGUI_SRC}
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
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${PERLIN_INCLUDE_DIRS}
        ${IMGUI_INCLUDE_DIRS}
        ${OPENCV_INCLUDE_DIRS}
)

set(OPENCV_LIBS
        opencv_core
        opencv_imgproc
)

target_link_libraries(crispr_simulator
        PUBLIC
        glfw
        libglew_shared
        glm
        ${OPENCV_LIBS}
        ${CMAKE_DL_LIBS}
)
