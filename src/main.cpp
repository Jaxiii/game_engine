//////////////////////////////////////////////////////////////////                    
//  File:        main.cpp                                     ////
//  Description: main function fil                            ////
//  Rev:         A                                            ////
//  Created:     Fri. Nov 04, 2022, 18:48:14                  ////
//  Author:      Bruno Sanguinetti                            ////
//  mail:        brunoebarros@gmail.com                       ////
//                                                            ////
//                                                            ////
//  MIT LICENSE                                               ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "../include/internal/SDL_include.hpp"
#include "../include/internal/game.hpp"

int main(int argc, char** argv) {
    Game& game = Game::GetInstance();
    game.Run();
    return 0;
}