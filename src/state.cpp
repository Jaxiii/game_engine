//////////////////////////////////////////////////////////////////                    
//  File:        state.cpp                                    ////
//  Description: Game class file                              ////
//  Rev:         A                                            ////
//  Created:     Wed. Nov 10, 2022, 16:21:12                  ////
//  Author:      Bruno Sanguinetti                            ////
//  mail:        brunoebarros@gmail.com                       ////
//                                                            ////
//                                                            ////
//  MIT LICENSE                                               ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <iostream>     

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define ENEMY_SPRITE_PATH "assets/img/penguinface.png"
#define ENEMY_SOUND_PATH "assets/img/boom.wav"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP -1

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#define PI 3.141592

#include "../include/internal/SDL_include.hpp"
#include "../include/internal/state.hpp"
#include "../include/internal/face.hpp"
#include "../include/internal/vec2.hpp"

using namespace std;

State::State() : sprite(new Sprite(background, BACKGROUND_SPRITE_PATH)),
                 sound(new Sound(background, BACKGROUND_MUSIC_PATH)) {
    background.AddComponent((shared_ptr<Sprite>)sprite);
    background.AddComponent((shared_ptr<Sound>)sound);
    objectArray.emplace_back((shared_ptr<GameObject>)&background);
    quitRequested = false;
    Sound *soundFX = (Sound *)background.GetComponent("Sound").get();
    soundFX->Play();
}

void State::Update(float delta_time) {
    Input();

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        objectArray[i]->Update(delta_time);
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }

    SDL_Delay(delta_time);
}

void State::Render() {
    background.Render();
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {
        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = int(objectArray.size()) - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains(float(mouseX), float(mouseY)))
                {
                    Face *face = (Face *)go->GetComponent("Face").get();
                    if (nullptr != face)
                    {
                        int damage = std::rand() % 10 + 10;
                        std::cout << "Damage applied: " << damage << std::endl;
                        // Aplica dano
                        face->Damage(damage);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}
bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *enemy = new GameObject();

    // Criando o som do inimigo
    Sound *enemy_sound = new Sound(*enemy, ENEMY_SOUND_PATH);
    enemy->AddComponent((shared_ptr<Sound>)enemy_sound);
    // Criando a interface do inimigo
    Face *enemy_interface = new Face(*enemy);
    enemy->AddComponent((shared_ptr<Face>)enemy_interface);

    // Criando o sprite do inimigo
    Sprite *enemy_sprite = new Sprite(*enemy, ENEMY_SPRITE_PATH);
    enemy->AddComponent((shared_ptr<Sprite>)enemy_sprite);

    enemy->box.x = mouseX - (enemy_sprite->GetWidth()) / 2;
    enemy->box.y = mouseY - (enemy_sprite->GetHeight()) / 2;

    // Adicionando o inimigo no objectArray
    objectArray.emplace_back(enemy);
}
