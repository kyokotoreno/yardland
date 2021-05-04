#pragma once

#include <iostream>
#include <iomanip>

#ifdef UNIX
    #include <unistd.h>
#endif /*UNIX*/

#include <SDL2/SDL.h>

#include <libyardland/video/video.hpp>
#include <libyardland/cpu/cpu-65816.hpp>
#include <libyardland/binary-file/binary-file.hpp>
