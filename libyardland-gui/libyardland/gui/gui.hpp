#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

extern SDL_Event GuiSDLEvent;

extern SDL_Renderer* GuiRenderer;
extern SDL_Window* GuiWindow;
extern SDL_Surface* GuiWindowSurface;
extern TTF_Font* GuiFont;

/**
 * \brief Enum for gui statuses.
 */
enum GuiStatus {
    GUI_EVENT_NOTHING = 0,
    GUI_EVENT_QUIT,
    GUI_EVENT_SIMSTART
};

/**
 * @brief Initialize SDL.
 * 
 * @return A non-zero value on error.
 */
extern int GuiInitSDL(void(*OnRenderCallback)());

extern int GuiCloseSDL();

/**
 * \brief Handle SDL Events.
 * 
 * \return int status (A cast from a GuiStatus variable into an int, used to determine the result of the event handling)
 */
extern int GuiEventHandler();
