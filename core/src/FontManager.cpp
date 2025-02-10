//
// Created by liamg on 2025-01-14.
//

#include "../include/FontManager.hpp"

#include <iostream>
#include <ostream>

core::FontManager::FontManager() {
    _font = sf::Font{};

    if (!_font.loadFromFile(_fontPath)) {
        std::cerr << "Failed to load font file: " << _fontPath << std::endl;
        return;
    }
}

sf::Font &core::FontManager::getFont() {
    return _font;
}

