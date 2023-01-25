#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL.h>
#include <string>
#include <memory>

class GameWindow {

private:
    // Our window pointer
    SDL_Window* window;

    // Window name
    std::string winName = "";

    // Our window dimensions
    int width = 960;
    int height = 540;

    // Window Focus
    bool isMouseFocused = false;
    bool isKeyboardFocused = false;
    bool isFullScreen = false;
    bool isMinimized = false;
    bool isResizing = false;

public:

    // Constructor
    GameWindow();

    // Create the window
    bool init(std::string name, int width, int height);

    // Creates a renderer for the window
    SDL_Renderer* constructRenderer();

    // Handle our window events
    void handleEvent(SDL_Renderer* winRenderer, SDL_Event& winEvent);

    // Free internals
    void free();

    // Getters
    int getWidth();
    int getHeight();
    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool hasMinimized();
    //bool hasResized();
    // Setter
    //void resetResized();
};


#endif