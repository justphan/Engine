#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "unit.h"
#include <vector>
using namespace std;

class Map {
private:
	//struct UnitCoords {
	//	int x;
	//	int y;
	//	Unit u;
	//};
	//struct has a bug with VisualStudio, I'll use class
	class UnitCoords {
	public:
		int x;
		int y;
		Unit u;
		UnitCoords(int x_coord, int y_coord, Unit unit) {
			x = x_coord;
			y = y_coord;
			u = unit;
		}
	};
	int map_width;
	int map_height; //map dimensions
	vector<vector<int>> tiles;
	vector<UnitCoords> units;
public:
	int map_x() { return map_width; }
	int map_y() { return map_height; }
	Map(char * map_name);
	void add_unit(Unit u, int x, int y);
};

#endif