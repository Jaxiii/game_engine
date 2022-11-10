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
    if(Game::instance != nullptr) { 
        cout << "Game: Something's Wrong!" << endl;
    }
    else {
        Game::instance = this;
    }

    //Aqui também, será que eu modularizo tipo Game::SDL_Init
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        cout << "Game: SDL_Init Error -> Return != 0";
    } 

}