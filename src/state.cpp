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
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOP -1
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "../include/internal/SDL_include.hpp"
#include "../include/internal/state.hpp"

using namespace std;

State::State() : background(), music(){
    quitRequested = false;
}

void State::LoadAssets() {
    music.Open(BACKGROUND_MUSIC_PATH);
    music.Play(BACKGROUND_MUSIC_LOOP);
    background.Open(BACKGROUND_SPRITE_PATH);
}

void State::Update(float delta_time) {
    if (SDL_QuitRequested() == true) quitRequested = true;
}

void State::Render() {
    background.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}

