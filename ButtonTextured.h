#ifndef BUTTONTEXTURED_H
#define BUTTONTEXTURED_H

#include "Button.h"

class ButtonTextured : public Button {
private:

    // X & Y position of button
    SDL_Point buttonPos;
    // Texture for button, shared ptr to reduce amount of times we'd need to create same texture
    std::shared_ptr<Texture> buttonTexture;
    // Determines dimensions of clipRect. x is width, y is height
    std::shared_ptr<SDL_Point> clipRectDimensions;
    // Button's clip rectangle
    SDL_Rect clipRect;
    // Format, LSB first: 1 bit - using clip, 1 bit - horizontal or vertical sprite sheet
    Uint8 buttonParams;

protected:

    // Determines what clipRect should be
    void renderColors();

    // Renders the texture
    void renderBox();

    // Renders just the label
    void renderLabel();

    ButtonTextured();

public:

    enum ButtonParams {
        NCLIP = 0,
        YCLIP = 1,
        HORIZONTAL = 0,
        VERTICAL = 2,
    };

    ButtonTextured(const std::string& buttonName);

    // Set the position of the buttons top left corner
    void setPosition(const int& x, const int& y);

    // Sets the texture of the button
    void setTexture(const std::shared_ptr<Texture>& buttonTexture);

    // Set the clip rectangle
    void setClipRectDimensions(const std::shared_ptr<SDL_Point>& buttonDimensions);

    // Set button parameters, utilize ButtonParams enum, use bit OR
    void setButtonParams(const int& parameters);

    // Get the information about the box
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    // Render the button
    void render();

    // Assign values to a created button quickly
    void initButton(const SDL_Point& buttonPos, const std::shared_ptr<Texture>& buttonTexture,
        const std::string& labelText, const SDL_Color labelColor, const Uint8& buttonParams = 0,
        const std::shared_ptr<SDL_Point> clipRectDimensions = nullptr);
    
    // Handle any events
    void handleEvent(SDL_Event& bEvent, const SDL_Rect& viewPort = { 0, 0, 0, 0 });
};

#endif