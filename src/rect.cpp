#include "../include/internal/rect.hpp"

Rect::Rect(float x, float y, float w, float h) : x(x),
                                                 y(y),
                                                 w(w),
                                                 h(h) {
}

bool Rect::Contains(float x, float y) {
    if ((x >= this->x)&&(x <= this->x + this->w)) {   
        return ((y >= this->y) && (y <= this->y + this->h))
        ? true 
        : false;
    } else {
        return false;
    }
}

void Rect::DefineCenter(float x, float y) {
    this->x = x - (this->w / 2);
    this->y = y - (this->h / 2);
}

void Rect::DefineCenter(Vec2 box) {   
    DefineCenter(box.x, box.y);
}

Vec2 Rect::GetCenter() {   
    Vec2 center = Vec2(this->x + (this->w / 2), this->y + (this->h / 2));
    return center;
}