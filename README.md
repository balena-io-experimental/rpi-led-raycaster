# RPI RGB LED Panel Raycaster

This project is a proof on concept of a raycaster implemented in c++ on a raspberry pi, outputting to a chain of RGB LED panels. It uses resin.io and the [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix) library.

It is controlled via keyboard, but does not run an xserver. Map format is simple, and colours are hardcoded.

## Known issues

Sometimes going too close to a wall makes you get stuck.
