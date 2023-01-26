// This is to be a tile based platformer engine that serves as a base
// For more advanced projects in the future.

// Scope:
// Create a window ./
// Create a button class ./
// Create a menu system ./
// Create a main menu that can access the game or options ./
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
#include "ButtonTextured.h"
#include "Menu.h"
#include "MenuController.h"
#include "GameController.h"


int main(int argc, char* args[]) {
    
    GameController::initLibs();
    GameWindow platWin;
    SDL_Renderer* gameRenderer = nullptr;
    SDL_Event winEvent;

    platWin.init(GameController::gameName, GameController::screenResolution.x, GameController::screenResolution.y);
    gameRenderer = platWin.constructRenderer();

    GameController::initClasses(gameRenderer);

    GameController::gameLoop(platWin, gameRenderer, winEvent);

    GameController::close(platWin, gameRenderer);

    return 0;
}