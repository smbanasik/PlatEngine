#include "MenuController.h"

namespace MenuController {

    // Does not own objects, just keeps track of order
    std::stack<Menu*> menuOrder;
    // Whatever this points to should be rendered
    Menu* activeMenu;

    // Deactivate current menu, add a menu to the stack, make it the activeMenu, activate it
    void addMenu(Menu* addedMenu) {

        // If there's nothing in here, skip this
       if(menuOrder.size() != 0)
            activeMenu->deactivateMenuButtons();
        
        menuOrder.push(addedMenu);
        activeMenu = menuOrder.top();
        activeMenu->activateMenuButtons();
    }

    // Deactivate current menu, pop it from the stack, make most recent activeMenu, activate it
    void backMenu() {

        // If we're 0 already, leave.
        if (menuOrder.size() == 0)
            return;

        // If not, deactivate what's there and pop
        activeMenu->deactivateMenuButtons();
        menuOrder.pop();

        // If our size is zero, we set equal to nullptr and leave
        if (menuOrder.size() == 0) {
            activeMenu = nullptr;
            return;
        }

        // Set to new top value and activate
        activeMenu = menuOrder.top();
        activeMenu->activateMenuButtons();
    }

    // Render the activeMenu
    void renderActiveMenu() {

        if (activeMenu != nullptr)
            activeMenu->render();
            
    }

    // Handle events of active menu
    void handleActiveMenuEvents(SDL_Event& buttonEvent) {

        int buttonIndex = 0;
        bool wasClicked = false;

        wasClicked = activeMenu->handleButtonEvents(buttonEvent, buttonIndex);

        if (wasClicked == true)
            activeMenu->callFuncPtr(buttonIndex);
    }

}