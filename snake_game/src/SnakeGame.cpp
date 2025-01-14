//
// Created by Willam Galvin on 2025-01-11.
//

#include "../include/SnakeGame.hpp"

#include <random>
#include <__random/random_device.h>

#include "../include/SnakeDir.hpp"

snake_game::SnakeGame::SnakeGame(core::Window* window)
    : Game(window), _dir(DOWN) {

    const int midPos = static_cast<int>(floor(_gridDim / 2.0));
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

void snake_game::SnakeGame::onGameEnd() {
    score = 0;
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
    static std::random_device rand;
    static std::mt19937 gen(rand());
    static std::uniform_int_distribution<> dis(0, _gridDim - 1);

    auto pos = sf::Vector2i{
        dis(gen), dis(gen)
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
}

void snake_game::SnakeGame::onKeyPressed(sf::Keyboard::Key key) {
    if ((key == sf::Keyboard::W || key == sf::Keyboard::Up) && _dir != DOWN)
        _dir = UP;
    else if ((key == sf::Keyboard::S || key == sf::Keyboard::Down) && _dir != UP)
        _dir = DOWN;
    else if ((key == sf::Keyboard::A || key == sf::Keyboard::Left) && _dir != RIGHT)
        _dir = LEFT;
    else if ((key == sf::Keyboard::D || key == sf::Keyboard::Right) && _dir != LEFT)
        _dir = RIGHT;
}
