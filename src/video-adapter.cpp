#include <video-adapter.hpp>
#include <font8x8/font8x8_basic.hpp>

VideoAdapter::VideoAdapter()
{
    mpTerminalBuffer =     (char*) calloc(TERMINAL_BUFFER_SIZE, sizeof(char));
    strcpy(mpTerminalBuffer, "Hello World!");

    mWindow = SDL_CreateWindow(
        "Virtual Screen",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        400,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (mWindow == NULL) {
        BOOST_LOG_TRIVIAL(error) << "Could not create video adapter window, SDL Error: " << SDL_GetError();
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    mTexture = SDL_CreateTexture(
        mRenderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        TERMINAL_WIDTH,
        TERMINAL_HEIGHT
    );

    if (mTexture == NULL) {
        BOOST_LOG_TRIVIAL(error) << "Video adapter texture creation failed, SDL Error: " << SDL_GetError();
    }

    BOOST_LOG_TRIVIAL(info) << "Initialized video adapter.";
}

VideoAdapter::~VideoAdapter() {
    SDL_DestroyTexture(mTexture);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
}

void VideoAdapter::render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);

    drawTerminal();

    //SDL_UpdateTexture(mTexture, NULL, mpPixelBuffer, TERMINAL_PITCH);
    
    SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
    SDL_RenderPresent(mRenderer);

    return;
}

void VideoAdapter::processEvents(SDL_Event* e)
{
    switch(e->type) {
        case SDL_WINDOWEVENT:
            if(e->window.windowID == SDL_GetWindowID(mWindow)) {
                if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
                    BOOST_LOG_TRIVIAL(trace) << "Video adapter window resized, w: " << e->window.data1 << ", h: " << e->window.data2 << ".";
                }
            }
            break;
    }
    return;
}

void VideoAdapter::drawLetter(int screenX, int screenY, int row, int column) {
    uint8_t character = mpTerminalBuffer[(row * 40) + column];
    uint8_t* letterBitmap = font8x8_basic[character];

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int set = letterBitmap[x] & 1 << y;

            int ptr = (((screenY + x) * 320) + (screenX + y));

            mpPixelBuffer[ptr] = set ? UINT32_MAX : 0;
        }
    }
}

void VideoAdapter::drawTerminal()
{
    int pitch;
    SDL_LockTexture(mTexture, NULL, (void**) &mpPixelBuffer, &pitch);

    int screenX = 0, screenY = 0;

    for (int row = 0; row < 25; row++) {
        for (int column = 0; column < 40; column++) {
            drawLetter(screenX, screenY, row, column);

            screenX += 8;
        }

        screenX = 0;
        screenY += 8;
    }
    
    SDL_UnlockTexture(mTexture);
}
