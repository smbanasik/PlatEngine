#ifndef BUTTONDRAWN_H
#define BUTTONDRAWN_H

#include "Button.h"

class ButtonDrawn : public Button {

private:
    SDL_Rect buttonRect;
    SDL_Color buttonColors[3];

protected:

    // Used to separate the rendering of the colors from the other things
    void renderColors();

    // Used to separate the rendering of the box from other things
    void renderBox();

    // Used to separate rendering the label from everything else
    void renderLabel();

    ButtonDrawn();

public:

    ButtonDrawn(const std::string& buttonName);

    // Set the position of the buttons top left corner
    void setPosition(const int& x, const int& y);

    // Set the dimensions of the button
    void setDimensions(const int& w, const int& h);

    // Set Colors
    void setDefaultColor(const SDL_Color& buttonColor);
    void setHighlightColor(const SDL_Color& buttonColor);
    void setClickedColor(const SDL_Color& buttonColor);

    // Get the information about the box
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    // Render the button
    void render();

    // Assign values to a created button quickly
    void initButton(const SDL_Rect& buttonRect, const SDL_Color buttonColors[3],
        const std::string& labelText, const SDL_Color labelColor);

    // Handle any events
    void handleEvent(SDL_Event* bEvent);

};

#endif