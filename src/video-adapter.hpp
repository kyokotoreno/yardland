#pragma once

#include <cstdint>
//#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <boost/log/trivial.hpp>
#include <memory.hpp>

#define TERMINAL_WIDTH 720
#define TERMINAL_HEIGHT 480
#define TERMINAL_COLUMNS 40
#define TERMINAL_ROWS 25
#define TEXT_BUFFER_SIZE (TERMINAL_COLUMNS * TERMINAL_ROWS)
#define PIXEL_BUFFER_SIZE (TERMINAL_WIDTH * TERMINAL_HEIGHT)
#define REGION_VIDEOPORTS_START 0x000200
#define REGION_TEXT_START 0x00C830
#define REGION_PIXELS_START 0x0B0000
#define REGION_VIDEOPORTS_END (REGION_VIDEOPORTS_START + sizeof(VideoPorts))
#define REGION_TEXT_END (REGION_TEXT_START + TEXT_BUFFER_SIZE)
#define REGION_PIXELS_END (REGION_PIXELS_START + 0xFFFF)

/*
enum RGBMask {
    BLUE  = 31,
    GREEN = 63 << 5,
    RED   = 31 << 11,
};
*/

struct VideoPorts {
    uint8_t mode;
    uint8_t bank;
};

class VideoAdapter
{
public:
    static void init();
    static void destroy();
    static void render(SDL_Texture *texture);
    static void accessPort(uint32_t address, uint8_t *data, bool get);
    static void accessText(uint32_t address, uint8_t *data, bool get);
    static void accessPixel(uint32_t address, uint8_t *data, bool get);
private:
    static VideoPorts *pPorts;
    static uint8_t *pPixelBuffer;
    static char *pTextBuffer;

    static void drawTerminal();
};
