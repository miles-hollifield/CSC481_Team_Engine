#include <SDL.h>
#include <iostream>
#include "game.h"

// SECTION 1: SDL Initialization
/**
 * Function to initialize SDL, create a window, and create a renderer.
 *
 * @param window Reference to the SDL_Window pointer.
 * @param renderer Reference to the SDL_Renderer pointer.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return true if initialization was successful, false otherwise.
 */
bool init(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL 2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

// SECTION 1: SDL Cleanup
/**
 * Function to clean up SDL resources (renderer and window).
 *
 * @param window SDL_Window pointer to the window.
 * @param renderer SDL_Renderer pointer to the renderer.
 */
void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// SECTION 2: Main Function
int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    // Initialize SDL and create window and renderer
    if (!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    Game game;  // Create an instance of the Game class

    bool quit = false;
    SDL_Event e;

    // SECTION 4: Game Loop
    while (!quit) {
        // SECTION 4: Event Handling
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Handle input
        const Uint8* state = SDL_GetKeyboardState(NULL);
        game.handleInput(state);

        // Update game state
        game.update();

        // SECTION 2: Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Clear screen with blue background
        SDL_RenderClear(renderer);

        game.render(renderer);  // Render game objects

        SDL_RenderPresent(renderer);  // Present the updated screen
    }

    close(window, renderer);
    return 0;
}
