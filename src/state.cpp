#include "../include/internal/state.hpp"
#include "../include/internal/game_object.hpp"
#include "../include/internal/face.hpp"
#include "../include/internal/vec2.hpp"

#define PI 3.141592

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_SOUND_PATH "assets/audio/stageState.ogg"

#define ENEMY_SPRITE_PATH "assets/img/alien.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"



State::State() : bg_sprite(new Sprite(background, BACKGROUND_SPRITE_PATH)),
                 bg_sound(new Sound(background, BACKGROUND_SOUND_PATH)) {
    background.AddComponent((shared_ptr<Sprite>)bg_sprite);
    background.AddComponent((shared_ptr<Sound>)bg_sound);
    objectArray.emplace_back((shared_ptr<GameObject>)&background);
    quitRequested = false;
    Sound *sound = (Sound *)background.GetComponent("Sound").get();
    sound->Play();
}

State::~State() {
    objectArray.clear();
}

void State::Update(float delta_time){
    Input();

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        objectArray[i]->Update(delta_time);
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin() + i);
    }

    SDL_Delay(delta_time);
}

void State::Render() {
    for (int i = 0; i != (int)objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) quitRequested = true;
    
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = int(objectArray.size()) - 1; i >= 0; --i) {
                GameObject *go = (GameObject *)objectArray[i].get();
                if (go->box.Contains(float(mouseX), float(mouseY))) {
                    Face *face = (Face *)go->GetComponent("Face").get();
                    if (nullptr != face) {
                        int damage = rand() % 10 + 10;
                        cout << "Damage applied: " << damage << endl;
                        face->Damage(damage);
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            } else {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *enemy = new GameObject();
    
    Sprite *enemy_sprite = new Sprite(*enemy, ENEMY_SPRITE_PATH);
    enemy->AddComponent((shared_ptr<Sprite>)enemy_sprite);
    
    Sound *enemy_sound = new Sound(*enemy, ENEMY_SOUND_PATH);
    enemy->AddComponent((shared_ptr<Sound>)enemy_sound);
    
    Face *enemy_interface = new Face(*enemy);
    enemy->AddComponent((shared_ptr<Face>)enemy_interface);

    enemy->box.x = mouseX - (enemy_sprite->GetWidth()) / 2;
    enemy->box.y = mouseY - (enemy_sprite->GetHeight()) / 2;

    // Adicionando o inimigo no objectArray
    objectArray.emplace_back(enemy);
}
