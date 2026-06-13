#include "game.hpp"
#include "state/statebase.hpp"
#include "state/mainmenustate.hpp"

constexpr int frameCap = 60;

Game::Game(int argc, char **argv)
    : m_window(nullptr, &SDL_DestroyWindow),
      m_renderer(nullptr, &SDL_DestroyRenderer),
      m_ecs(),
      m_stateMachine(new StateMachine(m_ecs))
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
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();      // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(m_window.get(), m_renderer.get());
    ImGui_ImplSDLRenderer3_Init(m_renderer.get());

    m_stateMachine->changeState(new MainMenuState(m_stateMachine));
    return SDL_APP_CONTINUE;

}

SDL_AppResult Game::HandleEvent(SDL_Event* event){
    ImGui_ImplSDL3_ProcessEvent(event);
    m_stateMachine->handleEvent(*event);
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
    ImGui::Render();
    m_stateMachine->render( m_renderer.get());
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer.get());
    SDL_RenderPresent(m_renderer.get());
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::OnUpdate()
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>((NOW - LAST) * 1000) / SDL_GetPerformanceFrequency();
    if (deltaTime < (1000.0 / frameCap)) {
        SDL_Delay(static_cast<Uint32>((1000.0 / frameCap) - deltaTime));
        NOW = SDL_GetPerformanceCounter();
        deltaTime = static_cast<double>((NOW - LAST) * 1000) / SDL_GetPerformanceFrequency();
    }
    
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug Window");
    ImGui::Text("Delta Time: %.3f ms", deltaTime);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

    m_stateMachine->update(deltaTime);
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
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    m_stateMachine->changeState(nullptr);
    SDL_DestroyRenderer(m_renderer.get());
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}
