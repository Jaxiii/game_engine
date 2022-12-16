#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>

class Vec2 {
public:
  float x, y;
  Vec2();
  Vec2(float x, float y);
  Vec2 GetRotated(float theta);
  Vec2 operator+(const Vec2 &other) const;
};

#endif