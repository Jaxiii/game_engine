//  File:        state.h
//  Description: State class header
//  Rev:         A
//  Created:     Fri. Nov 10, 2022, 19:31:14
//  Author:      Bruno Sanguinetti
//  mail:        brunoebarros@gmail.com
//
//
//  MIT LICENSE
class State;
#ifndef _STATE_H_
#define _STATE_H_

#include "game_object.hpp"
#include "sprite.hpp"
#include "music.hpp"
#include "sound.hpp"

using namespace std;

class GameObject;

class State { 

    private:
        bool quitRequested;
        GameObject background;
        Sprite *sprite;
        Sound *sound;
        void Input();
        void AddObject(int mouseX, int mouseY);
        vector<shared_ptr<GameObject>> objectArray;

    public:
        State();
        ~State();
        bool QuitRequested();
        void Update(float delta_time);
        void Render();

};

#endif