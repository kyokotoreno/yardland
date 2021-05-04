#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

class video
{
public:
    video();
    //void set_video_mode(int video_mode);

    void OnRender();
    void OnEvent(SDL_Event* e);
    void terminal_tick();

    void set_argperformancetest(bool _ArgPerformanceTest = true);

private:
    SDL_Texture* virtual_scr_texture;

    SDL_Renderer* window_renderer;
    SDL_Window* window;

    unsigned int virtual_scr_width;
    unsigned int virtual_scr_height;
    std::uint32_t virtual_scr_pixelformat;

    std::vector <Uint8>* virtual_scr_pixelbuf;
    std::vector <char>* terminal_buffer;

    bool ArgPerformanceTest;

    enum RGBMasks
    {
        VIDEO_MASK_RED   = 0b0000000000001111,
        VIDEO_MASK_GREEN = 0b0000000011110000,
        VIDEO_MASK_BLUE  = 0b0000111100000000,
        VIDEO_MASK_ALPHA = 0b1111000000000000,
    };
};
