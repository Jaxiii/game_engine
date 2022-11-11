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

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "../include/internal/SDL_include.hpp"
#include "../include/internal/game.hpp"

using namespace std;

State::State() {
}

void State::Update(float delta_time) {
    if (SDL_QuitRequested()) quitRequested = true;
}

bool State::QuitRequested() {
    return quitRequested;
}