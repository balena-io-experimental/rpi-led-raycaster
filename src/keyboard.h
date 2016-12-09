#ifndef RESIN_KEYBOARD_H
#define RESIN_KEYBOARD_H



void getKeyMap(char *keymap);

bool getPressed(int key, char *keymap);

int getKeymapSize();

#endif /* RESIN_KEYBOARD_H */
