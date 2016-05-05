#include "map.h"


Map::Map(char * map_name) {
	int tally_x = 0;
	int tally_y = 0;
	string path = "map/";
	path += map_name;
	fstream map_file(path);
	string line;
	bool first = true;
	if (map_file.is_open()) {
		while (getline(map_file, line)) {
			istringstream s(line);
			string token;
			vector<int> row;
			while (getline(s, token, ' ')) {
				int current;
				stringstream(token) >> current;
				row.push_back(current);
			}
			if (first) {
				first = false;
				tally_x = row.size();
			}
			tiles.push_back(row);
		}
		tally_y = tiles.size();
	}
	else {
		//error opening map
		1; //pass
	}

	map_width = tally_x;
	map_height = tally_y;
}

void Map::add_unit(Unit u, int x, int y) {
	UnitCoords g(x, y, u);
	units.push_back(g);
}