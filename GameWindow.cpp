#include "GameWindow.h"
#include <string>
#include <sstream>

// Constructor
GameWindow::GameWindow() {
    window = nullptr;
    std::string winName = "";
    isMouseFocused = false;
    isKeyboardFocused = false;
    isFullScreen = false;
    isMinimized = false;
    isResizing = false;
    width = 960;
    height = 540;
}

// Create the window
bool GameWindow::init(std::string name, int width, int height) {
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN /* | SDL_WINDOW_RESIZABLE*/);
    if (window != nullptr) {

        winName = name;
        isMouseFocused = true;
        isKeyboardFocused = true;
        this->width = width;
        this->height = height;

    }
    return window != nullptr;
}

// Creates a renderer for the window
SDL_Renderer* GameWindow::constructRenderer() {
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// Handle our window events
void GameWindow::handleEvent(SDL_Renderer* winRenderer, SDL_Event& winEvent) {

    // Check if it's a window event
    if (winEvent.type == SDL_WINDOWEVENT) {
        
        // We might have to update caption of the window
        bool updateCaption = false;

        switch (winEvent.window.event) {

            // Get new dimensions and change window
        /*
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            // Update our values
            width = winEvent.window.data1;
            height = winEvent.window.data2;
            isResizing = true;
            // Update our screen
            SDL_RenderPresent(winRenderer);
            break;
            */

            // Repaint when exposed
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(winRenderer);
            break;

            // Mouse has entered the window
        case SDL_WINDOWEVENT_ENTER:
            isMouseFocused = true;
            updateCaption = true;
            break;

            // Mouse left window
        case SDL_WINDOWEVENT_LEAVE:
            isMouseFocused = false;
            updateCaption = true;
            break;

            // Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            isKeyboardFocused = true;
            updateCaption = true;
            break;
            
            // Window does not have keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            isKeyboardFocused = false;
            updateCaption = true;
            break;

            // Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            isMinimized = true;
            break;
            
            // Window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
            isMinimized = false;
            break;

            // Window restored
        case SDL_WINDOWEVENT_RESTORED:
            isMinimized = false;
            break;
        } // End switch

        if (updateCaption == true) {

            std::stringstream caption;
            caption << winName << " - M: " << ((isMouseFocused) ? "On" : "Off") << " K: " << ((isKeyboardFocused) ? "On" : "Off");
            SDL_SetWindowTitle(window, caption.str().c_str());

        }
    }
    else if (winEvent.type == SDL_KEYDOWN && winEvent.key.keysym.sym == SDLK_F11) {

        if (isFullScreen == true) {
            SDL_SetWindowFullscreen(window, SDL_FALSE);
            isFullScreen = false;
        }
        else {
            SDL_SetWindowFullscreen(window, SDL_TRUE);
            isFullScreen = true;
            isMinimized = false;
        }

    }
}

// Free internals
void GameWindow::free() {
    SDL_DestroyWindow(window);
    window = nullptr;
}

// Getters
int GameWindow::getWidth() {
    return width;
}
int GameWindow::getHeight() {
    return height;
}
bool GameWindow::hasMouseFocus() {
    return isMouseFocused;
}
bool GameWindow::hasKeyboardFocus() {
    return isKeyboardFocused;
}
bool GameWindow::hasMinimized() {
    return isMinimized;
}
/*
bool GameWindow::hasResized() {
    return isResizing;
}

// Setter
void GameWindow::resetResized() {
    isResizing = false;
}*/