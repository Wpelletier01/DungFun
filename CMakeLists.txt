set(CMAKE_CXX_COMPILER "clang++")
cmake_minimum_required(VERSION 3.29)
project(DungFun)

set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Automatically find all source files in the src directory
# file(GLOB_RECURSE sources "src/libgame/**/*.cpp" "src/libgame/*.cpp")

# Automatically find all header files in the include/my_lib directory
# file(GLOB_RECURSE headers "include/libgame/**/*.h" "include/libgame/*.h" "include/**/*.hpp" )

# Required lib
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)


add_executable(DungFun main.cpp
        src/App.cpp
        src/AssetManager.cpp
        src/EntityManager.cpp
        src/Renderer.cpp
        include/libgame/Declaration.h
        include/libgame/Camera.h
        src/Camera.cpp
        include/libgame/system/System.h
        include/libgame/system/Collision.h
        src/system/Collision.cpp
        include/libgame/world/Tile.h
        src/world/Tile.cpp
        include/libgame/world/TileMap.h
        src/world/TileMap.cpp)

target_include_directories(DungFun PUBLIC include/libgame include/entt include/nlohmann ${SDL2_INCLUDE_DIRS})
target_link_libraries(DungFun ${SDL2_LIBRARIES} SDL2_image)

