#pragma once
#include "main.hpp"

class GlobalFunction
{
public:
    static GlobalFunction &getInstance();

    const unsigned int WIDTH = 1600, HEIGHT = 900;
    int rng(int from, int to);
    float rngF(float from, float to);
    float getLimit(const float& num, float min, float max);
};

#define gbFunc GlobalFunction::getInstance()