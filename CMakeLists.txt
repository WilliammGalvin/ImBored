cmake_minimum_required(VERSION 3.28)
project(ImBored)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/SFML_mingw64/SFML-2.6.2/include")
set(SFML_DIR "C:/SFML_mingw64/SFML-2.6.2/lib/cmake/SFML")

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
        core/include/FontManager.hpp
        core/src/FontManager.cpp
        home_screen/include/HomeScreen.hpp
        home_screen/src/HomeScreen.cpp
        core/include/ScreenManager.hpp
        core/src/ScreenManager.cpp
        core/include/KeybindManager.hpp
        core/include/Keybind.hpp
        core/src/KeybindManager.cpp
        frogger_game/include/FroggerGame.hpp
        frogger_game/include/LaneTypes.hpp
        utils/include/RandomUtil.hpp
        utils/src/RandomUtil.cpp
        frogger_game/src/FroggerGame.cpp
        frogger_game/include/HazardManager.hpp
        frogger_game/include/Hazard.hpp
        core/include/GameScreen.hpp
        core/src/GameScreen.cpp
)

# Link SFML libraries
target_link_libraries(ImBored sfml-system sfml-window sfml-graphics)
