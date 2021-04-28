#include <libyardland/video/video.hpp>

#define TERMINAL_SCREEN_WIDTH   320
#define TERMINAL_SCREEN_HEIGHT  200
#define TERMINAL_COLUMNS         40
#define TERMINAL_ROWS            25

video::video()
{
    this->window = SDL_CreateWindow
        (
        "Virtual Screen",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        400,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );

    if (this->window == NULL) {
        std::cout << "[libyardland/video/video.cpp:16] ERROR Could not create virtual screen window, SDL Error: " << SDL_GetError() << std::endl;
    }

    this->window_renderer = SDL_CreateRenderer
        (
        this->window,
        -1,
        SDL_RENDERER_ACCELERATED
        );

    this->virtual_scr_pixelformat = SDL_PIXELFORMAT_RGB444;

    this->virtual_scr_width  = TERMINAL_SCREEN_WIDTH;
    this->virtual_scr_height = TERMINAL_SCREEN_HEIGHT;

    this->virtual_scr_pixelbuf = new std::vector <Uint8> (this->virtual_scr_width * this->virtual_scr_height * 2);

    this->terminal_buffer = new std::vector <char>(TERMINAL_COLUMNS * TERMINAL_ROWS);

    this->virtual_scr_texture = SDL_CreateTexture
        (
        this->window_renderer,
        this->virtual_scr_pixelformat,
        SDL_TEXTUREACCESS_STREAMING,
        this->virtual_scr_width,
        this->virtual_scr_height
        );

    // Deactivate performance test
    this->ArgPerformanceTest = false;

    std::cout << "[libyardland/video/video.cpp:44] INFO Initialized virtual video adapter." << std::endl;

    return;
}


void video::OnRender()
{
    SDL_SetRenderDrawColor( this->window_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
    SDL_RenderClear(this->window_renderer);

    // splat down some random pixels, if performance test is enabled.

    if (this->ArgPerformanceTest) {
        for (unsigned int i = 0; i < this->virtual_scr_pixelbuf->capacity(); i++)
        {
            const unsigned int x = rand() % this->virtual_scr_width;
            const unsigned int y = rand() % this->virtual_scr_height;

            const unsigned int offset = ( this->virtual_scr_width * 2 * y ) + x * 2;

            (*virtual_scr_pixelbuf)[ offset + 0 ]  =  rand() % 0x0f;       // b
            (*virtual_scr_pixelbuf)[ offset + 0 ] += (rand() % 0x0f) << 5; // g
            (*virtual_scr_pixelbuf)[ offset + 1 ]  =  rand() % 0x0f;       // r
            
            //(*virtual_scr_pixelbuf)[ offset + 1 ] += (0x0f) << 4; // a
            //virtual_scr_pixelbuf[ offset + 0 ] = 0xff;
            //virtual_scr_pixelbuf[ offset + 1 ] = 0xff;
        }
    }   
    // If performance test is not enabled, then continue emulating a terminal. 
    else {
        this->terminal_tick();
    }

    SDL_UpdateTexture
    (
    this->virtual_scr_texture,
    NULL,
    this->virtual_scr_pixelbuf->data(),
    this->virtual_scr_width * 2
    );

    SDL_RenderCopy(this->window_renderer, this->virtual_scr_texture, NULL, NULL);

    SDL_RenderPresent(this->window_renderer);

    return;
}

void video::OnEvent(SDL_Event* e)
{
    switch(e->type) {
        case SDL_WINDOWEVENT:
            if(e->window.windowID == SDL_GetWindowID(this->window)) {
                /*
                if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
                    std::cout << "[libyardland/video/video.cpp:97] INFO Virtual screen window resized, w: " << e->window.data1 << " h: " << e->window.data2 << std::endl;
                }
                */
            }
            break;
    }
    return;
}

void video::terminal_tick()
{
    int screen_x = 0, screen_y = 0;

    for (int row = 0; row < 25; row++) {
        for (int column = 0; column < 40; column++) {
            Uint8* letter_bitmap = ( Uint8* ) font8x8_basic[(unsigned int) (*this->terminal_buffer)[(row * 40) + column]];

            int x, y;
            int set;

            for (x = 0; x < 8; x++) {
                for (y = 0; y < 8; y++) {
                    set = letter_bitmap[x] & 1 << y;

                    int ptr = (((screen_y + x) * 320) + (screen_x + y));

                    (*this->virtual_scr_pixelbuf)[(ptr * 2) + 0] = set ? 0xDD : 0;
                    (*this->virtual_scr_pixelbuf)[(ptr * 2) + 1] = set ? 0x0D : 0;
                }
            }

            screen_x += 8;
        }

        screen_x = 0;
        screen_y += 8;
    }
    return;
}
