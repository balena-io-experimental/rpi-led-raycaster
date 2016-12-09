#ifndef RESIN_RAYCASTER_H
#define RESIN_RAYCASTER_H

#include <cmath>
#include <limits>

#include "led-matrix.h"
#include "graphics.h"

#include "ray.h"
#include "map.h"

using rgb_matrix::Canvas;

class Raycaster {
public:
    struct Viewport {
      double x, y;
      double angle;
      double fov;
      double maxDist;
      Map *map;

      Viewport(double x, double y, double angle, Map *map, double fov = M_PI / 3.0, double maxDist = 64.0) {
        this->x = x;
        this->y = y;
        this->angle = angle;
        this->fov = fov;
        this->maxDist = maxDist;
        this->map = map;
      }

      void move(double delta) {
        double newx = x + cos(angle)*delta;
        double newy = y + sin(angle)*delta;

        // ensure we're not walking through a wall
        if(this->map->get(floor(newx), floor(newy)) != 0) {
          return;
        }
        x = newx;
        y = newy;
      }

      void turn(double delta) {
        angle += delta;
      }

    };

    Raycaster(Canvas *canvas, Map *map);
    void render(Viewport vp);

  private:
    Canvas *canvas;
    Map *map;

    int computeDisplayHeight(double distance, int blockHeight = 32) {
      return distance > 0 ? static_cast<int>(blockHeight / distance) : std::numeric_limits<int>::max();
    }

    rgb_matrix::Color getColor(int c) {
      switch(c) {
        case 1:
          return rgb_matrix::Color(30, 30, 30);
        case 2:
          return rgb_matrix::Color(150, 150, 100);
        case 3:
          return rgb_matrix::Color(0, 100, 100);
        case 4:
          return rgb_matrix::Color(50, 0, 100);
        default:
          return rgb_matrix::Color(255, 0, 0);
      }
    }
};


#endif /* RESIN_RAYCASTER_H */
