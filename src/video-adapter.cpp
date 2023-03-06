#include <video-adapter.hpp>
#include <font8x8/font8x8_basic.hpp>

VideoPorts *VideoAdapter::pPorts;
uint32_t *VideoAdapter::pPixelBuffer;
char *VideoAdapter::pTerminalBuffer;

VideoAdapter::VideoAdapter() {
    VideoAdapter::pPorts = (VideoPorts*)calloc(1, sizeof(VideoPorts));
    VideoAdapter::pTerminalBuffer = (char*)calloc(TERMINAL_BUFFER_SIZE, sizeof(char));
    VideoAdapter::pPixelBuffer = (uint32_t*)calloc(PIXEL_BUFFER_SIZE, sizeof(uint32_t));

    /*
    mTexture = SDL_CreateTexture(
        mRenderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        TERMINAL_WIDTH,
        TERMINAL_HEIGHT
    );
    */

    BOOST_LOG_TRIVIAL(info) << "Initialized video adapter.";
}

//VideoAdapter::~VideoAdapter() {}

void VideoAdapter::render(SDL_Texture *texture) {
    int pitch;
    uint32_t *pPixels;
    SDL_LockTexture(texture, NULL, (void**) &pPixels, &pitch);

    if (VideoAdapter::pPorts->mode == 0) {
        drawTerminal(pPixels);
        memcpy(pPixelBuffer, pPixels, PIXEL_BUFFER_SIZE);
    } else {
        memcpy(pPixels, pPixelBuffer, PIXEL_BUFFER_SIZE);
    }
    
    SDL_UnlockTexture(texture);
    return;
}

void VideoAdapter::processEvents(SDL_Event* e) { }

Region VideoAdapter::getPortsRegion() {
    BOOST_LOG_TRIVIAL(debug) << "Video ports are located at: " << boost::format("%#x") % (0xa000 + TERMINAL_BUFFER_SIZE + sizeof(VideoPorts)) << ".";
    return {
        0xa000 + TERMINAL_BUFFER_SIZE,
        0xa000 + TERMINAL_BUFFER_SIZE + sizeof(VideoPorts),
        accessPorts
    };
}

Region VideoAdapter::getTerminalRegion() {
    return {
        0xa000,
        0xa000 + TERMINAL_BUFFER_SIZE,
        accessTerminal
    };
}

Region VideoAdapter::getPixelsRegion() {
    return {
        0xb000,
        0xcfff,
        accessPixel
    };
}

void VideoAdapter::accessPorts(uint32_t address, uint8_t *data, bool get) {
    size_t port = address - (0xa000 + TERMINAL_BUFFER_SIZE);
    if (get) {
        *data = ((uint8_t*)VideoAdapter::pPorts)[port];
    } else {
        ((uint8_t*)VideoAdapter::pPorts)[port] = *data;
    }
}

void VideoAdapter::accessTerminal(uint32_t address, uint8_t *data, bool get) {
    size_t character = address - 0xa000;
    if (get) {
        *data = VideoAdapter::pTerminalBuffer[character];
    } else {
        VideoAdapter::pTerminalBuffer[character] = *data;
    }
}

void VideoAdapter::accessPixel(uint32_t address, uint8_t *data, bool get) {
    size_t pixel = (address - 0xb000) + (VideoAdapter::pPorts->bank << 12);
    if (get) {
        *data = VideoAdapter::pPixelBuffer[pixel];
    } else {
        VideoAdapter::pPixelBuffer[pixel] = *data;
    }
}

void VideoAdapter::drawLetter(uint32_t *pixels, int screenX, int screenY, int row, int column) {
    uint8_t character = pTerminalBuffer[(row * TERMINAL_COLUMNS) + column];
    uint8_t* letterBitmap = font8x8_basic[character];

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            bool set = letterBitmap[x] & 1 << y;
            int ptr = ((screenY + x) * TERMINAL_WIDTH) + (screenX + y);
            uint32_t color;
            switch(VideoAdapter::pPorts->color) {
                case 0: color = UINT32_MAX; break;
                case 1: color = RGBMask::VIDEO_MASK_RED   + RGBMask::VIDEO_MASK_ALPHA; break;
                case 2: color = RGBMask::VIDEO_MASK_GREEN + RGBMask::VIDEO_MASK_ALPHA; break;
                case 3: color = RGBMask::VIDEO_MASK_BLUE  + RGBMask::VIDEO_MASK_ALPHA; break;
            }
            pixels[ptr] = set ? color : 0;
        }
    }
}

void VideoAdapter::drawTerminal(uint32_t *pixels) {
    int screenX = 0, screenY = 0;

    for (int row = 0; row < TERMINAL_ROWS; row++) {
        for (int column = 0; column < TERMINAL_COLUMNS; column++) {
            drawLetter(pixels, screenX, screenY, row, column);
            screenX += 8;
        }
        screenX = 0;
        screenY += 8;
    }
}
