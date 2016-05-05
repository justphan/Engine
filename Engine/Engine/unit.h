#ifndef UNIT_H
#define UNIT_H

class Unit {
private:
	bool init = false; //whether or not unit has been initialized
	//Unit Identification
	int unit_id;
	char * unit_name;
	//End unit identification

	//Unit permanent stats
	char * job;
	int max_hp;
	//End unit stats

	//Unit current stats
	int cur_hp;
	//End unit current stats

	//Unit misc data
	bool male;
	int faction; //0 = player, 1 = enemy, 3 = ally?
	//End unit misc data
public:
	//gets
	float get_percent_health() { return (cur_hp / max_hp); }
	int get_max_health() { return max_hp; }
	int get_faction() { return faction; }
	//end gets

	//sets
	void set_cur_health(int hp) { cur_hp = hp; }
	void set_max_health(int hp) { max_hp = hp; }
	void set_faction(int fac) { faction = fac; }
	int init_unit(int id, char * name) {
		if (init == false) {
			unit_id = id;
			unit_name = name;
			init = true;
			return 1;
		}
		else
			return 0;
	}
	//end sets

	Unit(int id, char * name) {
		unit_id = id;
		unit_name = name;
		init = true;
	}
	Unit() {
	}
};

#endif