#pragma once

#define INCLUDE_SDL

#include <memory>
#include "state.hpp"
#include "SDL_include.hpp"

using namespace std;

class Game {

    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        float GetDeltaTime();

    private:
        static Game* instance;
        Game(string title, int width, int height);
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        int frameStart;
        float delta_time;
        void CalculateDeltaTime();

};
