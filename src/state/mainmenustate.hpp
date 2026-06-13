#pragma once
#include "statebase.hpp"
#include <SDL3/SDL.h>
#include <flecs.h>

class MainMenuState: public StateBase {
public:
    MainMenuState(flecs::world& ecs) : StateBase(), ecs(ecs) {};
    void enter() override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void exit() override;
private:
    flecs::world& ecs;
};