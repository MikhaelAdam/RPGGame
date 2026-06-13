#pragma once

#include "statebase.hpp"
#include <SDL3/SDL.h>
#include <flecs.h>

class StateMachine {
public:
    void changeState(StateBase* newState) {
        if (currentState) {
            currentState->exit();
        }
        currentState = newState;
        if (currentState) {
            currentState->enter();
        }
    }

    void update( float deltaTime) {
        if (currentState) {
            currentState->update(deltaTime);
        }
    }

    void render(SDL_Renderer* renderer) {
        if (currentState) {
            currentState->render(renderer);
        }
    }

    void handleEvent(const SDL_Event& event) {
        if (currentState) {
            currentState->handleEvent(event);
        }
    }
    StateMachine(flecs::world& ecs) : ecs(ecs) {};
private:
    StateBase* currentState = nullptr;
    flecs::world& ecs;
};