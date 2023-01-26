#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

// This contains values and functions that the game needs such as
// Should it be running, options, closing & initializing libraries,
// and so on. Stuff that you might find defined in main

#include <SDL.h>
#include <string>

#include "GameWindow.h"
#include "Menu.h"

namespace GameController {

    extern SDL_Point screenResolution;
    extern std::string gameName;
    extern bool quitGame;

    // Initialize the libraries
    void initLibs();

    // Close out libraries
    void close(GameWindow& window, SDL_Renderer* renderer);

    // Initialize any classes
    void initClasses(SDL_Renderer* gameRenderer);

    // Game loop
    void gameLoop(GameWindow& window, SDL_Renderer* renderer, SDL_Event& winEvent);

    namespace Fonts {

        extern TTF_Font* fontTNR;

    }

    namespace Menus {

        // Steps to making a menu!
        // Step 1 - Planning, figure out how many buttons, what they're going to do, etc.
        // Step 2 - The function, make a function that implements this, or get the skeleton down
        // Step 3 - The menu, now you can create the menu and assign the function to the menu


        // The actual menu's storing what we need
        extern std::unique_ptr<Menu> mainMenu;
        extern std::unique_ptr<Menu> optionsMenu;

        // Functionality for menus
        void mainMenuFunctionality(const int& buttonIndex);
        void OptionsMenuFunctionality(const int& buttonIndex);


    }

}

#endif