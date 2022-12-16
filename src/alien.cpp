#include "../include/internal/alien.hpp"
#include "../include/internal/input_manager.hpp"
#include "../include/internal/camera.hpp"
#include "../include/internal/vec2.hpp"
#include "../include/internal/game.hpp"

using namespace std;

Alien::Action::Action(ActionType type, float x, float y) : type(type),
                                                           pos(x, y) {
}

Alien::Alien(GameObject &associated, int nMinions) : Component::Component(associated),
                                                     hp(50),
                                                     nMinions(nMinions) {
    Sprite *alien_sprite = new Sprite(associated, ALIEN_SPRITE_PATH);
    associated.AddComponent((shared_ptr<Sprite>)alien_sprite);
}

void Alien::Start() {
    weak_ptr<GameObject> weak_alien = Game::GetInstance().GetState().GetObjectPtr(&associated);

    for (int i = 0; i < nMinions; i++) {
        GameObject *minion = new GameObject();
        Minion *minion_behaviour = new Minion(*minion, weak_alien, i * 360/nMinions);
        minion->AddComponent((shared_ptr<Minion>)minion_behaviour);

        weak_ptr<GameObject> weak_minion = Game::GetInstance().GetState().AddObject(minion);
        minionArray.push_back(weak_minion);
    }
}

Alien::~Alien() {

    for (int i = minionArray.size() - 1; i >= 0; i--) {
        minionArray.erase(minionArray.begin() + i);
    }
}

void Alien::Update(float delta_time) {   
    associated.angleDeg += delta_time * ALIEN_ANG_VEL;
    
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT))
        taskQueue.emplace(Action(SHOOT, InputManager::GetInstance().GetMouseX(),
                                        InputManager::GetInstance().GetMouseY()));
    
    if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT))
        taskQueue.emplace(Action(MOVE, InputManager::GetInstance().GetMouseX(),
                                       InputManager::GetInstance().GetMouseY()));
    

    if (!taskQueue.empty()) {
        switch (taskQueue.front().type) {
            case MOVE: {
                float step = delta_time * ALIEN_VELOCITY;

                Vec2 distance = Vec2::Distance(Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2), taskQueue.front().pos);

                if (distance.Magnitude() > step) {
                    associated.box.x += step * cos(distance.Arg());
                    associated.box.y += step * sin(distance.Arg());
                } else {
                    associated.box.x = taskQueue.front().pos.x - associated.box.w / 2;
                    associated.box.y = taskQueue.front().pos.y - associated.box.h / 2;
                    taskQueue.pop();
                }
                break;
            } case SHOOT: {   
                shared_ptr<GameObject> minion;
                Vec2 target = taskQueue.front().pos;
                
                float distToTarget = numeric_limits<float>::max();

                if (!minionArray.empty()) {   
                    for (int i = 0; i < (int)minionArray.size(); i++) {   
                        if (!minionArray[i].expired()) {
                            shared_ptr<GameObject> temp_minion = minionArray[i].lock();
                            float closerMinionDistance = Vec2::Distance(temp_minion->box.GetCenter(), target).Magnitude();

                            if (closerMinionDistance < distToTarget) {
                                distToTarget = closerMinionDistance;
                                minion = temp_minion;
                            }
                        }
                    }
                }
                

                if (minion != nullptr) {   
                    Minion* realPtrMinion = (Minion *)minion->GetComponent("Minion").get();
                    realPtrMinion->Shoot(target); 
                } else {
                    cout << "ERRO: minion é um nullptr!" << endl;
                }

                taskQueue.pop();
                break;
            }
        }
    }
}

void Alien::Render() {}

bool Alien::Is(string type) {
    return type == "Alien" ? true : false;
}
