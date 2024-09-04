#include <SDL.h>
#include <iostream>

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