cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

project(Sandbox VERSION 0.1.5
                DESCRIPTION "OpenGL rendering engine"
                LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(ZLIB REQUIRED)
find_package(assimp REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Bullet REQUIRED)

### Foundation ###

file(GLOB FOUNDATION_SOURCE
    "Code/Foundation/App/*.cpp"
    "Code/Foundation/Core/Exception/*.cpp"
    "Code/Foundation/Core/*.cpp"
    "Code/Foundation/Game/Attributes/*.cpp"
    "Code/Foundation/Game/Scene/Camera/*.cpp"
    "Code/Foundation/Game/Scene/Light/*.cpp"
    "Code/Foundation/Game/Scene/Object/*.cpp"
    "Code/Foundation/Game/Scene/*.cpp"
    "Code/Foundation/Game/*.cpp"
    "Code/Foundation/Graphics/Renderers/*.cpp"
    "Code/Foundation/Graphics/Shaders/*.cpp"
    "Code/Foundation/Graphics/*.cpp"
    "Code/Foundation/IO/*.cpp"
    "Code/Foundation/Math/Physics/RigidBody/*.cpp"
    "Code/Foundation/Math/Physics/*.cpp"
    "Code/Foundation/Math/*.cpp"
    "Code/Foundation/Timing/*.cpp"
    "Code/Foundation/Util/Generators/*.cpp"
    "Code/Foundation/Util/Loaders/*.cpp"
    "Code/Foundation/Util/*.cpp"
)

add_library(Foundation SHARED ${FOUNDATION_SOURCE})
target_include_directories(Foundation PUBLIC Code/Foundation External ${BULLET_INCLUDE_DIRS})
target_link_libraries(Foundation OpenGL::GL GLEW::GLEW glfw glm::glm ZLIB::ZLIB assimp::assimp yaml-cpp ${BULLET_LIBRARIES})

### MeshExporter ###

file(GLOB MESH_EXPORTER_SOURCE
    "Code/MeshExporter/App/*.cpp"
    "Code/MeshExporter/Exporters/*.cpp"
    "Code/MeshExporter/MeshExporter.cpp"
)

add_executable(MeshExporter ${MESH_EXPORTER_SOURCE})
target_include_directories(MeshExporter PRIVATE Code/MeshExporter)
target_link_libraries(MeshExporter Foundation assimp::assimp)

### SandboxClient ###

file(GLOB SANDBOX_CLIENT_SOURCE
    "Code/SandboxClient/App/*.cpp"
    "Code/SandboxClient/Game/Managers/*.cpp"
    "Code/SandboxClient/Game/Scene/Object/*.cpp"
    "Code/SandboxClient/Game/Scene/*.cpp"
    "Code/SandboxClient/Game/*.cpp"
    "Code/SandboxClient/SandboxClient.cpp"
)

add_executable(SandboxClient ${SANDBOX_CLIENT_SOURCE})
target_include_directories(SandboxClient PRIVATE Code/SandboxClient)
target_link_libraries(SandboxClient Foundation)

### Test ###

file(GLOB TEST_SOURCE
    "Code/Test/App/*.cpp"
    "Code/Test/Game/*.cpp"
    "Code/Test/Test.cpp"
)

add_executable(Test ${TEST_SOURCE})
target_include_directories(Test PRIVATE Code/Test)
target_link_libraries(Test Foundation)
