//
// Created by liamg on 2025-01-14.
//

#include "../include/ScreenManager.hpp"

#include "../../frogger_game/include/FroggerGame.hpp"
#include "../../snake_game/include/SnakeGame.hpp"
#include "../include/GameScreen.hpp"

core::ScreenManager::ScreenManager(Window* window, KeybindManager* keybindManager)
    : WindowScreen(window, keybindManager), _homeScreen(home_screen::HomeScreen{ window, keybindManager, this }) {
    _games.insert(std::pair{
        new snake_game::SnakeGame(window, keybindManager, this), std::string("Snake")
    });

    _games.insert(std::pair{
        new frogger_game::FroggerGame(window, keybindManager, this), std::string("Frogger")
    });
}

core::ScreenManager::~ScreenManager() {
    _games.erase(_games.begin(), _games.end());
}

core::Game* core::ScreenManager::getCurrentGame(int gameIndex) {
    if (gameIndex < 0 || gameIndex >= _games.size()) {
        std::cerr << "Game index out of bounds." << std::endl;

        _inGame = false;
        return nullptr;
    }

    auto it = _games.begin();
    std::advance(it, gameIndex);

    return it->first;
}


core::WindowScreen& core::ScreenManager::getCurrentScreen() {
    if (_currentScreen == nullptr || !_inGame)
        return _homeScreen;

    return *_currentScreen;
}

void core::ScreenManager::onUpdate() {
    getCurrentScreen().onUpdate();
}

void core::ScreenManager::onRender(sf::RenderTarget &target) {
    getCurrentScreen().onRender(target);
}

void core::ScreenManager::onKeyPressed(sf::Keyboard::Key key) {
    getCurrentScreen().onKeyPressed(key);
}

void core::ScreenManager::launchGame(int gameIndex) {
    if (getCurrentGame(gameIndex) == nullptr) {
        std::cerr << "Not a valid game index." << std::endl;
        return;
    }

    _currentScreen = new GameScreen(getCurrentGame(gameIndex)->createNewInstance(), window, keybindManager);
    _inGame = true;
}

void core::ScreenManager::exitGame() {
    _currentScreen = nullptr;
    _inGame = false;
}


std::map<core::Game*, std::string>& core::ScreenManager::getGames() {
    return _games;
}


