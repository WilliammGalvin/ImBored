//
// Created by liamg on 2025-01-14.
//

#include "../include/RandomUtil.hpp"

namespace utils {

    std::random_device rand;
    std::mt19937 RandomUtil::gen(rand());

}