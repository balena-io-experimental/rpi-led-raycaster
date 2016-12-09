
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <linux/input.h>

#include "keyboard.h"

void getKeyMap(char *keymap) {
	// You may need to change this to get keyboard input to work, this is just what my system had
	// it set up as
	FILE *kbd = fopen("/dev/input/event0", "r");
	if(kbd == NULL) {
		fprintf(stderr, "Could not open keyboard input file");
	}
	memset(keymap, 0, getKeymapSize());
	ioctl(fileno(kbd), EVIOCGKEY(getKeymapSize()), keymap);
	fclose(kbd);
}

bool getPressed(int key, char *keymap) {
	int keyb = keymap[key / 8];
	int mask = 1 << (key % 8);

	return keyb & mask;
}

int getKeymapSize() {
	return KEY_MAX / 8 + 1;
}
