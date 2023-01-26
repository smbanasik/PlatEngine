// TODO: Split the button in half. Textured Button, Drawn Button.
// Inheritence over composition should be okay here

#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Texture.h"

// A button is an object that may be clicked and sends a signal when clicked

class Button {
protected:

    // Constructor

    Button();

    // Internal name
    std::string buttonName;
    // Texture and text for the button label
    Texture label;

    // Check if highlighted
    bool isHighlighted;
    // Visual click, turned off when mouse visually stops clicking
    bool isClicked;
    // Frame independent click, is only turned off when action function has been resolved
    bool signalClick;

    // Used to separate the rendering of the colors from the other things
    virtual void renderColors() = 0;

    // Used to separate the rendering of the box from other things
    virtual void renderBox() = 0;

    // Used to separate rendering the label from everything else
    virtual void renderLabel() = 0;

    // Our own reference to the renderer, so we don't have to pass it to every function.
    static SDL_Renderer* buttonRender;

    // Given that this just has shared functionality for actual buttons
    // Why do we need to make objects of it?
    //Button();

public:

    // TODO: Need to figure out how to handle button shenanigans.
    // Buttons should always be stored so they're not creating textures on the fly.
    // Maybe whatever has buttons will store (pointers to) them? Think that's fine, better than a global button thing.
    //static std::vector<std::shared_ptr<Button>> bList;
    //static std::unordered_map<std::string, int> bMap;

    // External things will need to read and write to these vars, no reason to make private

    // Should the button be rendered and interactable?
    bool buttonIsRendered;
    // Button label text
    std::string labelText;
    // Button label color
    SDL_Color labelColor;

    // Whatever size the clip is, the order should be shown below.
    // Buttons with more functionality should be expanded into their own class
    // And utilize the protected functions
    enum ButtonColorOrder {
        DEFAULT = 0,
        HIGHLIGHTED = 1,
        CLICKED = 2
    };

    // Set the position of the buttons top left corner
    virtual void setPosition(const int& x, const int& y) = 0;

    // Get the information about the box
    virtual int getX()      = 0;
    virtual int getY()      = 0;
    virtual int getWidth()  = 0;
    virtual int getHeight() = 0;

    // Get if button has been clicked
    virtual bool getSignalClick();
    virtual void resetSignalClick();

    // Load the label texture
    void loadLabel(TTF_Font* font, const Uint32& wrap);

    // Render the button
    virtual void render() = 0;

    // Handle any events
    virtual void handleEvent(SDL_Event& bEvent, const SDL_Rect& viewPort = { 0, 0, 0, 0 });

    // Handles every button event.
    //static void buttonEvents(SDL_Event* bEvent);

    // Initializes buttons by handing the class the renderer
    static void initButtonClasses(SDL_Renderer* renderer);
};
#endif