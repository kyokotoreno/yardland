#include <main.hpp>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        BOOST_LOG_TRIVIAL(error) << "Could not initilize SDL!, Error: " << SDL_GetError();
        return -1;
    }

    //binary_file firmware_file;

    //firmware_file.load("firmware.bin");

    auto memory = new Memory();
    auto video_adapter = new VideoAdapter();

    SDL_Event event;

    while(true)
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT) {
            break;
        }
        
        video_adapter->processEvents(&event);
        video_adapter->render();
    }

    BOOST_LOG_TRIVIAL(trace) << "Application quit.";
    SDL_Quit();
    return 0;
}
