#include "ButtonTextured.h"

// PROTECTED

// Used to separate the rendering of the colors from the other things
void ButtonTextured::renderColors() {

    // If we're not configured to do clipping, don't
    if ((buttonParams & ButtonParams::YCLIP) == false)
        return;

    // X & Y Coords of clipRect
    int x = 0, y = 0;

    // If it's configured that we're stacking our sprite sheet vertically, we offset our y coord
    if (buttonParams & (ButtonParams::YCLIP | ButtonParams::VERTICAL)) {

        // Offset by 1
        if (isHighlighted == true)
            y = clipRectDimensions->y * ButtonColorOrder::HIGHLIGHTED;

        // Offset by 2
        if (isClicked == true)
            y = clipRectDimensions->y * ButtonColorOrder::CLICKED;

    }
    
    // If it's configured that we're stacking our sprite sheet horizontally, we offset our x coord
    if (buttonParams & (ButtonParams::YCLIP | ButtonParams::HORIZONTAL)) {

        // Offset by 1
        if (isHighlighted == true)
            x = clipRectDimensions->x * ButtonColorOrder::HIGHLIGHTED;

        // Offset by 2
        if (isClicked == true)
            x = clipRectDimensions->x * ButtonColorOrder::CLICKED;

    }


    // Determine clip rect
    clipRect = {x, y, clipRectDimensions->x, clipRectDimensions->y};

}

// Used to separate the rendering of the box from other things
void ButtonTextured::renderBox() {
    // Draw Rect
    if ((buttonParams & ButtonParams::YCLIP) == true) {
        buttonTexture->render(buttonRender, buttonPos.x, buttonPos.y, &clipRect);
    }
    else {
        buttonTexture->render(buttonRender, buttonPos.x, buttonPos.y);
    }
}

// Used to separate rendering the label from everything else
void ButtonTextured::renderLabel() {
    // Draw text
    label.render(buttonRender, (buttonPos.x + (this->getWidth() - label.getWidth()) / 2), (2 + buttonPos.y + (this->getHeight() - label.getHeight()) / 2));
    //label.render(renderer, buttonRect.x, buttonRect.y);
}

ButtonTextured::ButtonTextured() {
    isHighlighted = false;
    isClicked = false;
    buttonIsRendered = false;
    labelText = "";
    labelColor = { 0xFF, 0xFF, 0xFF };
    buttonPos = { 0, 0 };
    buttonTexture = nullptr;
    clipRectDimensions = nullptr;
    clipRect = { 0, 0, 0, 0 };
    buttonParams = 0;
}

// PUBLIC

ButtonTextured::ButtonTextured(const std::string& buttonName) {
    this->buttonName = buttonName;
}

// Set the position of the buttons top left corner
void ButtonTextured::setPosition(const int& x, const int& y) {
    buttonPos.x = x;
    buttonPos.y = y;
}

// Sets the texture of the button
void ButtonTextured::setTexture(const std::shared_ptr<Texture>& buttonTexture) {
    this->buttonTexture = buttonTexture;
}

// Set the clip rectangle
void ButtonTextured::setClipRectDimensions(const std::shared_ptr<SDL_Point>& buttonDimensions) {
    this->clipRectDimensions = buttonDimensions;
}

// Set button parameters, utilize ButtonParams enum, use bit OR
void ButtonTextured::setButtonParams(const int& parameters) {
    this->buttonParams = parameters;
}

// Get the information about the box

int ButtonTextured::getX() {
    return buttonPos.x;
}

int ButtonTextured::getY() {
    return buttonPos.y;
}

int ButtonTextured::getWidth() {

    if (clipRectDimensions != nullptr && (buttonParams &  ButtonParams::YCLIP) == false) {
        return buttonTexture->getWidth();
    }

    return clipRectDimensions->x;
    
}

int ButtonTextured::getHeight() {

    if (clipRectDimensions != nullptr && (buttonParams & ButtonParams::YCLIP) == false) {
        return buttonTexture->getHeight();
    }
    
    return clipRectDimensions->y;
    
}

// Render our button
void ButtonTextured::render() {

    if (buttonIsRendered == false)
        return;

    renderColors();

    renderBox();

    renderLabel();
}

// Initializes buttons by handing the class the renderer
void ButtonTextured::initButton(const SDL_Point& buttonPos, const std::shared_ptr<Texture>& buttonTexture,
    const std::string& labelText, const SDL_Color labelColor, const Uint8& buttonParams,
    const std::shared_ptr<SDL_Point> clipRectDimensions) {

    this->buttonPos = buttonPos;
    this->buttonTexture = buttonTexture;
    this->labelText = labelText;
    this->labelColor = labelColor;
    this->buttonParams = buttonParams;
    this->clipRectDimensions = clipRectDimensions;
}

void ButtonTextured::handleEvent(SDL_Event* bEvent) {
    // Mouse event and button is rendered
    if ((bEvent->type == SDL_MOUSEMOTION || bEvent->type == SDL_MOUSEBUTTONDOWN || bEvent->type == SDL_MOUSEBUTTONUP)
        && buttonIsRendered == true) {
        //int x, y;
        // Depending on the viewport that the button is in, get coords relative to the viewport
        //ViewPort::vpList[buttonViewPort].getVPMouseCoords(x, y);
        // Temp code for testing our getVPMouseCoords button
        //ViewPort temp = ViewPort::vpList[buttonViewPort];
        int mX, mY;
        SDL_GetMouseState(&mX, &mY);
        //std::cout << "VX: " << temp.getViewPort().x << " VY: " << temp.getViewPort().y << std::endl;
        //std::cout << "MX: " << mX << " MY: " << mY << std::endl;
        //std::cout << " X: " << x << "  Y: " << y << std::endl;

        //SDL_GetMouseState(&x, &y); // We need to add an offset depending on the viewport.
        isHighlighted = true;
        // Mouse left of button
        if (mX < buttonPos.x) {
            isHighlighted = false;
        }
        // Mouse right of button
        else if (mX > buttonPos.x + this->getWidth()) {

            isHighlighted = false;
        }
        // Mouse above button
        else if (mY < buttonPos.y) {

            isHighlighted = false;
        }
        // Mouse below button
        else if (mY > buttonPos.y + this->getHeight()) {

            isHighlighted = false;
        }

        if (isHighlighted == true) {

            if (bEvent->type == SDL_MOUSEBUTTONDOWN) {

                isClicked = true;
            }
            else {

                isClicked = false;
            }
        }
        else {

            isClicked = false;
        }

    }
}