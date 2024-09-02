#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include <SDL.h>

class PhysicsEntity {
public:
    SDL_Rect rect;
    float velocityY;  // Vertical velocity
    float gravity;    // Gravity value

    PhysicsEntity(int x, int y, int w, int h, float gravityValue);

    // Apply gravity to the entity
    void applyGravity(int screenHeight);

    // Reset the entity position when it reaches the bottom
    void resetPosition(int screenHeight);
};

#endif
