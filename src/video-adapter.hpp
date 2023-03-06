#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <boost/log/trivial.hpp>
#include <memory.hpp>

#define TERMINAL_WIDTH       640
#define TERMINAL_HEIGHT      200
#define TERMINAL_COLUMNS     80
#define TERMINAL_ROWS        25

#define TERMINAL_BUFFER_SIZE TERMINAL_COLUMNS * TERMINAL_ROWS
#define    PIXEL_BUFFER_SIZE TERMINAL_WIDTH   * TERMINAL_HEIGHT

enum RGBMask {
    VIDEO_MASK_ALPHA = 0b00000000000000000000000011111111,
    VIDEO_MASK_BLUE  = 0b00000000000000001111111100000000,
    VIDEO_MASK_GREEN = 0b00000000111111110000000000000000,
    VIDEO_MASK_RED   = 0b11111111000000000000000000000000,
};

struct VideoPorts {
    uint8_t color;
    uint8_t mode;
    uint8_t bank;
};

class VideoAdapter
{
    public:
    
    VideoAdapter();
    //~VideoAdapter();

    void render(SDL_Texture *texture);
    void processEvents(SDL_Event *e);

    static Region getPortsRegion();
    static Region getTerminalRegion();
    static Region getPixelsRegion();
    
    static void accessPorts(uint32_t address, uint8_t *data, bool get);
    static void accessTerminal(uint32_t address, uint8_t *data, bool get);
    static void accessPixel(uint32_t address, uint8_t *data, bool get);

private:
    static VideoPorts *pPorts;
    static uint32_t *pPixelBuffer;
    static char *pTerminalBuffer;

    void drawTerminal(uint32_t *pixels);
    void drawLetter(uint32_t *pixels, int screenX, int screenY, int row, int column);
};
