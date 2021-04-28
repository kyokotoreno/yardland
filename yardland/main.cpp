#include <yardland/main.hpp>

video* video_adapter;

SDL_Event AppSDLEvent;

bool ArgPrintPerformance = false;

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "[yardland/main.cpp:10] ERROR SDL could not initialize!\n\tSDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "[yardland/main.cpp:16] INFO Yardland Emulator v0.3.0" << std::endl;
    //std::cout << "[yardland/main.cpp:17] INFO Loading Firmware file \"firmware.bin\"" << std::endl;
    
    binary_file firmware_file;

    //firmware_file.load("firmware.bin");

    video_adapter = new video();

    unsigned int frames = 0;
    Uint64 start = SDL_GetPerformanceCounter();

    while(1)
    {
        SDL_PollEvent(&AppSDLEvent);
        if(AppSDLEvent.type == SDL_QUIT) {
            break;
        }
        else {
            video_adapter->OnEvent(&AppSDLEvent);
        }

        video_adapter->OnRender();

        frames++;
        const Uint64 end = SDL_GetPerformanceCounter();
        const static Uint64 freq = SDL_GetPerformanceFrequency();
        const double seconds = ( end - start ) / static_cast< double >( freq );
        if(seconds > 2.0)
        {
            std::cout
                << "[yardland/main.cpp:44] INFO Performance: " 
                << frames << " frames in "
                << std::setprecision(1) << std::fixed << seconds << " seconds = "
                << std::setprecision(1) << std::fixed << frames / seconds << " FPS ("
                << std::setprecision(3) << std::fixed << ( seconds * 1000.0 ) / frames << " ms/frame)"
                << std::endl;
            start = end;
            frames = 0;
        }
    }

    SDL_Quit();
    return 0;
}
