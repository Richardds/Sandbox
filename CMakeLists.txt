cmake_minimum_required(VERSION 3.10)

project(Sandbox)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(gli REQUIRED)
find_package(assimp REQUIRED)

### Foundation ###

file(GLOB FOUNDATION_SOURCE
    "Code/Foundation/App/*.cpp"
    "Code/Foundation/Core/*.cpp"
    "Code/Foundation/Game/Attributes/*.cpp"
    "Code/Foundation/Game/Scene/*.cpp"
    "Code/Foundation/Game/*.cpp"
    "Code/Foundation/Graphics/Renderers/*.cpp"
    "Code/Foundation/Graphics/Shaders/*.cpp"
    "Code/Foundation/Graphics/*.cpp"
    "Code/Foundation/IO/*.cpp"
    "Code/Foundation/Math/*.cpp"
    "Code/Foundation/Timing/*.cpp"
    "Code/Foundation/Util/Generators/*.cpp"
    "Code/Foundation/Util/Loaders/*.cpp"
    "Code/Foundation/Util/*.cpp"
)

add_library(Foundation SHARED ${FOUNDATION_SOURCE})
set_target_properties(Foundation PROPERTIES CXX_STANDARD 17)
set_target_properties(Foundation PROPERTIES CXX_STANDARD_REQUIRED YES)
set_target_properties(Foundation PROPERTIES CXX_EXTENSIONS NO)
target_include_directories(Foundation PUBLIC Code/Foundation)

### MeshExporter ###

file(GLOB MESH_EXPORTER_SOURCE
    "Code/MeshExporter/App/*.cpp"
    "Code/MeshExporter/Exporters/*.cpp"
    "Code/MeshExporter/MeshExporter.cpp"
)

add_executable(MeshExporter ${MESH_EXPORTER_SOURCE})
set_target_properties(MeshExporter PROPERTIES CXX_STANDARD 17)
set_target_properties(MeshExporter PROPERTIES CXX_STANDARD_REQUIRED YES)
set_target_properties(MeshExporter PROPERTIES CXX_EXTENSIONS YES)
target_include_directories(MeshExporter PRIVATE Code/MeshExporter)
target_link_libraries(MeshExporter Foundation assimp glfw GLEW::GLEW OpenGL::GL)

### SandboxClient ###

file(GLOB SANDBOX_CLIENT_SOURCE
    "Code/SandboxClient/App/*.cpp"
    "Code/SandboxClient/Game/Managers/*.cpp"
    "Code/SandboxClient/Game/Scene/*.cpp"
    "Code/SandboxClient/Game/*.cpp"
    "Code/SandboxClient/SandboxClient.cpp"
)

message(STATUS ${SANDBOX_CLIENT_SOURCE})
add_executable(SandboxClient ${SANDBOX_CLIENT_SOURCE})
set_target_properties(SandboxClient PROPERTIES CXX_STANDARD 17)
set_target_properties(SandboxClient PROPERTIES CXX_STANDARD_REQUIRED YES)
set_target_properties(SandboxClient PROPERTIES CXX_EXTENSIONS YES)
target_include_directories(SandboxClient PRIVATE Code/SandboxClient)
target_link_libraries(SandboxClient Foundation assimp glfw GLEW::GLEW OpenGL::GL)
