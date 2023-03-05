#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <boost/log/trivial.hpp>

#define TERMINAL_WIDTH       320
#define TERMINAL_HEIGHT      200
#define TERMINAL_COLUMNS     40
#define TERMINAL_ROWS        25

#define TERMINAL_PITCH       TERMINAL_WIDTH * 8

#define TERMINAL_BUFFER_SIZE TERMINAL_COLUMNS * TERMINAL_ROWS
#define    PIXEL_BUFFER_SIZE TERMINAL_WIDTH   * TERMINAL_HEIGHT

class VideoAdapter
{
    public:
    
    VideoAdapter();
    ~VideoAdapter();
    //void set_video_mode(int video_mode);

    void render();
    void processEvents(SDL_Event* e);

    private:
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;

    uint32_t *mpPixelBuffer;
    char *mpTerminalBuffer;

    enum RGBMasks
    {
        VIDEO_MASK_RED   = 0b0000000000001111,
        VIDEO_MASK_GREEN = 0b0000000011110000,
        VIDEO_MASK_BLUE  = 0b0000111100000000,
        VIDEO_MASK_ALPHA = 0b1111000000000000,
    };

    void drawTerminal();
    void drawLetter(int screenX, int screenY, int row, int column);
};
