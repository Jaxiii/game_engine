#include "../include/internal/sprite.hpp"
#include "../include/internal/game.hpp"

using namespace std;


Sprite::Sprite(GameObject &associated) : Component::Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) SDL_DestroyTexture(texture);
}

int Sprite::QueryTexture() {
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)  {
        printf("Error - Texture Query"); 
        return -1;
    } else {
        return 0;
    }
    return -1;
}

void Sprite::Open(string file) {
    if (texture != nullptr) SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    texture == nullptr 
    ? printf("Error - Texture Load")
    : QueryTexture();
    
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x), int(associated.box.y), clipRect.w, clipRect.h};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) {
        cout << "Falha ao renderizar a textura: " << SDL_GetError() << endl;
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    bool isOpen;
    texture != nullptr ? isOpen = true : isOpen = false;
    return isOpen;
}

void Sprite::Update(float delta_time) {
}

bool Sprite::Is(string type) {
   return type == "Sprite" ? true : false;
}