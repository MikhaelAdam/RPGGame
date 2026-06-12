#define SDL_MAIN_USE_CALLBACKS 1  
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "game.hpp"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
	const auto app = new Game(argc, argv);
	*appstate = app;
    return app->Init();
}


SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	auto app = static_cast<Game*>(appstate);
    return app->HandleEvent(event);
}


SDL_AppResult SDL_AppIterate(void* appstate)
{
	auto app = static_cast<Game*>(appstate);
    return app->Iterate();
}


void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	auto app = static_cast<Game*>(appstate);
	app->Quit(result);
}
