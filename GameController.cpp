#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "GameController.h"
#include "Menu.h"
#include "Button.h"
#include "MenuController.h"

namespace GameController {
    
    std::string gameName = "PlatEngine";
    // Options
    SDL_Point screenResolution = { 1280, 720 };
    bool useOSCursor = true; // SDL_ShowCursor(int toggle) combined with own cursor texture
    bool quitGame = false;

    // Initialize the libraries
    void initLibs() {
        
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            std::cout << "ERROR: Sdl has failed - " << SDL_GetError();
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == false)
            std::cout << "ERROR: IMG has failed - " << IMG_GetError();
        TTF_Init();
    }

    // Close out libraries
    void close(GameWindow& window, SDL_Renderer* renderer) {

        window.free();
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    void initFonts() {

        Fonts::fontTNR = TTF_OpenFont("Assets/Fonts/times.ttf", 16);

    }


    // Load textures
    void initMenus() {

        // Work pointer, assign as needed and perform operations
        Menu* menuWorkPtr;

        Menus::mainMenu = std::make_unique<Menu>("menuMain", &Menus::mainMenuFunctionality, 5);
        menuWorkPtr = Menus::mainMenu.get();
        menuWorkPtr->initMenu(100, 50, "Assets/Textures/Menu/menuMainTexture.png");
        menuWorkPtr->initLabel(50, 20, Fonts::fontTNR, "PLATFORM ENGINE IS A GO", { 0xFF, 0x00, 0x00, 0xFF });
        menuWorkPtr->loadButtonTexture("Assets/Textures/Button/buttonMainTexture.png", { 75, 25 });
        menuWorkPtr->createMenuButton("menuMainButtonNewGame", 15, 50, "Start new game!", { 0xFF, 0xFF, 0xFF }, Fonts::fontTNR);

        // MENU CONTROLLER
        MenuController::addMenu(menuWorkPtr);
    }

    // Initialize any classes
    void initClasses(SDL_Renderer* gameRenderer) {
        Button::initButtonClasses(gameRenderer);
        Menu::initMenuClass(gameRenderer);
        initFonts();
        initMenus();
    }

    // Game loop
    void gameLoop(GameWindow& window, SDL_Renderer* renderer, SDL_Event& winEvent) {
        
        while (!quitGame) {

            while (SDL_PollEvent(&winEvent) != 0) {
                if (winEvent.type == SDL_QUIT) {
                    quitGame = true;
                }

                window.handleEvent(renderer, winEvent);
                MenuController::handleActiveMenuEvents(winEvent);
            }

            // Get mouse state
            int mX, mY;
            SDL_GetMouseState(&mX, &mY);

            // Draw background
            SDL_Rect windowRect = { 0, 0, screenResolution.x, screenResolution.y };
            SDL_RenderSetViewport(renderer, &windowRect);
            SDL_SetRenderDrawColor(renderer, 0x33, 0x11, 0x11, 0xFF);
            SDL_RenderClear(renderer);

            // Draw menu stack
            MenuController::renderActiveMenu();

            // Draw square on mouse
            SDL_RenderSetViewport(renderer, &windowRect);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xAA, 0xFF);
            SDL_Rect temp = { mX - 10, mY - 10, 20, 20 };
            SDL_RenderFillRect(renderer, &temp);

            SDL_RenderPresent(renderer);
        }

    }

    namespace Fonts {

        TTF_Font* fontTNR;

    }

    namespace Menus {

        // Steps to making a menu!
        // Step 1 - Planning, figure out how many buttons, what they're going to do, etc.
        // Step 2 - The function, make a function that implements this, or get the skeleton down
        // Step 3 - The menu, now you can create the menu and assign the function to the menu


        // The actual menu's storing what we need
        std::unique_ptr<Menu> mainMenu;
        std::unique_ptr<Menu> optionsMenu;

        // Functionality for menus
        void mainMenuFunctionality(const int& buttonIndex) {

            // 4 Buttons:
            // Start game, load game, options, quit
            // Start game - takes you to level select menu
            // Load game - takes you to save storage menu
            // Options - Takes you to options menu
            // Level editor - Takes you to level menu
            // Quit - ends program
            switch (buttonIndex) {
            case 0:
                std::cout << "Starting new game!" << std::endl;
                break;
            case 1:
                std::cout << "Loading save menu!" << std::endl;
                break;
            case 2:
                std::cout << "Options!" << std::endl;
                break;
            case 3:
                std::cout << "Level editor!" << std::endl;
                break;
            case 4:
                std::cout << "Quitting!" << std::endl;
                break;
            }

        }



        void optionsMenuFunctionality(const int& buttonIndex) {

        }


    }

}