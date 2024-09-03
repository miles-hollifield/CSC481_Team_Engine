#include "PhysicsEntity.h"

// Constructor: Initialize position, size, and gravity
PhysicsEntity::PhysicsEntity(int x, int y, int w, int h, float gravityValue)
    : velocityY(0), gravity(gravityValue) {
    rect = { x, y, w, h };
}

// Apply gravity to the entity
void PhysicsEntity::applyGravity(int screenHeight) {
    velocityY += gravity;  // Increase vertical velocity by gravity
    rect.y += static_cast<int>(velocityY);  // Update position based on velocity

    // Prevent the entity from falling through the bottom of the screen
    if (rect.y + rect.h > screenHeight) {
        rect.y = screenHeight - rect.h;  // Position the entity at the bottom edge
        velocityY = 0;  // Stop downward velocity
    }
}

// Handle collision detection with a platform
void PhysicsEntity::handleCollision(const SDL_Rect& platformRect) {
    if (SDL_HasIntersection(&rect, &platformRect)) {
        rect.y = platformRect.y - rect.h;  // Position the entity on top of the platform
        velocityY = 0;  // Stop downward velocity
    }
}
