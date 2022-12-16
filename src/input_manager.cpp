#include "../include/internal/input_manager.hpp"

InputManager &InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() : mouseState{false, false, false, false, false, false},
                               mouseUpdate{0, 0, 0, 0, 0, 0},
                               quitRequested(false),
                               updateCounter(0),
                               mouseX(0),
                               mouseY(0) {
}

InputManager::~InputManager(){}

void InputManager::Update() {
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;

    updateCounter ++;

    while (SDL_PollEvent(&event)) {   
        if (event.key.repeat != true) {   
            switch (event.type) {
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_QUIT:
                quitRequested = true;
                break;
            }
        }
    }
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::KeyPress(int key) {
    return ((keyState[key] == true) && (keyUpdate[key] == updateCounter))
    ? true
    : false;
}

bool InputManager::KeyRelease(int key) {
    return ((keyState[key] == false) && (keyUpdate[key] == updateCounter))
    ? true
    : false;
}

bool InputManager::IsKeyDown(int key) { 
    return (keyState[key] == true)
    ? true
    : false;
}

bool InputManager::MousePress(int button) {
    return ((mouseState[button] == true) && (mouseUpdate[button] == updateCounter))
    ? true
    : false;
}

bool InputManager::MouseRelease(int button) {
    return ((mouseState[button] == false) && (mouseUpdate[button] == updateCounter))
    ? true
    : false;
}

bool InputManager::IsMouseDown(int button) {
    return (mouseState[button] == true)
    ? true
    : false;
}