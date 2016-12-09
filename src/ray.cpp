#include "ray.h"

#include <iostream>
#include <limits>
#include <cmath>

Ray::Ray(double x, double y, double angle) {
	startX = x;
	startY = y;

	mapX = static_cast<int>(floor(startX));
	mapY = static_cast<int>(floor(startY));

	rayDirX = cos(angle);
	rayDirY = sin(angle);

	double rayDirX2 = rayDirX*rayDirX;
	double rayDirY2 = rayDirY*rayDirY;

	deltaDistX = rayDirX2 > 0 ? sqrt(1 + rayDirY2 / rayDirX2) : std::numeric_limits<double>::max();
	deltaDistY = rayDirY2 > 0 ? sqrt(1 + rayDirX2 / rayDirY2) : std::numeric_limits<double>::max();

	if(rayDirX < 0) {
		stepX = -1;
		sideDistX = (startX - mapX) * deltaDistX;
	} else {
		stepX = 1;
		sideDistX = (mapX + 1 - startX) * deltaDistX;
	}

	if(rayDirY < 0) {
		stepY = -1;
		sideDistY = (startY - mapY) * deltaDistY;
	} else {
		stepY = 1;
		sideDistY = (mapY + 1 - startY) * deltaDistY;
	}

}

void Ray::next() {
	if(sideDistX < sideDistY) {
		sideDistX += deltaDistX;
		mapX += stepX;
		side = Ray::Vertical;
	} else {
		sideDistY += deltaDistY;
		mapY += stepY;
		side = Ray::Horizontal;
	}
}

int Ray::getMapX() {
	return mapX + 1;
}

int Ray::getMapY() {
	return mapY + 1;
}

double Ray::getTrueDistance() {
	double distance;
	if(side == Ray::Vertical) {
		distance = std::abs((mapX - startX + (1 - stepX) / 2) / rayDirX);
	} else {
		distance = std::abs((mapY - startY + (1 - stepY) / 2) / rayDirY);
	}

	return distance;
}

Ray::Side Ray::getSide() {
	return side;
}
