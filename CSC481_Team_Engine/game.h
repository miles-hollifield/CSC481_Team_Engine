#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "PhysicsEntity.h"

// SECTION 2: Game Class Definition
/**
 * The Game class encapsulates all game-specific logic, including handling
 * player input, updating game state, and rendering game objects.
 */
class Game {
public:
    /**
     * Constructor for Game.
     * Initializes game entities such as the platforms and the controllable shape.
     */
    Game();

    /**
     * Handles player input, specifically moving the controllable shape
     * left or right based on keyboard input.
     *
     * @param state A pointer to the current state of the keyboard.
     */
    void handleInput(const Uint8* state);

    /**
     * Updates the game state, applying gravity to the controllable shape,
     * checking for collisions, and updating the position of the moving platform.
     */
    void update();

    /**
     * Renders the game objects, including the platforms and the controllable shape.
     *
     * @param renderer The SDL_Renderer used to draw the objects on the screen.
     */
    void render(SDL_Renderer* renderer);

private:
    SDL_Rect platformRect;  // The static platform
    SDL_Rect movingPlatformRect;  // The moving platform
    PhysicsEntity controllableRect;  // The controllable shape
    int movingPlatformVelocity;  // Velocity of the moving platform
};

#endif
