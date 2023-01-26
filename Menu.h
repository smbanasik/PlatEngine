#ifndef MENU_H
#define MENU_H

// This class will have a texture for the menu, and a vector of buttons
// It also contains a texutre & cliprect for the buttons.
// The buttons use shared pointers for both of those, so you can replace the pointers with different addresses and the buttons will be fine
// The menu shall handle input handling for the buttons

#include <SDL.h>
#include <vector>
#include "Button.h"
#include "ButtonTextured.h"

// A menu is a strucuture that holds a group of buttons and provides ways to acces,
// modify, and display them as a group. Additionally, it handles event handling.

class Menu {
private:

    // Our own reference to the renderer, so we don't have to pass it to every function.
    static SDL_Renderer* menuRenderer;

    // Action function pointer. Takes in index of button, returns nothing
    void (*resultFuncPtr)(const int& index);

    // Position of our menu
    SDL_Point menuPos;
    // Position of our menu label, relative to view port
    SDL_Point labelPos;
    // Internal name
    std::string menuName;
    // Texture for the menu
    Texture menuTexture;
    // Texture for menu label
    Texture menuLabel;
    // Vector of buttons. Buttons will either be drawn or textured and casted
    std::vector<std::unique_ptr<Button>> menuButtons;

    // The assumption is that textures will be used, so these are to be 
    // initialized and passed to the buttons
    std::shared_ptr<Texture> buttonTexture;
    std::shared_ptr<SDL_Point> buttonClipRectDimensions;

protected:
    Menu();

public:

    // Constructor, function pointer MUST be declared here to prevent any potential screw ups.
    // numButtons can be an estimate, it's just for optimization purposes
    Menu(const std::string& menuName, void (*ptr)(const int& index), int numButtons);

    // Should the menu be rendered?
    bool menuIsRendered;
    // Menu label text
    std::string labelText;
    // Menu label color
    SDL_Color labelColor;

    // Sets a buttons texture to the menu's button texture
    void setButtonTexture(const unsigned int& index);

    // Sets a buttons clipRect, assumes a vertical spritesheet unless specified
    void setButtonClipRect(const unsigned int& index, const int& parameters = (ButtonTextured::ButtonParams::VERTICAL | ButtonTextured::ButtonParams::YCLIP));

    // Sets all buttons to have a texture & clipRect
    void setAllTexture();

    // Set position relative to viewport, to get a button's position,
    // Access it through getMenuButton
    void setButtonPos(const unsigned int& index, const int& x, const int& y);
    
    // Set the position of the button label
    void setLabelPos(const int& x, const int& y);

    // Getters for menu box info
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    // Load in a new texture for the menu's button texture
    // X = width, Y = height
    void loadButtonTexture(const std::string& path, const SDL_Point& clipRectDimensions);

    // Create a textured button and add it to the menu's storage
    // Uses the menu's stored texture and clipRect for buttons so set those first
    // X & Y values are relative to the viewport
    void createMenuButton(const std::string& buttonName, const int& x, const int& y, 
        const std::string&buttonLabel, const SDL_Color& labelColor,
        TTF_Font* font, Uint32 wrap = 0,
        const int& parameters = (ButtonTextured::ButtonParams::VERTICAL | ButtonTextured::ButtonParams::YCLIP));

    // Return a pointer to the button so it may be accessed and modified
    Button* getMenuButton(const unsigned int& index);

    // Adds button to menu, cannibalizes whatever is put into it.
    // Pointer put into it returns null
    void addMenuButton(std::unique_ptr<Button>& button);

    // Removes the button from the vector, returns it for further use
    std::unique_ptr<Button> removeMenuButton(const unsigned int& index);

    // Initialize a menu after calling initial constructor
    void initMenu(const int& x, const int& y, const std::string& menuTexturePath);

    // Initialize the label
    void initLabel(const int& x, const int& y, TTF_Font* font, const std::string& labelText,
        const SDL_Color& labelColor, const Uint32& wrap = 0);

    // Render the menu and buttons, utilizes a generated viewport for rendering
    void render();

    // Activate menu buttons
    void activateMenuButtons();

    // Deactivate menu buttons
    void deactivateMenuButtons();

    // Handle events for buttons
    // Bool if button was clicked and modifies index to button that was clicked
    bool handleButtonEvents(SDL_Event& buttonEvent, int& index);

    // Call the menu action function
    void callFuncPtr(const int& index);

    // Initializes buttons by handing the class the renderer
    static void initMenuClass(SDL_Renderer* renderer);

};

#endif