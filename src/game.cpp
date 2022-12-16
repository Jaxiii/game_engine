#include <string>
#include <iostream>

#include "../include/internal/game.hpp"

#define WINDOW_FLAGS 0

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Bruno Sanguinetti - 180046063"
#define AUDIO_CHUNKSIZE 1024
#define AUDIO_FREQUENCY MIX_DEFAULT_FREQUENCY
#define AUDIO_FORMAT MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS MIX_DEFAULT_CHANNELS
#define SOUND_RESOLUTION 32

using namespace std;

Game *Game::instance = nullptr;

Game::Game(string title, int width, int height) {
    int SDL_ERROR;
    int IMG_ERROR;
    int MSC_ERROR;

    if (Game::instance != nullptr) {
        cout << "Error - Game instance not null";
    } else {
        Game::instance = this;
    }

    SDL_ERROR = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (SDL_ERROR != 0) {
        cout << "Error - SDL_Init";
    } else {
        IMG_ERROR = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        if (IMG_ERROR == 0) {
            cout << "Error - IMG_Init";
        } else {
            MSC_ERROR = Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3);
            if (MSC_ERROR == 0) {
                cout << "Error -Mix_Init";
            } else {
                Mix_OpenAudio(AUDIO_FREQUENCY, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE);
                Mix_AllocateChannels(SOUND_RESOLUTION);
                
                window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, WINDOW_FLAGS);
                if (window == nullptr) cout << "Error - SDL_CreateWindow" << endl;
                
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
                if (renderer == nullptr) cout << "Error - SDL_CreateRenderer" << endl;
                
            }
        }
    } 
    state = new State();
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game &Game::GetInstance(){
    if (Game::instance != nullptr) {
        return *Game::instance;
    } else {
        Game::instance = new Game(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
        return *Game::instance;
    }
}

State &Game::GetState() {
    return *state;
}

SDL_Renderer *Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while (state->QuitRequested() != true) {   
        state->Update(33);
        state->Render();
        SDL_RenderPresent(Game::GetInstance().GetRenderer());
    }
}