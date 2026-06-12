#include <SDL3/SDL.h>

class Game{
public:
    Game(int argc, char **argv);
    SDL_AppResult Init();
    SDL_AppResult HandleEvent(SDL_Event* event);
    SDL_AppResult Iterate();
    void Quit(SDL_AppResult result);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};