//
// Created by Willam Galvin on 2025-01-11.
//

#include <iostream>
#include "../include/Game.hpp"

core::Game::Game(Window* window, std::chrono::milliseconds updateDelay)
    : WindowScreen(window), _updateManager(updateDelay), _gameState(GAME) {
    initUpdateStateMap();
    initRenderStateMap();
}

core::Game::Game(Window* window)
    : Game(window, std::chrono::milliseconds(200)) {}

core::Game::~Game() {
    delete _gameOffset;
}

void core::Game::initUpdateStateMap() {
    _updateStateMap = {
        { START, [this]() { onStartUpdate(); } },
        { GAME, [this]() { onGameUpdate(); } },
        { END, [this]() { onEndUpdate(); } },
    };
}

void core::Game::initRenderStateMap() {
    _renderStateMap = {
        { START, [this](sf::RenderTarget& t) { onStartRender(t); } },
        { GAME, [this](sf::RenderTarget& t) { onGameRender(t); } },
        { END, [this](sf::RenderTarget& t) { onEndRender(t); } }
    };
}

sf::Vector2f& core::Game::getGameOffset() {
    if (_gameOffset == nullptr) {
        _gameOffset = new sf::Vector2f{
            (static_cast<float>(window->getWindowSize().x) - getGameSize().x) / 2.0f,
            (static_cast<float>(window->getWindowSize().y) - getGameSize().y) / 2.0f
        };
    }

    return *_gameOffset;
}


void core::Game::onUpdate() {
    if (_updateManager.isCycleOver()) {
        auto it = _updateStateMap.find(_gameState);

        if (it != _updateStateMap.end()) {
            it->second();
        } else {
            std::cerr << "Couldn't find update function from state." << std::endl;
            return;
        }

        _updateManager.resetLastUpdate();
    }
}

void core::Game::onRender(sf::RenderTarget& target) {
    auto it = _renderStateMap.find(_gameState);

    if (it != _renderStateMap.end()) {
        it->second(target);
    } else {
        std::cerr << "Couldn't find render function from state." << std::endl;
    }
}



