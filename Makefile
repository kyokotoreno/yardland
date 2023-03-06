CFLAGS := -std=c++20 -Wall -pedantic -g -DBOOST_LOG_DYN_LINK
LIBS := -lpthread -lboost_log -lSDL2 -lSDL2main
SOURCES := src/main.cpp src/video-adapter.cpp src/memory.cpp src/input-files/binary-file.cpp src/emu816.cpp src/wdc816.cpp
SOURCES_IMGUI := deps/imgui/*.cpp deps/imgui/backends/imgui_impl_sdl2.cpp deps/imgui/backends/imgui_impl_sdlrenderer.cpp deps/imgui/misc/cpp/imgui_stdlib.cpp
INCLUDE := -Isrc -Ideps -Ideps/imgui -I/usr/include/SDL2
OUT := yardland

all: $(SOURCES) $(SOURCES_IMGUI)
	g++ $(CFLAGS) -Og -DLOG_TRACE $(INCLUDE) $(LIBS) $(SOURCES) $(SOURCES_IMGUI) -o $(OUT)-debug

test: deps/test
	$(MAKE) -C deps/test

release: $(SOURCES) $(SOURCES_IMGUI)
	g++ $(CFLAGS) -Ofast $(INCLUDE) $(LIBS) $(SOURCES) $(SOURCES_IMGUI) -o $(OUT)
