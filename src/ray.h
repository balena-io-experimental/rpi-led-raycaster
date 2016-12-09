#ifndef RESIN_RAY_H
#define RESIN_RAY_H

class Ray {
	public:

		enum Side {
			Vertical,
			Horizontal
		};

		// Initialise the ray with a position and angle in rads
		Ray(double x, double y, double angle);

		// Advance to the next intersection point
		void next();

		int getMapX();
		int getMapY();

		// Perpendicular distance between ray's  initial and current pos
		double getTrueDistance();

		// Which type of intersection
		Side getSide();

	private:
		// Starting position
		double startX, startY;
		// Direction
		double rayDirX, rayDirY;
		// Last intersected cell
		int mapX, mapY;
		// Length to next side
		double sideDistX, sideDistY;
		// Length from side to the next
		double deltaDistX, deltaDistY;
		// Which direction to step in
		int stepX, stepY;
		Side side;
};

#endif /* RESIN_RAY_H */
