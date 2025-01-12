//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef SNAKEDIR_HPP
#define SNAKEDIR_HPP
#include <iostream>
#include <map>
#include <SFML/Graphics/CircleShape.hpp>

namespace snake_game {

    enum SnakeDir {
        UP, DOWN, LEFT, RIGHT
    };

    inline sf::Vector2i snakeDirToVec2i(const SnakeDir& dir) {
        static const std::map<SnakeDir, sf::Vector2i> dirMap = {
            { UP, sf::Vector2i{ 0, -1 } },
            { DOWN, sf::Vector2i{ 0, 1 } },
            { LEFT, sf::Vector2i{ -1, 0 } },
            { RIGHT, sf::Vector2i{ 1, 0 } }
        };

        auto it = dirMap.find(dir);
        if (it != dirMap.end())
            return it->second;

        std::cerr << "Direction pair not found." << std::endl;
        return sf::Vector2i{ 0, 0 };
    }

}

#endif //SNAKEDIR_HPP
