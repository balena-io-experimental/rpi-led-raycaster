#include "led-matrix.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <unistd.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <linux/input.h>

#include "raycaster.h"
#include "keyboard.h"
#include "map.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

int main(int argc, char *argv[]) {
  /*
   * Set up GPIO pins. This fails when not running as root.
   */
  GPIO io;
  if (!io.Init()) {
    std::cerr << "Could not initialise GPIO" << std::endl;
    return 1;
  }

  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
  int rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 2;    // Number of boards chained together.
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
  Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);

  Map map("res/map");
  // Do drawing code here
  Raycaster rc(canvas, &map);

  Raycaster::Viewport vp(16.0, 16.0, 0, &map);

  // We don't have xserver running, so allocate some space for the device map
  char *keymap = static_cast<char *>(malloc(getKeymapSize()));

  double moveSpeed = 1.0;
  double turnSpeed = M_PI / 18.0;
  while(1) {
    getKeyMap(keymap);

    if(getPressed(KEY_UP, keymap)) {
      vp.move(moveSpeed);
    } else if(getPressed(KEY_DOWN, keymap)) {
      vp.move(-moveSpeed);
    }

    if(getPressed(KEY_LEFT, keymap)) {
      vp.turn(-turnSpeed);
    } else if(getPressed(KEY_RIGHT, keymap)) {
      vp.turn(turnSpeed);
    }

    canvas->Clear();
    rc.render(vp);
    usleep(10000);

  }

  free(keymap);

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
