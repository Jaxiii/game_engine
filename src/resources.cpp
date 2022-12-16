#include "../include/internal/resources.hpp"

unordered_map<string, SDL_Texture *> Resources::imageTable;
unordered_map<string, Mix_Music *> Resources::musicTable;
unordered_map<string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(string file) {   
    SDL_Texture* texture;
    unordered_map<string, SDL_Texture*>::iterator it = Resources::imageTable.find(file);

    if (it == Resources::imageTable.end()) {   
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        Resources::imageTable.insert({file, texture});
        return texture;
    } else {
        return it->second;
    } 
}

void Resources::ClearImages() {   
    int i = 0;
    while (imageTable.begin() != imageTable.end()) {
        imageTable.erase(imageTable.begin()++);
        i++;
    }
}

Mix_Music *Resources::GetMusic(string file) {
    Mix_Music *music;
    unordered_map<string, Mix_Music *>::iterator it = Resources::musicTable.find(file);
    if (it == Resources::musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());
        Resources::musicTable.insert({file, music});
        return music;
    }
    return it->second;
}
    
void Resources::ClearMusics() {
    int i = 0;
    while (musicTable.begin() != musicTable.end()) {
        musicTable.erase(musicTable.begin()++);
        i++;
    }
}

Mix_Chunk *Resources::GetSound(string file) {
    Mix_Chunk *chunk;
    unordered_map<string, Mix_Chunk *>::iterator it = Resources::soundTable.find(file);
    if (it == Resources::soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());
        Resources::soundTable.insert({file, chunk});
        return chunk;
    }
    return it->second;
}

void Resources::ClearSounds() {
    int i = 0;
    while (soundTable.begin() != soundTable.end()) {
        soundTable.erase(soundTable.begin()++);
        i++;
    }
}