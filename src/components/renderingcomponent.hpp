#pragma once
#include <SDL3/SDL.h>
#include <string>

typedef struct Sprite
{
	std::string name;
	SDL_Texture* texture;
	SDL_FRect srcRect;
	SDL_FRect dstRect;
	float angle;
	SDL_FPoint* center;
	SDL_FlipMode flip;
}Sprite;

typedef struct Priority{
	int priority;
} Priority;