#ifndef RESIN_MAP_H
#define RESIN_MAP_H

#include <string>
#include <vector>

class Map {
public:
	Map(std::string mapFile);
	short get(unsigned x, unsigned y);

private:
	unsigned int width;
	unsigned int height;
	short *map;

	void splitLine(std::string line, std::vector<std::string>& arr);
};

#endif /* RESIN_MAP_H */
