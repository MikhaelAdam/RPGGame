#pragma once
#include <SDL3/SDL.h>

class StateBase{
public:
    virtual ~StateBase() = default;
    
    virtual void enter() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;
    virtual void exit() = 0;
};