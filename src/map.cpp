#include "map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cassert>

Map::Map(std::string mapFile) {
	std::ifstream mapData(mapFile.c_str());

	std::string line;

	// The first line contains the width and height
	std::string delimiter = ",";
	std::getline(mapData, line);
	unsigned idx = static_cast<unsigned int>(line.find(delimiter));
	std::string wStr = line.substr(0, idx);
	std::string hStr = line.substr(idx+1);
	std::cout << "Width: " << wStr << ", Height: " << hStr << std::endl;
	this->width = atoi(wStr.c_str());
	this->height = atoi(hStr.c_str());

	unsigned x = 0, y = 0;
	// Allocate space for the map
	this->map = static_cast<short *>(malloc(sizeof(short) * this->width * this->height));

	while(std::getline(mapData, line)) {

		while(x < this->width) {
			this->map[x + y * this->width] = static_cast<short>(line.at(x) - '0');
			++x;
		}

		x = 0;
		y += 1;
	}
	std::cout << "Y is: " << y << " height is: " << this->height << std::endl;
	assert(y == this->height - 1);
}

short Map::get(unsigned x, unsigned y) {
	if(x >= this->width || y >= this->height) return 0;
	return this->map[x + y * this->width];

}
