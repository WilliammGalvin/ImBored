//
// Created by liamg on 2025-01-14.
//

#ifndef RANDOMUTIL_HPP
#define RANDOMUTIL_HPP

#include <random>

namespace utils {

    class RandomUtil {
        static std::mt19937 gen;

    public:
        static int genRandomInt(int min, int max) {
            std::uniform_int_distribution<> dis(min, max);
            return dis(gen);
        }
    };

}

#endif //RANDOMUTIL_HPP
