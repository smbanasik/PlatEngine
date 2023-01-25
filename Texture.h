#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

class Texture {

private:
    SDL_Texture* texture;

    // Dimensions
    int width;
    int height;

public:

    // Constructor
    Texture();

    // Destructor, just calls free
    ~Texture();

    // Load the texture from a particular file
    bool loadFromFile(SDL_Renderer* renderer,  const std::string& path);

    // Load texture with color key
    bool loadFromFile(SDL_Renderer* renderer, const std::string& path, const SDL_Color& colorKey);

    //Creates image from font string
    bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* Font, const std::string& textureText, const SDL_Color& textColor, const Uint32& wrap = 0);

    // Set the color
    void setColor(const SDL_Color& colorArr);

    //Set blending
    void setBlendMode(const SDL_BlendMode& blending);

    //Set alpha modulation
    void setAlpha(const Uint8& alpha);

    // Render the texture at a given point
    void render(SDL_Renderer* renderer, const int& x, const int& y, const SDL_Rect* clip = nullptr);

    // Frees memory related to the texture
    void free();

    // Getters
    int getWidth();
    int getHeight();
};
#endif