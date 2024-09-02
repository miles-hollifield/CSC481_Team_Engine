#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(int x, int y, int w, int h, float gravityValue)
    : velocityY(0), gravity(gravityValue) {
    rect = { x, y, w, h };
}

void PhysicsEntity::applyGravity(int screenHeight) {
    velocityY += gravity;
    rect.y += static_cast<int>(velocityY);

    // If the entity reaches the bottom of the screen, reset it to the top
    if (rect.y >= screenHeight) {
        resetPosition(screenHeight);
    }
}

void PhysicsEntity::resetPosition(int screenHeight) {
    rect.y = -rect.h;  // Start falling from above the screen
    velocityY = 0;  // Reset velocity for consistent falling
}
