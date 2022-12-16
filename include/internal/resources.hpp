#pragma once

#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include <iostream>
#include <unordered_map>
#include "SDL_include.hpp"
#include "game.hpp"

using namespace std;

class Resources {   

  public:
    static SDL_Texture *GetImage(string file);
    static Mix_Music *GetMusic(string file);
    static Mix_Chunk *GetSound(string file);
    static void ClearImages();
    static void ClearMusics();
    static void ClearSounds();

  private:
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;
    
};

#endif