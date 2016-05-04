#ifndef MAINMENU_H
#define MAINMENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class MainMenu{
private:
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
				x_end = width / 6; //both of these surely still need to be adjusted
				y_end = height / 12;
			}
		}
		float offset_x(float offset) { return (x_end + offset); }
		float offset_y(float offset) { return (y_end + offset); }
		bool round() { return rounded; }
	};
	int w;
	int h; //resolution
	ALLEGRO_FONT * title = NULL; //may replace to ALLEGRO_BITMAP if we get a logo 
	ALLEGRO_FONT * options = NULL;
	//need boxes for: New Game, Load Game, Exit (for now)
	Box_Data * new_game = NULL;
	Box_Data * load_game = NULL;
	Box_Data * exit_game = NULL;

	ALLEGRO_COLOR background = al_map_rgb(0, 0, 0); //currently black
public:
	MainMenu(int width, int height, ALLEGRO_COLOR color);
	~MainMenu();
	void draw_main_menu(int select); //decides which box is selected; 0 = no box, 1 = new game, 2 = load game, 3 = exit
	int x_bound_left(); //returns left bound of option boxes
	int x_bound_right();
	int y_bound_top_new_game();
	int y_bound_offset();
	int y_bound_top_load_game();
	int y_bound_top_exit_game();
};

#endif