// This is to be a tile based platformer engine that serves as a base
// For more advanced projects in the future.

// Scope:
// Create a window ./
// Create a button class ./
// Create a menu system
// Create an options menu & config file
// Create an entity system
// Create 3 types of blocks: solid, stair, platform
// Create a basic level system & screen scrolling
// Create a player character with customizable input
// Create a physics system
// Create a saving system
// Create a level editor
// Recieve input and add on further

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "GameWindow.h"
#include "Button.h"
#include "ButtonDrawn.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void initLibs();
void close(GameWindow& window, SDL_Renderer* renderer);

int main(int argc, char* args[]) {
    
    initLibs();
    GameWindow platWin;
    SDL_Renderer* gameRenderer = nullptr;
    SDL_Event winEvent;

    // Temporary lol
    std::string gameName = "PlatWin";
    bool quitGame = false;

    platWin.init(gameName, SCREEN_WIDTH, SCREEN_HEIGHT);
    gameRenderer = platWin.constructRenderer();

    while (!quitGame) {

        while (SDL_PollEvent(&winEvent) != 0) {
            if (winEvent.type == SDL_QUIT) {
                quitGame = true;
            }

            platWin.handleEvent(gameRenderer, winEvent);
        }

        // Get mouse state
        int mX, mY;
        SDL_GetMouseState(&mX, &mY);

        // Draw background
        SDL_SetRenderDrawColor(gameRenderer, 0x11, 0x11, 0x11, 0xFF);
        SDL_RenderClear(gameRenderer);
        
        // Draw square on mouse
        SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0x00, 0xAA, 0xFF);
        SDL_Rect temp = { mX - 10, mY - 10, 20, 20 };
        SDL_RenderFillRect(gameRenderer, &temp);
        SDL_RenderPresent(gameRenderer);
    }

    close(platWin, gameRenderer);

    return 0;
}

void initLibs() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}

void close(GameWindow& window, SDL_Renderer* renderer) {

    window.free();
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}