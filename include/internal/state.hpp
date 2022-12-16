#ifndef STATE_H
#define STATE_H

#pragma once

#define PI 3.141592

#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define MAP_TILESET_PATH "assets/img/tileset.png"
#define MAP_TILEMAP_PATH "assets/map/tileMap.txt"

#define BACKGROUND_SPRITE_PATH "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_SOUND_PATH "assets/audio/stageState.ogg"
#define BACKGROUND_MUSIC_LOOPS -1

#define ENEMY_SPRITE_PATH "assets/img/alien.png"
#define ENEMY_SOUND_PATH "assets/audio/boom.wav"


#include <vector>
#include <memory>
#include "sprite.hpp"
#include "sound.hpp"
#include "game_object.hpp"
#include "music.hpp"
#include "tile_map.hpp"
#include "tile_set.hpp"
#include "camera_follower.hpp"
#include "alien.hpp"

using namespace std;

class State {
  public:
    State();
    ~State();
    void LoadAssets();
    void Start();
    bool QuitRequested();
    void Update(float delta_time);
    void Render();
    weak_ptr<GameObject> AddObject(GameObject *game_object);
    weak_ptr<GameObject> GetObjectPtr(GameObject *game_object);
  
  private:
    Music music;
    bool quitRequested;
    bool started;
    void Input();
    vector<shared_ptr<GameObject>> objectArray;
};

#endif