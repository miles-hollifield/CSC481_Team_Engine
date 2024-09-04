#include "main.h"


// SECTION 2: Main Function
int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // initialize sdl
    init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

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

        // SECTION 2: Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Clear screen with blue background
        SDL_RenderClear(renderer);

        game.run(renderer);

        SDL_RenderPresent(renderer);  // Present the updated screen
    }

    close(window, renderer);
    return 0;
}