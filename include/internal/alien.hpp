#pragma once

#define ALIEN_SPRITE_PATH "assets/img/alien.png"
#define ALIEN_VELOCITY 150
#define ALIEN_ANG_VEL 2
#define MIN_DIST 5

#include <iostream>
#include <queue>
#include <math.h>
#include <limits>
#include "component.hpp"
#include "game_object.hpp"
#include "vec2.hpp"
#include "sprite.hpp"
#include "minion.hpp"
#include "rect.hpp"
#include "state.hpp"

using namespace std;

enum ActionType {
  MOVE,
  SHOOT
};

class Alien : public Component {
  public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(string type);

private:
  class Action {
    public:
      Action(ActionType type, float x, float y);
      ActionType type;
      Vec2 pos;
  };
  Vec2 speed;
  int hp;
  queue<Action> taskQueue;
  vector<weak_ptr<GameObject>> minionArray;
  int nMinions;
};