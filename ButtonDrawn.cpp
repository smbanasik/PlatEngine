#include "ButtonDrawn.h"

// PROTECTED

// Used to separate the rendering of the colors from the other things
void ButtonDrawn::renderColors() {

    // Default color
    SDL_SetRenderDrawColor(buttonRender, buttonColors[ButtonColorOrder::DEFAULT].r, buttonColors[ButtonColorOrder::DEFAULT].g, buttonColors[ButtonColorOrder::DEFAULT].b, buttonColors[ButtonColorOrder::DEFAULT].a);

    // Highlight color
    if (isHighlighted == true)
        SDL_SetRenderDrawColor(buttonRender, buttonColors[ButtonColorOrder::HIGHLIGHTED].r, buttonColors[ButtonColorOrder::HIGHLIGHTED].g, buttonColors[ButtonColorOrder::HIGHLIGHTED].b, buttonColors[ButtonColorOrder::HIGHLIGHTED].a);

    // Clicked color
    if (isClicked == true)
        SDL_SetRenderDrawColor(buttonRender, buttonColors[ButtonColorOrder::CLICKED].r, buttonColors[ButtonColorOrder::CLICKED].g, buttonColors[ButtonColorOrder::CLICKED].b, buttonColors[ButtonColorOrder::CLICKED].a);

}

// Used to separate the rendering of the box from other things
void ButtonDrawn::renderBox() {
    // Draw Rect
    SDL_RenderFillRect(buttonRender, &buttonRect);
}

// Used to separate rendering the label from everything else
void ButtonDrawn::renderLabel() {
    // Draw text
    label.render(buttonRender, (buttonRect.x + (buttonRect.w - label.getWidth()) / 2), (2 + buttonRect.y + (buttonRect.h - label.getHeight()) / 2));
    //label.render(renderer, buttonRect.x, buttonRect.y);
}

ButtonDrawn::ButtonDrawn() {
    isHighlighted = false;
    isClicked = false;
    buttonIsRendered = false;
    labelText = "";
    labelColor = { 0xFF, 0xFF, 0xFF };
    buttonRect = { 0, 0, 0, 0 };
    buttonColors[0] = { 0, 0, 0, 0 };
    buttonColors[1] = { 0, 0, 0, 0 };
    buttonColors[2] = { 0, 0, 0, 0 };
}

// PUBLIC

ButtonDrawn::ButtonDrawn(const std::string& buttonName) {
    this->buttonName = buttonName;
}

// Set the position of the buttons top left corner
void ButtonDrawn::setPosition(const int& x, const int& y) {
    buttonRect.x = x;
    buttonRect.y = y;
}

// Set the dimensions of the button
void ButtonDrawn::setDimensions(const int& w, const int& h) {
    buttonRect.w = w;
    buttonRect.h = h;
}

// Set Colors
void ButtonDrawn::setDefaultColor(const SDL_Color& buttonColor) {
    this->buttonColors[ButtonColorOrder::DEFAULT] = buttonColor;
}
void ButtonDrawn::setHighlightColor(const SDL_Color& buttonColor) {
    this->buttonColors[ButtonColorOrder::HIGHLIGHTED] = buttonColor;
}
void ButtonDrawn::setClickedColor(const SDL_Color& buttonColor) {
    this->buttonColors[ButtonColorOrder::CLICKED] = buttonColor;
}

// Get the information about the box
int ButtonDrawn::getX() {
    return buttonRect.x;
}
int ButtonDrawn::getY() {
    return buttonRect.y;
}
int ButtonDrawn::getWidth() {
    return buttonRect.w;
}
int ButtonDrawn::getHeight() {
    return buttonRect.h;
}

// Render our button
void ButtonDrawn::render() {

    if (buttonIsRendered == false)
        return;

    renderColors();

    renderBox();

    renderLabel();
}

// Initializes buttons by handing the class the renderer
void ButtonDrawn::initButton(const SDL_Rect& buttonRect, const SDL_Color buttonColors[3],
    const std::string& labelText, const SDL_Color labelColor) {

    this->buttonRect = buttonRect;
    this->buttonColors[0] = buttonColors[0];
    this->buttonColors[1] = buttonColors[1];
    this->buttonColors[2] = buttonColors[2];
    this->labelText = labelText;
    this->labelColor = labelColor;
}

// Handle any events
void ButtonDrawn::handleEvent(SDL_Event& bEvent, const SDL_Rect& viewPort) {
    Button::handleEvent(bEvent, viewPort);
}

/*
void ButtonDrawn::handleEvent(SDL_Event& bEvent, const SDL_Rect& viewPort) {
    // Mouse event and button is rendered
    if ((bEvent.type == SDL_MOUSEMOTION || bEvent.type == SDL_MOUSEBUTTONDOWN || bEvent.type == SDL_MOUSEBUTTONUP)
        && buttonIsRendered == true) {
        
        // Grab mouse coords
        int mX, mY;
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
        if (mX < buttonRect.x) {
            isHighlighted = false;
        }
        // Mouse right of button
        else if (mX > buttonRect.x + this->getWidth()) {

            isHighlighted = false;
        }
        // Mouse above button
        else if (mY < buttonRect.y) {

            isHighlighted = false;
        }
        // Mouse below button
        else if (mY > buttonRect.y + this->getHeight()) {

            isHighlighted = false;
        }

        if (isHighlighted == true)
            return;

        if (bEvent.type == SDL_MOUSEBUTTONDOWN) {

            isClicked = true;
            signalClick = true;
        }

    }
}
*/