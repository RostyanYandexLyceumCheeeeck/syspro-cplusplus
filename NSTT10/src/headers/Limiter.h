#pragma once
#include <iostream>
#include <stdexcept>
#include <string>


template<typename T, int U = -1>
class Limiter {
    static unsigned int alive;
    static const std::string message;
protected:
    Limiter() {
        if (alive + 1 > (unsigned int) U) {
            throw std::length_error(message);
        }
        alive++;
    }

    Limiter(const Limiter&) {
        if (alive + 1 > (unsigned int) U) {
            throw std::length_error(message);
        }
        alive++;
    }

    ~Limiter() {
        alive--;
    }
};

template<typename T, int U>
unsigned int Limiter<T, U>::alive = 0;

template<typename T, int U>
const std::string Limiter<T, U>::message = "The limit on creating instances of class has been reached!";
