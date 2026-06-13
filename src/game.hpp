#pragma once
#include "texturemanager.hpp"
#include "state/statemachine.hpp"
#include "components/renderingcomponent.hpp"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <ranges>
#include <array>
#include <source_location>
#include <flecs.h>

class Game{
public:
    Game(int argc, char **argv);
    
    SDL_AppResult Init();
    SDL_AppResult HandleEvent(SDL_Event* event);
    SDL_AppResult OnRender();
    SDL_AppResult OnUpdate();
    SDL_AppResult Iterate();

    void Quit(SDL_AppResult result);

private:
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    
    std::unique_ptr <SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	std::unique_ptr <SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    
    StateMachine *m_stateMachine;
    Sprite* sprite;
    flecs::world m_ecs;

    SDL_AppResult sdl_error(const std::source_location& loc = std::source_location::current()) {
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s:%d:%d: %s\n", loc.file_name(), loc.line(), loc.column(),
		SDL_GetError());
	return SDL_APP_FAILURE;
}
};