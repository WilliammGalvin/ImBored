//
// Created by liamg on 2025-01-14.
//

#ifndef KEYBINDMANAGER_HPP
#define KEYBINDMANAGER_HPP

#include <map>
#include <SFML/Window/Keyboard.hpp>

#include "Keybind.hpp"

namespace core {

    struct KeybindManager {
        std::map<Keybind, sf::Keyboard::Key> keyBinds{};
        KeybindManager();
    };

}

#endif //KEYBINDMANAGER_HPP
