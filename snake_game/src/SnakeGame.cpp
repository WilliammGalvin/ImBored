//
// Created by Willam Galvin on 2025-01-11.
//

#include "../include/SnakeGame.hpp"

#include <cmath>

#include "../../utils/include/RandomUtil.hpp"
#include "../include/SnakeDir.hpp"

snake_game::SnakeGame::SnakeGame(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager)
    : Game(window, keybindManager, screenManager), _dir(DOWN) {

    const int midPos = static_cast<int>(std::floor(_gridDim / 2.0));
    initSegments(sf::Vector2i{ midPos, midPos });
}

void snake_game::SnakeGame::initSegments(const sf::Vector2i& startingPos) {
    for (int i = 0; i < _startingSegments; i++) {
        const auto offset = sf::Vector2i{ 0, -i };

        _segments.push_back(sf::Vector2i(
            startingPos + offset
        ));
    }
}

sf::Vector2f snake_game::SnakeGame::getGameSize() const {
    const float size = _tileSize * static_cast<float>(_gridDim);
    return sf::Vector2f{ size, size };
}

void snake_game::SnakeGame::renderGrid(sf::RenderTarget& target) {
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f{
        _tileSize, _tileSize
    });

    for (int y = 0; y < _gridDim; y++) {
        for (int x = 0; x < _gridDim; x++) {
            if ((x + y * _gridDim) % 2 == 0)
                tile.setFillColor(sf::Color{ 39, 174, 96 });
            else
                tile.setFillColor(sf::Color{ 46, 204, 113 });

            const auto tilePos = sf::Vector2f{
                static_cast<float>(x) * _tileSize,
                static_cast<float>(y) * _tileSize
            } + getGameOffset();

            tile.setPosition(tilePos);
            target.draw(tile);
        }
    }
}

void snake_game::SnakeGame::renderSnake(sf::RenderTarget &target) {
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color{ 0, 76, 255 });
    rect.setSize(sf::Vector2f{ _tileSize, _tileSize });

    for (auto& segment : _segments) {
        rect.setPosition(sf::Vector2f(segment) * _tileSize + getGameOffset());
        target.draw(rect);
    }
}

void snake_game::SnakeGame::renderApples(sf::RenderTarget &target) {
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color{ 255, 25, 25 });
    rect.setSize(sf::Vector2f{ _tileSize, _tileSize });

    for (auto& apple : _apples) {
        rect.setPosition(sf::Vector2f(apple) * _tileSize + getGameOffset());
        target.draw(rect);
    }
}

void snake_game::SnakeGame::renderUI(sf::RenderTarget &target) {
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


void snake_game::SnakeGame::onGameEnd() {
    _score = 0;
    _segments.clear();
    _apples.clear();
}


bool snake_game::SnakeGame::hasCollidedWithSelfOrWall() const {
    const sf::Vector2i* headSegment = &_segments[0];

    // Self
    for (int i = 0; i < _segments.size(); i++) {
        if (i == 0) continue;

        if (*headSegment == _segments[i])
            return true;
    }

    // Wall
    if (headSegment->x < 0 || headSegment->x >= _gridDim ||
        headSegment->y < 0 || headSegment->y >= _gridDim)
        return true;

    return false;
}

int snake_game::SnakeGame::hasCollidedWithApple(const sf::Vector2i& headPos) const {
    for (int i = 0; i < _apples.size(); i++) {
        if (_apples[i] == headPos)
            return i;
    }

    return -1;
}

sf::Vector2i snake_game::SnakeGame::getNewApplePos() const {
    auto pos = sf::Vector2i{
        utils::RandomUtil::genRandomInt(0, _gridDim - 1),
        utils::RandomUtil::genRandomInt(0, _gridDim - 1)
    };

    for (auto& segment : _segments) {
        if (segment == pos)
            return getNewApplePos();
    }

    return pos;
}


void snake_game::SnakeGame::checkAndAddApples() {
    if (_apples.size() >= _maxAppleCount) return;

    for (int i = 0; i < _maxAppleCount - _apples.size(); i++) {
        _apples.emplace_back(getNewApplePos());
    }
}

void snake_game::SnakeGame::onGameUpdate() {
    checkAndAddApples();

    sf::Vector2i nextPos{};
    for (int i = 0; i < _segments.size(); i++) {
        const auto currentPos = sf::Vector2i(_segments[i]);

        if (i == 0) {
            _segments[i] += snakeDirToVec2i(_dir);
            nextPos = currentPos;

            if (hasCollidedWithSelfOrWall()) {
                onGameEnd();
            }

            int appleIndex = hasCollidedWithApple(_segments[i]);

            if (appleIndex >= 0) {
                _apples.erase(_apples.begin() - appleIndex);
                _score++;
                _segments.emplace_back(nextPos);
            }

            continue;
        }

        _segments[i] = sf::Vector2i(nextPos);
        nextPos = currentPos;
    }
}

void snake_game::SnakeGame::onGameRender(sf::RenderTarget& target) {
    renderGrid(target);
    renderApples(target);
    renderSnake(target);
    renderUI(target);
}

void snake_game::SnakeGame::onKeyPressed(sf::Keyboard::Key key) {
    Game::onKeyPressed(key);

    if ((key == sf::Keyboard::W || key == sf::Keyboard::Up) && _dir != DOWN)
        _dir = UP;
    else if ((key == sf::Keyboard::S || key == sf::Keyboard::Down) && _dir != UP)
        _dir = DOWN;
    else if ((key == sf::Keyboard::A || key == sf::Keyboard::Left) && _dir != RIGHT)
        _dir = LEFT;
    else if ((key == sf::Keyboard::D || key == sf::Keyboard::Right) && _dir != LEFT)
        _dir = RIGHT;
}

core::Game* snake_game::SnakeGame::createNewInstance() const {
    return new SnakeGame(&getWindow(), &getKeybindManager(), getScreenManager());
}