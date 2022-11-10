//  File:        game.cc
//  Description: Game class file
//  Rev:         A
//  Created:     Fri. Nov 04, 2022, 18:48:14
//  Author:      Bruno Sanguinetti
//  mail:        brunoebarros@gmail.com
//
//
//  MIT LICENSE

#include <iostream>     

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "../include/internal/SDL_include.hpp"
#include "../include/internal/game.hpp"

using namespace std;

Game::Game(std::string title, int width, int height) {

    //Melhor colocar aqui ou criar um método de classe?
    //separar as inicializacoes e verificacoes por lib. 
    if(Game::instance != nullptr) {/////////////////////////////////
        cout << "[#1] Engine Error -> Instance nullptr" << endl;///
    }///////////////////////////////////////////////////////////////
    else {//////////////////////////////////////////////////////////
        Game::instance = this;//////////////////////////////////////
    }///////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //Aqui também, será que eu modularizo tipo Game::SDL_Init
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        cout << "[#2] SDL_Init Error -> Return != 0";//////////////
    }///////////////////////////////////////////////////////////////
    //// .          // .   .    ^^/// .   .///////// .            ./
    ///.    ///////// .   ////   .// .    .////////////   ///   ////
    ////--       ./// .  ////// . // .   .///////////// . ///   ////
    //ˆˆˆˆˆˆ    ./// .  //// .  //// .    ˆˆˆˆˆˆˆ|/////   ///   ////
    //.........../// ......... //// .............|// ............../
    ////////////////////////////////////////////////////////////////
    else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != 0) {
        cout << "[#3] IMG_init Error -> Return != 0";
        } else {
            if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) != 0) {
                cout << "[#3] Mix_init Error -> Return != 0";
            } else {
                Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
                Mix_AllocateChannels(32);
                if (TTF_Init != 0) {
                    cout << "[#4] TTF_init Error -> Return != 0" << endl;
                } else {
                    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
                    if (window == nullptr) {
                        cout << "[#5] Window Error -> nullptr" << endl;
                    }
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                    if (renderer == nullptr) {
                        cout << "[#6] Renderer Error -> nullptr" << endl;
                    }
                }
            }
        }
    }
}

Game& Game::GetInstance() {
    if (Game::instance != nullptr)
    {
        return *Game::instance;
    }
    else
    {
        Game::instance = new Game("Game", 1024, 600);
        return *Game::instance;
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
}

SDL_Window* Game::SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags){
}

SDL_Renderer* Game::SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags) {
}

void Game::Run() {
   while (!state->QuitRequested()) {
   }
}
