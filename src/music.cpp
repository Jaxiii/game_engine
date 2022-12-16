#include <iostream>
#include "../include/internal/music.hpp"

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    Open(file);
}

Music::~Music()  {
    if (music != nullptr) StopAndFree();
}

void Music::StopAndFree() {
    Stop(1500);
    Mix_FreeMusic(music);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        cout << "Error - Music Play" << endl;
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr) cout << "Error - Music Open" << endl;
    
}

bool Music::IsOpen() {
    return music != nullptr 
        ? true 
        : false;
}
