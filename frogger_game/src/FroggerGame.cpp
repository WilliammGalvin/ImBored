//
// Created by liamg on 2025-01-14.
//

#include "../include/FroggerGame.hpp"

#include <iostream>

#include "../../utils/include/RandomUtil.hpp"

frogger_game::FroggerGame::FroggerGame(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager)
    : Game(window, keybindManager, screenManager) {
    generateLaneTypes();
    generateTiles();
    spawnFrog();
}

void frogger_game::FroggerGame::generateLaneTypes() {
    _laneTypes[0] = END;
    _laneTypes[getTotalLaneCount() - 1] = START;

    int laneCount = 1;

    for (int i = 0; i < _hazardLanes; i++) {
        auto hazardType = static_cast<LaneTypes>(utils::RandomUtil::genRandomInt(1, 2));

        for (int j = 0; j < _hazardSize; j++) {
            _laneTypes[laneCount] = hazardType;
            laneCount++;
        }

        if (i < _hazardLanes - 1) {
            _laneTypes[laneCount] = SOLID;
            laneCount++;
        }
    }
}

void frogger_game::FroggerGame::generateTiles() {
    for (int y = 0; y < getTotalLaneCount(); y++) {
        std::vector<sf::Vector2i> row;

        for (int x = 0; x < _rowSize; x++) {
            row.emplace_back(x, y);
        }

        _tiles.push_back(row);
    }
}

void frogger_game::FroggerGame::spawnFrog() {
    _frogPos = sf::Vector2i{
        static_cast<int>(static_cast<float>(floor(_rowSize / 2.0))),
        getTotalLaneCount() - 1
    };
}

sf::Color frogger_game::FroggerGame::getColorFromLaneType(LaneTypes laneType) const {
    switch (laneType) {
        case WATER:
            return sf::Color{ 116, 185, 255 };
        case ROAD:
            return sf::Color{ 85, 85, 85 };
        default:
            return sf::Color{ 106, 176, 76 };
    }
}

void frogger_game::FroggerGame::renderTiles(sf::RenderTarget& target) {
    sf::RectangleShape rect;
    rect.setSize({
        static_cast<float>(_tileSize),
        static_cast<float>(_tileSize)
    });

    for (auto& row : _tiles) {
        for (auto& tile : row) {
            rect.setFillColor(getColorFromLaneType(
               _laneTypes[tile.y]
            ));

            rect.setPosition(sf::Vector2f{
                static_cast<float>(tile.x * _tileSize),
                static_cast<float>(tile.y * _tileSize)
            } + getGameOffset());

            target.draw(rect);
        }
    }
}

void frogger_game::FroggerGame::renderFrog(sf::RenderTarget& target) {
    sf::RectangleShape rect;
    rect.setSize({
        static_cast<float>(_tileSize),
        static_cast<float>(_tileSize)
    });

    rect.setFillColor(sf::Color::Green);
    rect.setPosition(sf::Vector2f{
        static_cast<float>(_frogPos.x * _tileSize),
        static_cast<float>(_frogPos.y * _tileSize)
    } + getGameOffset());

    target.draw(rect);
}

void frogger_game::FroggerGame::renderUI(sf::RenderTarget& target) {
    sf::Text text;
    text.setFont(getFont());
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);

    const float paddingBottom = 10.0f;

    text.setString("Score: " + std::to_string(_score));
    text.setPosition(sf::Vector2f{
        getGameOffset().x,
        getGameOffset().y - text.getGlobalBounds().height - paddingBottom
    });

    target.draw(text);
}

void frogger_game::FroggerGame::onGameUpdate() {}

void frogger_game::FroggerGame::onGameRender(sf::RenderTarget& target) {
    renderTiles(target);
    renderFrog(target);
    renderUI(target);
}

void frogger_game::FroggerGame::onKeyPressed(sf::Keyboard::Key key) {
    Game::onKeyPressed(key);

    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        _frogPos.y -= 1;

        if (_score < getTotalLaneCount() - _frogPos.y)
            _score++;
    }

    if ((key == sf::Keyboard::S || key == sf::Keyboard::Down) && _frogPos.y < getTotalLaneCount() - 1) {
        _frogPos.y += 1;
    }
}

int frogger_game::FroggerGame::getTotalLaneCount() const {
    return _hazardLanes * _hazardSize + (_hazardLanes - 1) + 2;
}

sf::Vector2f frogger_game::FroggerGame::getGameSize() const {
    return {
        static_cast<float>(_rowSize * _tileSize),
        static_cast<float>(getTotalLaneCount() * _tileSize)
    };
}

core::Game* frogger_game::FroggerGame::createNewInstance() const {
    return new FroggerGame(window, keybindManager, getScreenManager());
}
