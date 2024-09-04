#include <SDL.h>
#include <iostream>
#include "game.h"
#include "init.cpp"

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
