#include "../include/internal/sprite.hpp"
#include "../include/internal/game.hpp"

using namespace std;

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(string file) {
    texture = nullptr;
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

void Sprite::Render(int x, int y) {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x, y, GetWidth(), GetHeight()};
    
    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), 
                                  texture,
                                  &clipRect, 
                                  &dstLoc);

    if (RENDER_ERROR != 0) 
        cout << "Error - Texture Render: " 
             << SDL_GetError() 
             << endl;
    
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