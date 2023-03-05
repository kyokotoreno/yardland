#pragma once
#include <stdint.h>
#include <fstream>

#define IO_MOUSEPOS_X 0
#define IO_MOUSEPOS_Y 1

#define IO_KEYBOARD 2
#define IO_KEYBOARD_MAX 10

extern uint8_t io_buffer[12];

extern int keyboard_ptr;

extern void io_setMouse(int x, int y);
extern void io_pushKeyboard(char key);
extern char io_pullKeyboard();

void hdd_loadFile(int file, uint8_t* databank);
void hdd_saveFile(int file, uint8_t* databank);
