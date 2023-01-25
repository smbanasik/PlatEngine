#include "Texture.h"
#include <iostream>

// Constructor
Texture::Texture() {
    texture = nullptr;
    width = 0;
    height = 0;
}

// Destructor, just calls free
Texture::~Texture() {
    // Deallocate
    free();
}

// Load the texture from a particular file
bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path) {
    free();

    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == nullptr) {
        std::cout << "Texture could not be loaded at path " << path << "\n" << IMG_GetError();
    }
    texture = newTexture;
    return texture != nullptr;
}

// Load texture with color key
bool Texture::loadFromFile(SDL_Renderer* renderer, const std::string& path, const SDL_Color& colorKey) {
    free();

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Surface cannot be loaded at path " << path << "\n" << IMG_GetError();
    }
    else {

        // Set color key and texture
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Texture could not be loaded at path " << path << "\n" << SDL_GetError();
        }
        else {

            width = loadedSurface->w;
            height = loadedSurface->h;

        }

        // Get rid of surface
        SDL_FreeSurface(loadedSurface);
    }

    texture = newTexture;
    return texture != nullptr;
}

//Creates image from font string
bool Texture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* Font, const std::string& textureText, const SDL_Color& textColor, const Uint32& wrap) {
    // Remove any previous texture
    free();

    // Render the text, could try blended or shaded
    SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(Font, textureText.c_str(), textColor, wrap);
    if (textSurface == nullptr) {
        std::cout << "Unable to render text! " << TTF_GetError();
    }
    else {

        // Convert to texture
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == nullptr) {
            std::cout << "Unable to make texture from text" << "\n" << SDL_GetError();
        }
        else {

            width = textSurface->w;
            height = textSurface->h;

        }
        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    return texture != nullptr;
}

// Set the color
void Texture::setColor(const SDL_Color& color) {

    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

//Set blending
void Texture::setBlendMode(const SDL_BlendMode& blending) {
    
    SDL_SetTextureBlendMode(texture, blending);
}

//Set alpha modulation
void Texture::setAlpha(const Uint8& alpha) {

    SDL_SetTextureAlphaMod(texture, alpha);
}

// Render the texture at a given point, renders the whole texture unless a clip is used
// The dimensions of the clip determines what pixels are captured in the source texture
void Texture::render(SDL_Renderer* renderer, const int& x, const int& y, const SDL_Rect* clip) {

    // Set rendering position & dimensions to whole texture
    SDL_Rect renderSpace = { x, y, width, height };
    // If we have a clip rectangle, change dimensions to the clip
    if (clip != nullptr) {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }
    // Render our texture to the renderspace, with the clip as reference
    SDL_RenderCopy(renderer, texture, clip, &renderSpace);

}

// Frees memory related to the texture
void Texture::free() {

    // Free texture if it exists
    if (texture != nullptr) {

        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

// Getters
int Texture::getWidth() {
    return width;
}
int Texture::getHeight() {
    return height;
}