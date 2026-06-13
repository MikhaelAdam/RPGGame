#pragma once
#include "components/renderingcomponent.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cassert> 
#include <string>
#include <map>
#include <memory>	

#define MAX_TEXTURES 255

class TextureManager
{
	TextureManager() = default;

	static TextureManager* instance;

    std::map<std::string, std::unique_ptr<Sprite>> textureCache;
	public:
		Sprite* loadTexture(
			const char* filePath, 
			std::string name,  
			SDL_Renderer* renderer, 
			SDL_FRect &src , 
			SDL_FRect &dst , 
			float angle = 0,
			SDL_FPoint* center = nullptr,
			SDL_FlipMode flip = SDL_FLIP_NONE,
			SDL_ScaleMode scale = SDL_SCALEMODE_PIXELART);
		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		void clearCache();
		
		static TextureManager* getInstance();
		Sprite* getTexture(std::string name);
};

