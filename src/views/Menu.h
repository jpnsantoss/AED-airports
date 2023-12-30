
#ifndef PROJECT_AED_AIRPORTS_MENU_H
#define PROJECT_AED_AIRPORTS_MENU_H

using namespace std;

/**
 * Abstract base class for all menu classes.
 * Provides a common interface for displaying menus.
 */
class Menu {
public:
    /**
     * Pure virtual function for displaying a menu.
     * Must be overridden in derived classes.
     */
    virtual void display() = 0;
};

#endif //PROJECT_AED_AIRPORTS_MENU_H
