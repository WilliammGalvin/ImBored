cmake_minimum_required(VERSION 3.28)
project(ImBored)

set(CMAKE_CXX_STANDARD 20)

# Set the SFML installation prefix (SFML installed via Homebrew)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(ImBored main.cpp
        core/include/Window.hpp
        core/src/Window.cpp
        core/include/WindowScreen.hpp
        core/include/Game.hpp
        snake_game/include/SnakeGame.hpp
        snake_game/src/SnakeGame.cpp
        snake_game/include/SnakeDir.hpp
        core/src/Game.cpp
        core/src/WindowScreen.cpp
        core/include/UpdateManager.hpp
        core/src/UpdateManager.cpp
        core/include/GameState.hpp
)

# Link SFML libraries
target_link_libraries(ImBored sfml-system sfml-window sfml-graphics)
