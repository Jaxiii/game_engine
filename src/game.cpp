///////////////////////////////////////////////////////////////////                    
///  File:        game.cpp                                     ////
///  Description: Game class file                              ////
///  Rev:         A                                            ////
///  Created:     Fri. Nov 04, 2022, 18:48:14                  ////
///  Author:      Bruno Sanguinetti                            ////
///  mail:        brunoebarros@gmail.com                       ////
///                                                            ////
///                                                            ////
///  MIT LICENSE                                               ////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
                                                                
#include <iostream>                                             
#include <string>                                               
#include "../include/internal/game.hpp"                         
                                                                
using namespace std;                                            
                                                                
Game* Game::instance = nullptr;                                 
                                                                
Game::Game(string title, int width, int height) {               
                                                                

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        cout << "[#2] SDL_Init Error -> Return != 0";//////////////
    }///////////////////////////////////////////////////////////////

    else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        cout << "[#3] IMG_init Error -> Return != 0";
        } else {
            if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3) == 0) {
                cout << "[#3] Mix_init Error -> Return != 0";
            } else {
                Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);           ////
                Mix_AllocateChannels(32);                                                                       ////
                if (TTF_Init() != 0) {                                                                          //// . QUE ISSO?
                    cout << "[#4] TTF_init Error -> Return != 0" << endl;                                       //// .    
                } else {                                                                                        ////
                    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0); // <,<
                    if (window == nullptr) {                                                                    ////
                        cout << "[#5] Window Error -> nullptr" << endl;                                         ////  ^-^ Feião...
                    }
                    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                    if (renderer == nullptr) {
                        cout << "[#6] Renderer Error -> nullptr" << endl;
                    }
                }
            }
        }
    }
    state = new State();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

////////// Aqui em baixo ta BONITINHO :3 //////////////////////////
Game& Game::GetInstance() {
    if (Game::instance != nullptr) {
        return *Game::instance;
    } else {
        Game::instance = new Game("Bruno Sanguinetti - 180046063", 1024, 600);
        return *Game::instance;
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

void Game::Run() {
    state->LoadAssets();
    while (state->QuitRequested()!=true) {
        state->Update(0.0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}
