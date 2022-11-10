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

#include "../include/internal/state.hpp"

class Game
{ 
    private:
        Game(std::string title, int width, int height);
    
    public:
        Game* instance;
};

class State;