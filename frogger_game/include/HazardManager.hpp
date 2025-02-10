//
// Created by liamg on 2025-01-15.
//

#ifndef HAZARDMANAGER_HPP
#define HAZARDMANAGER_HPP
#include <map>
#include <vector>

#include "Hazard.hpp"

namespace frogger_game {

    class HazardManager {
        std::map<int, std::vector<Hazard*>> _hazardMap{};
    };

}

#endif //HAZARDMANAGER_HPP
