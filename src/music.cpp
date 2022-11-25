#include <iostream>
#include "../include/internal/music.hpp"

using namespace std;

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    Open(file);
}

Music::~Music() {
    if (music != nullptr) {
        Stop(1500);
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    music != nullptr ? Mix_PlayMusic(music, times) : printf("Error - Music Play");
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) cout << "Error - Music Load" << endl;
}

bool Music::IsOpen() {
    bool isOpen;
    music != nullptr ? isOpen = true : isOpen = false;
    return isOpen;
}