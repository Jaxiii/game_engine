#include <math.h>
#include "../include/internal/vec2.hpp"

Vec2::Vec2() {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::GetRotated(float theta) {   
    float x_((x * cos(theta)) - (y * sin(theta)));
    float y_((y * cos(theta)) + (x * sin(theta)));
    return Vec2(x_, y_);
}