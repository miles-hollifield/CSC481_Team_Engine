#include <SDL.h>
#include <iostream>
#include "PhysicsEntity.h"

// Function to initialize SDL, window, and renderer
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

// Function to close and clean up SDL
void close(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    if (!init(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        std::cerr << "Failed to initialize!" << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    // Section 2: Create entities
    SDL_Rect solidRect = { 300, 300, 100, 100 };  // Static solid shape
    SDL_Rect controllableRect = { 500, 500, 50, 50 };  // Controllable shape

    // Gravity applied to an entity for continuous falling
    PhysicsEntity fallingRect((SCREEN_WIDTH - 50) / 2, -50, 50, 50, 0.002f);

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Section 4: Handle keyboard inputs for controllableRect with boundary checks
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP] && controllableRect.y > 0) {
            controllableRect.y -= 2;
        }
        if (state[SDL_SCANCODE_DOWN] && controllableRect.y < SCREEN_HEIGHT - controllableRect.h) {
            controllableRect.y += 2;
        }
        if (state[SDL_SCANCODE_LEFT] && controllableRect.x > 0) {
            controllableRect.x -= 2;
        }
        if (state[SDL_SCANCODE_RIGHT] && controllableRect.x < SCREEN_WIDTH - controllableRect.w) {
            controllableRect.x += 2;
        }

        // Section 3: Apply gravity to fallingRect for continuous falling
        fallingRect.applyGravity(SCREEN_HEIGHT);

        // Section 5: Check collision between controllableRect and solidRect
        if (SDL_HasIntersection(&controllableRect, &solidRect)) {
            std::cout << "Collision detected!" << std::endl;
        }

        // Clear screen with blue background
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        // Render the solid static shape
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color
        SDL_RenderFillRect(renderer, &solidRect);

        // Render the controllable shape
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color
        SDL_RenderFillRect(renderer, &controllableRect);

        // Render the falling shape
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black color
        SDL_RenderFillRect(renderer, &fallingRect.rect);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    close(window, renderer);
    return 0;
}
