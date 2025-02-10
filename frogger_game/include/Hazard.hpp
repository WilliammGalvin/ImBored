//
// Created by liamg on 2025-01-15.
//

#ifndef HAZARD_HPP
#define HAZARD_HPP
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

namespace frogger_game {

    struct Hazard {
        sf::Vector2i pos;

        Hazard(sf::Vector2i pos) : pos(pos) {}

        virtual void onUpdate() = 0;
        virtual void onRender(sf::RenderTarget& target) = 0;
    };

}

#endif //HAZARD_HPP
