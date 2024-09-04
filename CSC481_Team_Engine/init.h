#pragma once
#include "defs.h"
#include <SDL.h>
#include <iostream>

// Initialize SDL rendering window
void init(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height);

// Close SDL rendering window
void close(SDL_Window* window, SDL_Renderer* renderer);
