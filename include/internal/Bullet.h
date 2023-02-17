#pragma once

#include <iostream>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "math.h"
#include "Vec2.h"
#include "Collider.h"

class Bullet : public Component
{
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, std::string shooter = "");
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);
    bool IsShooter(std::string shooter);

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
    // Bullet carrega agora uma string que idetifica seu atirador. 
    // Dessa forma a entidade que leva dano consegue evitar "friendlyfire".
    std::string shooter;
};