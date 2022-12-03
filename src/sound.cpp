#include "../include/internal/sound.hpp"
#include "../include/internal/resources.hpp"

using namespace std;

Sound::Sound(GameObject &associated) : Component::Component(associated) {
    chunk = NULL;
}

Sound::Sound(GameObject &associated, string file) : Sound(associated) {
    Open(file.c_str());
}

Sound::~Sound() {
    Mix_FreeChunk(chunk);
}

void Sound::Play(int times) {
    int loops(times - 1);
    channel = Mix_PlayChannel(-1, chunk, loops);
    if (channel == -1) cout 
                        << "Error - Play Sound" 
                        << SDL_GetError() << endl;
}

void Sound::Stop() {
   if (chunk != NULL) Mix_HaltChannel(channel);
}

void Sound::Open(string file) {   
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == NULL) cout << "Error - Open Sound" << endl;
}

void Sound::Update(float dt){}

void Sound::Render() {}

bool Sound::Is(string type) {
    return type == "Sound" ? true : false;
}