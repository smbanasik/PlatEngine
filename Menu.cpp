#include "Menu.h"
#include "ButtonDrawn.h"
#include <iostream>

SDL_Renderer* Menu::menuRenderer;

// Protected constructor
Menu::Menu() {
    menuPos = { 0, 0 };
    menuName = "";
    menuIsRendered = false;
    labelText = "";
    labelColor = { 0xFF, 0xFF, 0xFF, 0xFF };
}

// Public constructor
Menu::Menu(const std::string& menuName, void (*ptr)(const int& index), int numButtons) {
    this->menuName = menuName;
    this->resultFuncPtr = ptr;
    menuButtons.reserve(numButtons);
}

// Sets a buttons texture to the menu's button texture
void Menu::setButtonTexture(const unsigned int& index) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return;
    }
    
    ButtonTextured* textureButton = dynamic_cast<ButtonTextured*>(menuButtons[index].get());
    if (textureButton == nullptr)
        return;

    // Index is valid and button is a texture button
    textureButton->setTexture(buttonTexture);
}

// Sets a buttons clipRect, assumes a vertical spritesheet unless specified
void Menu::setButtonClipRect(const unsigned int& index, const int& parameters) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return;
    }

    ButtonTextured* textureButton = dynamic_cast<ButtonTextured*>(menuButtons[index].get());
    if (textureButton == nullptr)
        return;

    // Index is valid and button is a texture button
    textureButton->setClipRectDimensions(buttonClipRectDimensions);
    textureButton->setButtonParams(parameters);
}

// Sets all buttons to have a texture & clipRect
void Menu::setAllTexture() {

    ButtonTextured* textureButton;
    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {

        textureButton = dynamic_cast<ButtonTextured*>((*it).get());
        if (textureButton == nullptr)
            continue;

        // Button is a texture button
        textureButton->setTexture(buttonTexture);
        textureButton->setClipRectDimensions(buttonClipRectDimensions);
    }

}

// Set position relative to viewport, to get a button's position,
// Access it through getMenuButton
void Menu::setButtonPos(const unsigned int& index, const int& x, const int& y) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return;
    }

    menuButtons[index]->setPosition(x, y);
}

// Set the position of the button label
void Menu::setLabelPos(const int& x, const int& y) {

    labelPos.x = x;
    labelPos.y = y;

}

// Getters for menu box info
int Menu::getX() {
    return menuPos.x;
}

int Menu::getY() {
    return menuPos.y;
}

int Menu::getWidth() {
    return menuTexture.getWidth();
}

int Menu::getHeight() {
    return menuTexture.getHeight();
}

// Load in a new texture for the menu's button texture
// X = width, Y = height
void Menu::loadButtonTexture(const std::string& path, const SDL_Point& clipRectDimensions) {
    
    // Initialize buttonTexture with a new texture object
    buttonTexture = std::make_shared<Texture>();
    
    // Load file (and initialize the texture object)
    buttonTexture->loadFromFile(menuRenderer, path);
    this->buttonClipRectDimensions = std::make_shared<SDL_Point>(clipRectDimensions);
}

// Create a button and add it to the menu's storage
// Uses the menu's stored texture and clipRect for buttons so set those first
// X & Y values are relative to the viewport

void Menu::createMenuButton(const std::string& buttonName, const int& x, const int& y, const std::string&buttonLabel, const SDL_Color& labelColor, TTF_Font* font, Uint32 wrap, const int& parameters) {
    
    /*
    std::unique_ptr<ButtonTextured> temp = std::make_unique<ButtonTextured>(buttonName);
    temp->setPosition(x, y);
    temp->setTexture(buttonTexture);
    temp->setClipRectDimensions(buttonClipRectDimensions);
    temp->setButtonParams(parameters);
    // Working but has a copy, very cringe!
    menuButtons.push_back(std::move(temp));*/

    // Works, should have less copying since we build directly into the vector
    // We still make a pointer like last time
    menuButtons.emplace_back(std::make_unique<ButtonTextured>(buttonName));
    ButtonTextured* workPtr = dynamic_cast<ButtonTextured*>(menuButtons.back().get());
    // No need to check if null, we *just* inputted a textured button
    workPtr->setPosition(x, y);
    workPtr->setTexture(buttonTexture);
    workPtr->setClipRectDimensions(buttonClipRectDimensions);
    workPtr->labelText = buttonLabel;
    workPtr->labelColor = labelColor;
    workPtr->loadLabel(font, wrap);
    workPtr->setButtonParams(parameters);

    
}

