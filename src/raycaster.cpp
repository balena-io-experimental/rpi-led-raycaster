#include "raycaster.h"

using namespace rgb_matrix;

Raycaster::Raycaster(Canvas *canvas, Map *map) {
	this->canvas = canvas;
	this->map = map;
}

void Raycaster::render(Viewport vp) {

	// FIXME: get this from the canvas
	int screenW = 64;
	int screenH = 32;
	double screenDist = screenW / (2 * tan(vp.fov / 2));

	// Clear the screen
	canvas->Clear();

	// Draw the floor and ceiling
	for(int i = 0; i < screenH / 2; ++i) {
		DrawLine(canvas, 0, i, screenW, i, Color(0, 0, 255));
	}
	for(int i = screenH / 2 + 1; i < screenH; ++i) {
		DrawLine(canvas, 0, i, screenW, i, Color(30, 200, 30));
	}

	// Trace the rays

	// Loop over every pixel
	for(int x = 0; x < screenW; ++x) {
		// Trace a ray from the view point at this angle
		double deltaAngle = atan((x - screenW / 2) / screenDist);
		double angle = vp.angle + deltaAngle;
		Ray ray(vp.x, vp.y, angle);

		for(double stepCount = 0; stepCount < vp.maxDist; ++stepCount) {
			// Advance to the next intersection point
			ray.next();

			int mapX = ray.getMapX();
			int mapY = ray.getMapY();

			// Get if there is a wall at that point on the map
			//if(!isWall(mapX, mapY)) continue;
			int col = this->map->get(mapX, mapY);
			if(col == 0) continue;

			Color c = getColor(col);

			// Calculate 'true distance' and display height
			double distance = ray.getTrueDistance();
			int height = this->computeDisplayHeight(distance);
			if(height > screenH) height = screenH;

			// Draw  line
			DrawLine(canvas, x, (screenH - height) / 2, x, (screenH + height) / 2, c);

			// Next ray
			break;

		}
	}
}
