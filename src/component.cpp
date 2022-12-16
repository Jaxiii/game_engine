#include "../include/internal/component.hpp"
#include "../include/internal/game_object.hpp"

Component::Component(GameObject& associated) : associated(associated) {
}

Component::~Component() {
}