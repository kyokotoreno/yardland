#include <video-adapter.hpp>
#include <font8x8/font8x8_basic.hpp>

VideoPorts *VideoAdapter::pPorts = new VideoPorts {0, 0};
char *VideoAdapter::pTextBuffer = new char[TEXT_BUFFER_SIZE];
uint8_t *VideoAdapter::pPixelBuffer = new uint8_t[PIXEL_BUFFER_SIZE * 2];

void VideoAdapter::init() {
    // Add the video ports region.
    Memory::addRegion({
        REGION_VIDEOPORTS_START,
        REGION_VIDEOPORTS_END,
        VideoAdapter::accessPort
    });
    // Add the video chars region.
    Memory::addRegion({
        REGION_TEXT_START,
        REGION_TEXT_END,
        VideoAdapter::accessText
    });
    // Add the video pixels region.
    Memory::addRegion({
        REGION_PIXELS_START,
        REGION_PIXELS_END,
        VideoAdapter::accessPixel
    });
}


void VideoAdapter::destroy() {
    delete VideoAdapter::pPorts;
    delete[] VideoAdapter::pTextBuffer;
    delete[] VideoAdapter::pPixelBuffer;
}

void VideoAdapter::drawTerminal() {
    for (unsigned int row = 0; row < TERMINAL_ROWS; row++) {
        for (unsigned int column = 0; column < TERMINAL_COLUMNS; column++) {
            uint8_t character = VideoAdapter::pTextBuffer[(row * TERMINAL_COLUMNS) + column];

            for (unsigned int y = 0; y < 8; y++) {
                for (unsigned int x = 0; x < 8; x++) {
                    bool set = font8x8_basic[character][x] & 1 << y;

                    unsigned int screenY = row * 8, screenX = column * 8;
                    
                    size_t ptr = ((screenY + x) * TERMINAL_WIDTH) + (screenX + y);
                    
                    reinterpret_cast<uint16_t*>(VideoAdapter::pPixelBuffer)[ptr] = set ? UINT16_MAX : 0;
                }
            }
        }
    }
}

void VideoAdapter::render(SDL_Texture *texture) {
    if (VideoAdapter::pPorts->mode == 0)
        drawTerminal();
    
    int pitch;
    uint16_t *pPixels;

    SDL_LockTexture(texture, NULL, reinterpret_cast<void**>(&pPixels), &pitch);
    memcpy(pPixels, pPixelBuffer, PIXEL_BUFFER_SIZE * 2);
    SDL_UnlockTexture(texture);
}

void VideoAdapter::accessPort(uint32_t address, uint8_t *data, bool get) {
    size_t port = address - REGION_VIDEOPORTS_START;
    if (get) {
        *data = reinterpret_cast<uint8_t*>(VideoAdapter::pPorts)[port];
    } else {
        reinterpret_cast<uint8_t*>(VideoAdapter::pPorts)[port] = *data;
    }
}

void VideoAdapter::accessText(uint32_t address, uint8_t *data, bool get) {
    size_t character = address - REGION_TEXT_START;

    if (get) {
        *data = reinterpret_cast<uint8_t*>(VideoAdapter::pTextBuffer)[character];
    } else {
        reinterpret_cast<uint8_t*>(VideoAdapter::pTextBuffer)[character] = *data;
    }
}

void VideoAdapter::accessPixel(uint32_t address, uint8_t *data, bool get) {
    if (VideoAdapter::pPorts->mode == 1) {
        size_t pixel = (address - REGION_PIXELS_START) + (VideoAdapter::pPorts->bank << 16);

        if (get) {
            *data = VideoAdapter::pPixelBuffer[pixel];
        } else {
            VideoAdapter::pPixelBuffer[pixel] = *data;
        }
    }
}
