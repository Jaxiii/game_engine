#include "../include/internal/state.hpp"
#include "../include/internal/game_object.hpp"
#include "../include/internal/face.hpp"
#include "../include/internal/vec2.hpp"
#include "../include/internal/input_manager.hpp"
#include "../include/internal/camera.hpp"

State::State() : music(BACKGROUND_MUSIC_PATH),
                 quitRequested(false),
                 started(false)
{   
    music.Play(BACKGROUND_MUSIC_LOOPS);
        
    GameObject *background = new GameObject();
    
    Sprite *sprite = new Sprite(*background, BACKGROUND_SPRITE_PATH);
    background->AddComponent((shared_ptr<Sprite>)sprite);

    CameraFollower *camera_follower = new CameraFollower(*background);
    background->AddComponent((shared_ptr<CameraFollower>)camera_follower);

    background->box.x = 0;
    background->box.y = 0;

    objectArray.emplace_back(background);

    GameObject *map = new GameObject();
    
    TileSet *tile_set = new TileSet(*map, TILE_HEIGHT, TILE_WIDTH, MAP_TILESET_PATH);

    TileMap *tile_map = new TileMap(*map, MAP_TILEMAP_PATH, tile_set);
    map->AddComponent((shared_ptr<TileMap>)tile_map);

    map->box.x = 0;
    map->box.y = 0;

    objectArray.emplace_back(map);
    
    GameObject *alien = new GameObject();
    Alien *behaviour = new Alien(*alien, 4);
    alien->AddComponent((shared_ptr<Alien>)behaviour);

    alien->box.x = 512;
    alien->box.y = 300;

    objectArray.emplace_back(alien);
}


State::~State() {
    objectArray.clear();
}

void State::LoadAssets(){}

void State::Start() {
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

void State::Update(float delta_time){

    Camera::Update(delta_time);

    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested()))
    quitRequested = true;

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        objectArray[i]->Update(delta_time);
    }

    for (int i = (int)objectArray.size() - 1; i >= 0; --i) {
        if (objectArray[i]->IsDead()) objectArray.erase(objectArray.begin() + i);
    }

    SDL_Delay(delta_time);
}

void State::Render() {
    for (int i = 0; i != (int)objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

weak_ptr<GameObject>  State::AddObject(GameObject* game_object) {

    shared_ptr<GameObject> shared_game_object(game_object);

    objectArray.push_back(shared_game_object);

    if (started) shared_game_object->Start();

    weak_ptr<GameObject> weak_game_object(shared_game_object);

    return weak_game_object;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *game_object) {
    for (int i = 0; i < (int)objectArray.size(); i++) {
        if (game_object == objectArray[i].get()) {
            weak_ptr<GameObject> weak_game_object(objectArray[i]);
            return weak_game_object;
        }
    }
    weak_ptr<GameObject> empty_weak;
    return empty_weak;
}