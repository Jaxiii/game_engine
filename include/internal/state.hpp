//  File:        state.h
//  Description: State class header
//  Rev:         A
//  Created:     Fri. Nov 10, 2022, 19:31:14
//  Author:      Bruno Sanguinetti
//  mail:        brunoebarros@gmail.com
//
//
//  MIT LICENSE

class State { 

    private:
        bool quitRequested;

    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float delta_time);
        void Render();

};