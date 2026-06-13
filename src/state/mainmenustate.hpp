#pragma once
#include "statebase.hpp"
#include "statemachine.hpp"
#include <SDL3/SDL.h>
#include <flecs.h>

class MainMenuState: public StateBase {
public:
    MainMenuState(const StateMachine* stateMachine ) : StateBase(), m_stateMachine(stateMachine) {};
    void enter() override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;
    void handleEvent(const SDL_Event& event) override;
    void exit() override;
private:
    const StateMachine* m_stateMachine;
    friend class StateMachine;
};