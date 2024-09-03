#include <SDL.h>
#include <iostream>
#include "PhysicsEntity.h"

// SECTION 1: SDL Initialization
/**
 * Function to initialize SDL, create a window, and create a renderer.
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

    bool quit = false;
    SDL_Event e;

    // SECTION 2: Define Game Entities
    // Static platform that does not move
    SDL_Rect platformRect = { 0, 600, 600, 50 };  // Red platform

    // Moving platform that moves horizontally
    SDL_Rect movingPlatformRect = { 600, 800, 700, 50 };  // Cyan platform
    int movingPlatformVelocity = 1;  // Slow movement speed for the platform

    // Controllable shape with physics (gravity)
    PhysicsEntity controllableRect(500, SCREEN_HEIGHT / 2 - 50, 50, 50, 0.01f);  // Green shape

    // SECTION 4: Game Loop
    while (!quit) {
        // SECTION 4: Event Handling
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // SECTION 4: Handle Keyboard Inputs for Controllable Shape
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && controllableRect.rect.x > 0) {
            controllableRect.rect.x -= 2;  // Move left
        }
        if (state[SDL_SCANCODE_RIGHT] && controllableRect.rect.x < SCREEN_WIDTH - controllableRect.rect.w) {
            controllableRect.rect.x += 2;  // Move right
        }

        // SECTION 3: Apply Gravity to Controllable Shape
        controllableRect.applyGravity(SCREEN_HEIGHT);

        // SECTION 5: Collision Detection
        // Check and handle collision with the static platform (red)
        controllableRect.handleCollision(platformRect);

        // Check and handle collision with the moving platform (cyan)
        controllableRect.handleCollision(movingPlatformRect);

        // Update moving platform position and ensure it stays on screen
        movingPlatformRect.x += movingPlatformVelocity;
        if (movingPlatformRect.x <= 0 || movingPlatformRect.x >= SCREEN_WIDTH - movingPlatformRect.w) {
            movingPlatformVelocity = -movingPlatformVelocity;
        }

        // SECTION 2: Rendering
        // Clear screen with blue background
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        // Render the static platform (red)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &platformRect);

        // Render the moving platform (cyan)
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderFillRect(renderer, &movingPlatformRect);

        // Render the controllable shape (green)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &controllableRect.rect);

        // Present the updated screen
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    close(window, renderer);
    return 0;
}
