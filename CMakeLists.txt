cmake_minimum_required(VERSION 3.5...3.10)

project(helium CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 3.4 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

message("${CMAKE_BUILD_TYPE}")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("Building debug")
add_compile_options(-D_DEBUG)
endif()

set(SOURCES source/main.cpp 
            source/He/Log.cpp 
            source/He/App/BaseWindow.cpp 
            source/He/App/GLFW3Window.cpp
            source/He/Graphics/GL/VertexBufferObject.cpp
            source/He/Graphics/GL/VertexArrayObject.cpp
        source/He/Graphics/GL/Shader.cpp
        source/He/Graphics/GL/ElementBufferObject.cpp
        source/He/Graphics/GL/Mesh.cpp
        "source/He/Core/World/Voxel.cpp"
        source/He/Core/World/Chunk.cpp
        source/He/Core/World/World.cpp
        source/He/Graphics/GL/Camera.cpp
        source/He/App/Input.cpp
)

include_directories(include)
add_executable(helium ${SOURCES})
target_link_libraries(helium 
    fmt::fmt
    glfw
    GLEW::GLEW
    glm::glm-header-only)

add_custom_command(TARGET helium PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:helium>/resources)
