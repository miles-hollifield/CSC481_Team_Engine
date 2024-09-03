#include "game.h"

// SECTION 2: Game Class Implementation
// Constructor: Initialize platforms and the controllable shape
Game::Game()
    : platformRect{ 0, 600, 600, 50 },  // Static platform
    movingPlatformRect{ 600, 800, 700, 50 },  // Moving platform
    controllableRect(500, 400, 50, 50, 0.01f),  // Controllable shape with gravity
    movingPlatformVelocity(1) {  // Initial velocity for the moving platform
}

// Handle player input to move the controllable shape
void Game::handleInput(const Uint8* state) {
    if (state[SDL_SCANCODE_LEFT] && controllableRect.rect.x > 0) {
        controllableRect.rect.x -= 2;  // Move left
    }
    if (state[SDL_SCANCODE_RIGHT] && controllableRect.rect.x < 1920 - controllableRect.rect.w) {
        controllableRect.rect.x += 2;  // Move right
    }
}

// Update the game state: apply gravity, check collisions, update platform positions
void Game::update() {
    controllableRect.applyGravity(1080);  // Apply gravity to controllable shape

    // Handle collisions with the static and moving platforms
    controllableRect.handleCollision(platformRect);
    controllableRect.handleCollision(movingPlatformRect);

    // Update the moving platform position and ensure it stays on screen
    movingPlatformRect.x += movingPlatformVelocity;
    if (movingPlatformRect.x <= 0 || movingPlatformRect.x >= 1920 - movingPlatformRect.w) {
        movingPlatformVelocity = -movingPlatformVelocity;  // Reverse direction when platform hits screen edge
    }
}

// Render the game objects: static platform, moving platform, and controllable shape
void Game::render(SDL_Renderer* renderer) {
    // Render the static platform (red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &platformRect);

    // Render the moving platform (cyan)
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &movingPlatformRect);

    // Render the controllable shape (green)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &controllableRect.rect);
}
