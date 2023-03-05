#include <io.hpp>

uint8_t io_buffer[12];
int keyboard_ptr = IO_KEYBOARD;

void io_setMouse(int x, int y)
{
	io_buffer[IO_MOUSEPOS_X] = x;
	io_buffer[IO_MOUSEPOS_Y] = y;
	return;
}

void io_pushKeyboard(char key)
{
	io_buffer[keyboard_ptr] = key;
	keyboard_ptr++;
	if (keyboard_ptr >= (IO_KEYBOARD + IO_KEYBOARD_MAX))
		keyboard_ptr = IO_KEYBOARD;
	return;
}

char io_pullKeyboard()
{
	char key;
	key = io_buffer[keyboard_ptr];
	keyboard_ptr--;
	if (keyboard_ptr <= (IO_KEYBOARD))
		keyboard_ptr = IO_KEYBOARD_MAX;
	return key;
}
