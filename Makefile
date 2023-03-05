CFLAGS:=-std=c++20 -Wall -pedantic -g -DBOOST_LOG_DYN_LINK
LIBS:=-lpthread -lboost_log -lSDL2 -lSDL2main
SOURCES:=src/main.cpp src/video-adapter.cpp src/memory.cpp
INCLUDE:=-Isrc -Ideps
OUT:=yardland

all: $(SOURCES)
	g++ $(CFLAGS) $(INCLUDE) $(LIBS) $(SOURCES) -o $(OUT)
