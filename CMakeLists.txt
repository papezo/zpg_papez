cmake_minimum_required(VERSION 3.20)
project(zpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH
            "/opt/homebrew"
            "/usr/local"
    )
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(zpg
        src/main.cpp
        src/Application/Application.cpp
        src/Camera/Camera.cpp
        src/Graphics/DrawableObject.cpp
        src/Graphics/Model.cpp
        src/Graphics/Scene.cpp
        src/Graphics/ShaderProgram.cpp
        src/Miscs/SceneCreator.cpp
        src/Miscs/SolarSystemCreator.cpp
        src/Miscs/SolarSystemCreator.h
)

target_include_directories(zpg PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
)

target_compile_definitions(zpg PRIVATE GLFW_INCLUDE_NONE)

target_link_libraries(zpg PRIVATE glfw OpenGL::GL)