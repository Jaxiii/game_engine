#pragma once

#include <iostream>
#include "component.hpp"
#include "game_object.hpp"

using namespace std;

class CameraFollower : public Component {

    public:
        CameraFollower(GameObject& associated);
        void Update(float delta_time);
        void Render();
        bool Is(string type);

};