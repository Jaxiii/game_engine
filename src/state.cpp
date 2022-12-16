#include "../include/internal/state.hpp"
#include "../include/internal/game_object.hpp"
#include "../include/internal/face.hpp"
#include "../include/internal/vec2.hpp"
#include "../include/internal/input_manager.hpp"
#include "../include/internal/camera.hpp"
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


State::State() : music(BACKGROUND_MUSIC_PATH),
                 quitRequested(false)
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

}


State::~State() {
    objectArray.clear();
}

void State::Update(float delta_time){

    Camera::Update(delta_time);

    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested()))
    quitRequested = true;
    

    if (InputManager::GetInstance().KeyPress(SPACEBAR_KEY)) {
        int mouseX = InputManager::GetInstance().GetMouseX();
        int mouseY = InputManager::GetInstance().GetMouseY();
        float rotation = -PI + PI * (rand() % 1001) / 500.0;

        Vec2 objPos = Vec2(200, 0).GetRotated(rotation) + Vec2(mouseX, mouseY);

        int new_x = (int)objPos.x - Camera::pos.x;
        int new_y = (int)objPos.y - Camera::pos.y;

        AddObject(new_x, new_y);
    }

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

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) quitRequested = true;
    
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            for (int i = int(objectArray.size()) - 1; i >= 0; --i) {
                GameObject *go = (GameObject *)objectArray[i].get();
                if (go->box.Contains(float(mouseX), float(mouseY))) {
                    Face *face = (Face *)go->GetComponent("Face").get();
                    if (nullptr != face) {
                        int damage = rand() % 10 + 10;
                        cout << "Damage on Target: " << damage << endl;
                        face->Damage(damage);
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            } else {
                Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *enemy = new GameObject();
    
    Sprite *enemy_sprite = new Sprite(*enemy, ENEMY_SPRITE_PATH);
    enemy->AddComponent((shared_ptr<Sprite>)enemy_sprite);
    
    Sound *enemy_sound = new Sound(*enemy, ENEMY_SOUND_PATH);
    enemy->AddComponent((shared_ptr<Sound>)enemy_sound);
    
    Face *enemy_interface = new Face(*enemy);
    enemy->AddComponent((shared_ptr<Face>)enemy_interface);

    enemy->box.x = mouseX - (enemy_sprite->GetWidth()) / 2;
    enemy->box.y = mouseY - (enemy_sprite->GetHeight()) / 2;

    objectArray.emplace_back(enemy);
}
