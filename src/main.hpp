#pragma once

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>
#include <imgui/backends/imgui_impl_sdlrenderer.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <stdio.h>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <SDL2/SDL.h>
#include <memory.hpp>
#include <video-adapter.hpp>
#include <input-files/binary-file.hpp>
#include <emu816.hpp>

static Memory memory;
static VideoAdapter video;
static emu816 emulator;
