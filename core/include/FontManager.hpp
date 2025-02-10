//
// Created by liamg on 2025-01-14.
//

#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP
#include <SFML/Graphics/Font.hpp>

namespace core {

    class FontManager {
        sf::Font _font{};

        const std::string _fontPath = "assets/fonts/PressStart2P-Regular.ttf";

    public:
        FontManager();
        sf::Font& getFont();
    };

}

#endif //FONTMANAGER_HPP
