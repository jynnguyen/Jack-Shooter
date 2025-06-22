#include "GlobalFunc.hpp"

GlobalFunction &GlobalFunction::getInstance()
{
    static GlobalFunction instance;
    return instance;
}

int GlobalFunction::rng(int from, int to)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(from, to);
    return dist(gen);
}

float GlobalFunction::rngF(float from, float to)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(from, to);
    return dist(gen);
}

float GlobalFunction::getLimit(const float &num, float min, float max)
{
    if (num > max)
        return max;
    else if (num < min)
        return min;
    return num;
}
