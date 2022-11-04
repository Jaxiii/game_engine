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

#include "state.h"

class Game
{ 
    private:
        Game(std::string title, int width, int height);
};

class State;