#include "Button.h"

#include <iostream>

// PROBLEM: Rendering labels using a vector is insanely weird.
// it works *perfectly* fine in some functions.
// It's not related to setLabel or the viewport,
// But instead whatever is going on in the functions.
// And it's not the order either, since that works just fine.

// SOLUTION: The labels fail because of how we're handling textures
// We use a raw pointer, when the vector reallocates, it performs a shallow copy
// meaning that the pointer is copied but not the things it references
// when it deletes the old material, the new pointer is now pointing to nothing.
// We fix this by storing shared pointers instead of the values

SDL_Renderer* Button::buttonRender = nullptr;

// Protected

Button::Button() {
    buttonName = "";
    isHighlighted = false;
    isClicked = false;
    buttonIsRendered = "";
    labelText = "";
    labelColor = { 0xFF, 0xFF, 0xFF };
}



// Handles every button event.
/*
void Button::buttonEvents(SDL_Event* bEvent) {

    // TODO: Optimize this. If the mouse event isn't in the view port, no need to check the buttons.

    // If the SDL event is a mouse event, go through every button and handle it's event.
    if (bEvent->type == SDL_MOUSEMOTION || bEvent->type == SDL_MOUSEBUTTONDOWN || bEvent->type == SDL_MOUSEBUTTONUP) {

        // Tried range loop, doesn't work. Unsure why. Perhaps i is it's own instance instead of an iterator?
        for (int i = 0; i < bList.size(); i++) {

            bList[i]->handleEvent(bEvent);
        }
    }
}*/

// Get if button has been clicked
bool Button::getSignalClick() {
    return signalClick;
}

void Button::resetSignalClick() {
    signalClick = 0;
}

// Load the label texture
void Button::loadLabel(TTF_Font* font, const Uint32& wrap) {
    label.loadFromRenderedText(buttonRender, font, labelText, labelColor, wrap);
}

// Handle any events
void Button::handleEvent(SDL_Event& bEvent, const SDL_Rect& viewPort) {
    // Mouse event and button is rendered
    if ((bEvent.type == SDL_MOUSEMOTION || bEvent.type == SDL_MOUSEBUTTONDOWN || bEvent.type == SDL_MOUSEBUTTONUP)
        && buttonIsRendered == true) {

        // Grab mouse coords
        int mX = 0, mY = 0;
        SDL_GetMouseState(&mX, &mY);
        
        // Math sanity check
        // To right of viewport start mX = 100 - 50 = 50
        // To left of viewport start mX = 49 - 50 = -1
        // If viewport is 0,0, there's no offset, uses screen cords.
        // If button has a viewport, scope is the viewport. No concern if mouse is off viewports right edge
        // Account for viewport
        mX = mX - viewPort.x;
        mY = mY - viewPort.y;

        // Reset vars
        isHighlighted = true;
        isClicked = false;

        // Mouse left of button
        if (mX < this->getX()) {
            isHighlighted = false;
        }
        // Mouse right of button
        else if (mX > this->getX() + this->getWidth()) {

            isHighlighted = false;
        }
        // Mouse above button
        else if (mY < this->getY()) {

            isHighlighted = false;
        }
        // Mouse below button
        else if (mY > this->getY() + this->getHeight()) {

            isHighlighted = false;
        }

        if (isHighlighted == false)
            return;

        if (bEvent.type == SDL_MOUSEBUTTONDOWN) {

            isClicked = true;
            signalClick = true;
        }

    }
}

void Button::initButtonClasses(SDL_Renderer* renderer) {
    buttonRender = renderer;
}
