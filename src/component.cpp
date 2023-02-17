#include "../include/internal/Component.h"
#include "../include/internal/GameObject.h"

Component::Component(GameObject &associated) : associated(associated)
{}

Component::~Component()
{}

void Component::Start()
{}

void Component::NotifyCollision(GameObject& other)
{}