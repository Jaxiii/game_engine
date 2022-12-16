#include "../include/internal/sprite.hpp"
#include "../include/internal/game.hpp"
#include "../include/internal/game_object.hpp"
#include "../include/internal/resources.hpp"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(string file) {
    
    texture = Resources::GetImage(file.c_str());

    if (texture == nullptr) {
        cout << "Error - Open Sprite" << endl;
    } else {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }

    SetClip(CLIP_START_X, CLIP_START_Y, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render() {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x), int(associated.box.y), clipRect.w, clipRect.h};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) cout << "Error - Render Texture " << SDL_GetError() << endl;
    
}

void Sprite::Render(int x, int y) {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x, y, clipRect.w, clipRect.h};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) cout << "Error - Render Texture " << SDL_GetError() << endl;

}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture == nullptr ? false : true;
}

void Sprite::Update(float delta_time) {}

bool Sprite::Is(string type) {
    return type == "Sprite" ? true : false;
}