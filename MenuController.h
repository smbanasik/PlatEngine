#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

// Collection of functions
// Since each function needs functionality

#include <SDL.h>
#include <stack>
#include <memory>
#include "Menu.h"

namespace MenuController {

    // Does not own objects, just keeps track of order
    extern std::stack<Menu*> menuOrder;
    // Whatever this points to should be rendered
    extern Menu* activeMenu;

    // Deactivate current menu, add a menu to the stack, make it the activeMenu, activate it
    void addMenu(Menu* addedMenu);
    // Deactivate current menu, pop it from the stack, make most recent activeMenu, activate it
    void backMenu();
    // Render the activeMenu
    void renderActiveMenu();
    // Handle events of active menu
    void handleActiveMenuEvents(SDL_Event& buttonEvent);
}

#endif