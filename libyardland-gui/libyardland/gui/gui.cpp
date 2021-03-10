#include <libyardland/gui/gui.hpp>

SDL_Event GuiSDLEvent;

SDL_Renderer* GuiRenderer = NULL;
SDL_Window* GuiWindow = NULL;
SDL_Surface* GuiWindowSurface = NULL;
SDL_Rect TextRect;
TTF_Font* GuiFont = NULL;

SDL_Texture* TextTexture;

void(*AppOnRenderCallback)();

int GuiEventHandler()
{

    GuiStatus GuiEventStatus = GUI_EVENT_NOTHING;

    while(SDL_PollEvent(&GuiSDLEvent)) {
        if (GuiSDLEvent.type == SDL_QUIT) {
            GuiEventStatus = GUI_EVENT_QUIT;
        }
        if (GuiSDLEvent.type == SDL_KEYDOWN) {
            switch(GuiSDLEvent.key.keysym.sym) {
                case SDLK_ESCAPE:
                    GuiEventStatus = GUI_EVENT_QUIT;
                    break;
                case SDLK_SPACE:
                    GuiEventStatus = GUI_EVENT_SIMSTART;
                    break;
            }
        }
    }

    SDL_SetRenderDrawColor(GuiRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(GuiRenderer);

    AppOnRenderCallback();

    SDL_RenderPresent(GuiRenderer);

    return (int)GuiEventStatus;
}

int GuiInitSDL(void(*OnRenderCallback)())
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL could not initialize!\n\tSDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	/*if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cerr << "SDL_image could not initialize!\n\tSDL_image Error: " << IMG_GetError() << std::endl;
		return -2;
	}
    */

   //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -2;
    }

    GuiFont = TTF_OpenFont("nixie.ttf", 24);
    if(GuiFont == NULL)
    {
        std::cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -2;
    }

	SDL_CreateWindowAndRenderer(1450, 980, SDL_WINDOW_SHOWN, &GuiWindow, &GuiRenderer);

	if (GuiWindow == NULL) {
		std::cerr << "Application Window could not be created!\n\tSDL Error: " << SDL_GetError() << std::endl;
		return -3;
	}

	if (GuiRenderer == NULL) {
		std::cerr << "Application Renderer could not be created!\n\tSDL Error: " << SDL_GetError() << std::endl;
        return -4;
	}

	GuiWindowSurface = SDL_GetWindowSurface(GuiWindow);

	if (GuiWindowSurface == NULL) {
		std::cerr << "Application Window Surface could not be retrieved!\n\tSDL Error: " << SDL_GetError() << std::endl;
        return -5;
	}

	SDL_SetWindowTitle(GuiWindow, "Project Yardland v0.1.0");
    SDL_SetWindowPosition(GuiWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    AppOnRenderCallback = OnRenderCallback;

    return 0;
}

int GuiCloseSDL()
{
    GuiWindowSurface = NULL;
    SDL_DestroyRenderer(GuiRenderer);
    SDL_DestroyWindow(GuiWindow);

    GuiRenderer = NULL;
    GuiWindow = NULL;

    TTF_Quit();
    SDL_Quit();

    return 0;
}
