#include "game.hpp"

Game::Game(int argc, char **argv)
    : m_window(nullptr, &SDL_DestroyWindow),
      m_renderer(nullptr, &SDL_DestroyRenderer)
{
}

SDL_AppResult Game::Init(){
    SDL_SetAppMetadata("RPG Game", "1.0.0", "com.mikhadams.rpggame");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
	    return sdl_error();
    }

    m_window.reset(SDL_CreateWindow("RPG Game", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN));
    if (!m_window) {
	    return sdl_error();
    }

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), NULL));
    if (!m_renderer.get())
    {
        return sdl_error();
    }

    if (!SDL_ShowWindow(m_window.get())) {
	    return sdl_error();
    }
    
    return SDL_APP_CONTINUE;

}

SDL_AppResult Game::HandleEvent(SDL_Event* event){
    	switch (event->type)
	{
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;

		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			if (event->window.windowID == SDL_GetWindowID(m_window.get())) {
				return SDL_APP_SUCCESS;
			}
			break;

		default:
			return SDL_APP_CONTINUE;
	}
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::OnRender()
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());

    SDL_RenderPresent(m_renderer.get());
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::OnUpdate()
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::Iterate()
{
    if (const auto result = OnUpdate(); result != SDL_APP_CONTINUE) return result;
    if (const auto result = OnRender(); result != SDL_APP_CONTINUE) return result;
    return SDL_APP_CONTINUE;
}

void Game::Quit(SDL_AppResult result)
{
    SDL_DestroyRenderer(m_renderer.get());
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}
