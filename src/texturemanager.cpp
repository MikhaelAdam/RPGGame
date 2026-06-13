#include "texturemanager.hpp"


TextureManager* TextureManager::instance = nullptr;

Sprite* TextureManager::loadTexture(const char* filePath, 
    std::string name, 
    SDL_Renderer* renderer, 
    SDL_FRect& src, 
    SDL_FRect& dst, 
    float angle, 
    SDL_FPoint* center, 
	SDL_FlipMode flip,
    SDL_ScaleMode scale)
{
    assert(textureCache.size() >= MAX_TEXTURES, "Texture cache limit reached. Cannot load more textures.");

    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
    if (texture == nullptr)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return nullptr;
    }
	SDL_SetTextureScaleMode(texture, scale);
    auto sprite = std::make_unique<Sprite>();
	sprite->name = name;
    sprite->texture = texture;
    sprite->srcRect = &src ? src : SDL_FRect{ 0, 0, 0, 0 };
    sprite->dstRect = &dst ? dst : SDL_FRect{ 0, 0, 0, 0 };
	sprite->angle = angle;
	sprite->center = &center ? center : nullptr;
	sprite->flip = flip;

    auto result = textureCache.emplace(std::string(name), std::move(sprite));
    return result.first->second.get();
}

void TextureManager::clearCache()
{
    for (auto& pair : textureCache)
    {
        SDL_DestroyTexture(pair.second->texture);
    }
    textureCache.clear();
}

 TextureManager* TextureManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}

Sprite* TextureManager::getTexture(std::string name)
{
    auto it = textureCache.find(name);
    if (it != textureCache.end())
    {
        return it->second.get();
    }
    return nullptr;
}