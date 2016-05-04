#ifndef MAINMENU_H
#define MAINMENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class MainMenu{
private:
	ALLEGRO_FONT * title = al_load_ttf_font("a_font.ttf", 72, 0); //may replace to ALLEGRO_BITMAP if we get a logo
	//need boxes for: New Game, Load Game, Exit (for now)

	ALLEGRO_FONT * options = al_load_ttf_font("a_font.ttf", 24, 0);

	class Box_Data { //for storing data needed to draw each of the boxes, depends on current resolution
	public:
		float x_start = 0;
		float y_start = 0;
		float x_end;
		float y_end;
		bool rounded;
		float radi;
		char * text;
		int type; //type of box, update here if more boxes are necessary
		// 0 -> main menu box;
		Box_Data(int width, int height, int t, bool round, char * str) {
			type = t;
			rounded = round;
			text = str;
			if (type == 0) { //main menu box
				x_end = width / 7; //both of these surely still need to be adjusted
				y_end = height / 10;
			}
		}
		float offset_x(float offset) {
			return (x_end + offset);
		}
		float offset_y(float offset) {
			return (y_end + offset);
		}
		bool round() {
			return rounded;
		}
	};

	Box_Data * new_game = NULL;
	Box_Data * load_game = NULL;
	Box_Data * exit = NULL;

	ALLEGRO_COLOR background = al_map_rgb(0, 0, 0); //currently black
public:
	MainMenu(int width, int height) {
		new_game = new Box_Data(width, height, 0, true, "New Game");
		load_game = new Box_Data(width, height, 0, true, "Load Game");
		exit = new Box_Data(width, height, 0, true, "Exit");
	}
	~MainMenu() {
		delete new_game;
		delete load_game;
		delete exit;
	}
};

#endif