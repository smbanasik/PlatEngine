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

// Private

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

bool Button::getIsClicked() {
    return isClicked;
}

void Button::setLabel(TTF_Font* font, const Uint32& wrap) {
    label.loadFromRenderedText(buttonRender, font, labelText, labelColor, wrap);
}

void Button::initButtonClasses(SDL_Renderer* renderer) {
    buttonRender = renderer;
}
