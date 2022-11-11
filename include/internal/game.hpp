//  File:        game.h
//  Description: Game class header
//  Rev:         A
//  Created:     Fri. Nov 04, 2022, 18:48:14
//  Author:      Bruno Sanguinetti
//  mail:        brunoebarros@gmail.com
//
//
//  MIT LICENSE

#define SDL

#include <string>
#include <iostream>


#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.hpp"
#include "state.hpp"

using namespace std; 

class Game
{ 
    private:
        Game(string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
    
    public:
        ~Game();
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetState();
        void Run();
};