// Return a pointer to the button so it may be accessed and modified
Button * Menu::getMenuButton(const unsigned int& index) {

    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return nullptr;
    }
    return menuButtons[index].get();
}


// Adds button to menu, cannibalizes whatever is put into it.
// Pointer put into it returns null
void Menu::addMenuButton(std::unique_ptr<Button>& button) {
      
    menuButtons.push_back(std::move(button));
}

// Removes the button from the vector, returns it for further use

std::unique_ptr<Button> Menu::removeMenuButton(const unsigned int& index) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return nullptr;
    }

    // Acquire ownership of vector element
    std::unique_ptr<Button> tempPtr;
    tempPtr.reset(menuButtons[index].release());
    
    // Remove now empty unique pointer
    menuButtons.erase(menuButtons.begin() + index);

    return tempPtr;
    
}

// Initialize a menu after calling initial constructor
void Menu::initMenu(const int& x, const int& y, const std::string& menuTexturePath) {

    menuPos.x = x;
    menuPos.y = y;
    this->menuTexture.loadFromFile(menuRenderer, menuTexturePath);
    
}

void Menu::initLabel(const int& x, const int& y, TTF_Font* font, const std::string& labelText,
    const SDL_Color& labelColor, const Uint32& wrap) {
    
    labelPos.x = x;
    labelPos.y = y;
    this->labelText = labelText;
    this->labelColor = labelColor;
    this->menuLabel.loadFromRenderedText(menuRenderer, font, labelText, labelColor, wrap);
}

// Render the menu and buttons, utilizes a generated viewport for rendering
void Menu::render() {

    SDL_Rect viewPortRect = { menuPos.x, menuPos.y, menuTexture.getWidth(), menuTexture.getHeight() };

    SDL_RenderSetViewport(menuRenderer, &viewPortRect);

    // Relative to viewport so start at 0, 0
    menuTexture.render(menuRenderer, 0, 0);

    menuLabel.render(menuRenderer, labelPos.x, labelPos.y);

    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {

        (*it)->render();
    }

}

// Activate menu buttons
void Menu::activateMenuButtons() {
    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {

        (*it)->buttonIsRendered = true;
    }
}

// Deactivate menu buttons
void Menu::deactivateMenuButtons() {
    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {

        (*it)->buttonIsRendered = false;
    }
}

// Handle events for buttons
// Bool if button was clicked and modifies index to button that was clicked
bool Menu::handleButtonEvents(SDL_Event& buttonEvent, int& index) {

    // Get a rectangle of the viewport
    SDL_Rect viewPortRect = { menuPos.x, menuPos.y, menuTexture.getWidth(), menuTexture.getHeight() };

    // Since we're modifying index, we don't want to modify it until we're sure
    // we need to. This increments with the iterator and if success, becomes index
    int tempIndex = 0;
    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++, tempIndex) {
        
        // Handle the button
        (*it)->handleEvent(buttonEvent, viewPortRect);

        // If it's been clicked, mark the index and exit successfully 
        if ((*it)->getSignalClick() == true) {
            index = tempIndex;
            return true;
        }
    }
    return false;
}

// Call the funcPtr
void Menu::callFuncPtr(const int& index) {
    if (resultFuncPtr != nullptr) {
        this->resultFuncPtr(index);
    }
    else {
        std::cout << "ERROR: funcPtr for menu " << this->menuName << " not found. Check where menu was constructed and ensure it is the correct address" << std::endl;
    }
    menuButtons[index]->resetSignalClick();
}

// Initializes buttons by handing the class the renderer
void Menu::initMenuClass(SDL_Renderer* renderer) {
    menuRenderer = renderer;
}