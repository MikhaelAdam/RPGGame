#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 1. Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // 2. Create a Window
    SDL_Window *window = SDL_CreateWindow("SDL3 Window", 800, 600, 0);
    if (!window) {
        SDL_Log("Couldn't create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 3. Create a 2D Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Couldn't create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. Main Game Loop
    bool is_running = true;
    SDL_Event event;

    while (is_running) {
        // Process events (like closing the window)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                is_running = false;
            }
        }

        // Set draw color to black and clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Swap the buffer to show the screen
        SDL_RenderPresent(renderer);
        
        // Small delay to reduce CPU usage
        SDL_Delay(16);
    }

    // 5. Clean Up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}