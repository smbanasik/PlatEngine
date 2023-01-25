#include "Menu.h"
#include "ButtonDrawn.h"
#include <iostream>

// Protected constructor
Menu::Menu() {
    menuPos = { 0, 0 };
    menuName = "";
    menuIsRendered = false;
    labelText = "";
    labelColor = { 0xFF, 0xFF, 0xFF, 0xFF };
}

// Public constructor
Menu::Menu(const std::string& menuName, int numButtons) {
    
    this->menuName = menuName;
    menuButtons.reserve(numButtons);
}

// Return a pointer to the button so it may be accessed and modified
Button * Menu::getMenuButton(const unsigned int& index) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return nullptr;
    }
    return menuButtons[index].get();
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
    
    SDL_Point temp = clipRectDimensions;
    
    buttonTexture->loadFromFile(menuRenderer, path);
    this->buttonClipRectDimensions.reset(&temp);
}

// Create a button and add it to the menu's storage
// Uses the menu's stored texture and clipRect for buttons so set those first
// X & Y values are relative to the viewport
void Menu::createMenuButton(const std::string& buttonName, const int& x, const int& y, const int& parameters) {

    std::unique_ptr<ButtonTextured> temp = std::make_unique<ButtonTextured>(buttonName);
    temp->setPosition(x, y);
    temp->setTexture(buttonTexture);
    temp->setClipRectDimensions(buttonClipRectDimensions);
    temp->setButtonParams(parameters);
    menuButtons.emplace_back(temp);

}

// TODO: Test function, seems very scuffed
// Copies a button into the menu
void Menu::addMenuButton(Button* button) {

    ButtonTextured* tempTextured = dynamic_cast<ButtonTextured*> (button);

    if (tempTextured != nullptr) {
        menuButtons.emplace_back(std::make_unique<ButtonTextured>(tempTextured));
        return;
    }

    ButtonDrawn* tempDrawn = dynamic_cast<ButtonDrawn*>(button);

    if (tempTextured != nullptr)
        menuButtons.emplace_back(std::make_unique<ButtonDrawn>(tempTextured));

}

// Removes the button from the vector, returns it for further use
std::unique_ptr<Button> Menu::removeMenuButton(const unsigned int& index) {
    
    if (index > menuButtons.size()) {
        std::cout << "Error, index is out of bounds" << std::endl;
        return nullptr;
    }

    // Acquire ownership of vector element
    std::unique_ptr<Button> temp = std::make_unique<Button>(menuButtons[index].release());

    // Remove now empty unique pointer
    menuButtons.erase(menuButtons.begin() + index);

    return temp;
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

    menuTexture.render(menuRenderer, menuPos.x, menuPos.y);
    menuLabel.render(menuRenderer, labelPos.x, labelPos.y);

    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {

        (*it)->render();
    }

}

// Handle events for buttons
void Menu::handleButtonEvents(SDL_Event* buttonEvent) {

    for (auto it = menuButtons.begin(); it != menuButtons.end(); it++) {
        
        (*it)->handleEvent(buttonEvent);
    }

}

// Initializes buttons by handing the class the renderer
void Menu::initMenuClass(SDL_Renderer* renderer) {
    menuRenderer = renderer;
}