#include "../include/internal/minion.hpp"
#include "../include/internal/game.hpp"

Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component::Component(associated),
                                                                                                    alienCenter(alienCenter),
                                                                                                    arc(arcOffsetDeg) {
    Sprite* minion_sprite = new Sprite(associated, MINION_SPRITE_PATH);
    float scale = 1 + ((rand() % 50) / 100.0);
    minion_sprite->SetScale(scale, scale);
    associated.AddComponent((shared_ptr<Sprite>)minion_sprite);

    shared_ptr<GameObject> shared_alien = alienCenter.lock();
    if (shared_alien.get() != nullptr) {
        radius.x = (shared_alien->box.w / 2);
        radius.y = (shared_alien->box.h / 2);
    } else {   
        associated.RequestDelete();
    }
    radius.RotateDeg(arc);
    
    associated.angleDeg -= radius.ArgDeg();
}

void Minion::Update(float delta_time) {   
    float arcStep = delta_time * MINION_ANG_VEL;

    associated.angleDeg += arcStep;
    if (alienCenter.lock().get() != nullptr) {
        radius.RotateDeg(arcStep);
        Vec2 pos = radius + Vec2(alienCenter.lock()->box.x + alienCenter.lock()->box.w / 2, alienCenter.lock()->box.y + alienCenter.lock()->box.h / 2);
        associated.box.DefineCenter(pos.x, pos.y);
    } else {
        associated.RequestDelete();
    }
}

void Minion::Render() {}

void Minion::Shoot(Vec2 target) {
    Vec2 distance = target - Vec2(associated.box.x + (associated.box.w / 2), associated.box.y + (associated.box.h / 2));
    float angle = atan2(distance.y, distance.x);

    GameObject *bullet = new GameObject();
    Bullet *bullet_behaviour = new Bullet(*bullet, angle, MINION_BULLET_SPEED, MINION_BULLET_DAMAGE, distance.Magnitude(), MINION_BULLET_SPRITE_PATH);
    
    bullet->AddComponent((shared_ptr<Bullet>)bullet_behaviour);
    bullet->box.DefineCenter(associated.box.GetCenter());

    Game::GetInstance().GetState().AddObject(bullet);
}

bool Minion::Is(string type) {
    return (type == "Minion") ? true : false;
}
