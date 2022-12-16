#include "../include/internal/bullet.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component::Component(associated),
                                                                                                          distanceLeft(maxDistance),
                                                                                                          damage(damage) {
    Sprite* bullet_sprite = new Sprite(associated, sprite);
    associated.AddComponent((shared_ptr<Sprite>)bullet_sprite);
    this->speed.x = cos(angle) * speed;
    this->speed.y = sin(angle) * speed;
    associated.angleDeg = this->speed.ArgDeg();
}

void Bullet::Update(float delta_time) {   
    Vec2 step(speed.x * delta_time, speed.y * delta_time);
    associated.box.DefineCenter(associated.box.GetCenter() + step);

    distanceLeft -= step.Magnitude();

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return (type == "Bullet") ? true : false;
}

int Bullet::GetDamage() {
    return damage;
}


