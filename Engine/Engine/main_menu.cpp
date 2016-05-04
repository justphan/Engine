#include "main_menu.h"


MainMenu::MainMenu(int width, int height, ALLEGRO_COLOR color) {
	new_game = new Box_Data(width, height, 0, true, "New Game");
	load_game = new Box_Data(width, height, 0, true, "Load Game");
	exit_game = new Box_Data(width, height, 0, true, "Exit");
	background = color;
	w = width;
	h = height;
}
MainMenu::~MainMenu() {
	delete new_game;
	delete load_game;
	delete exit_game;
	al_destroy_font(title);
	al_destroy_font(options);
}

void MainMenu::draw_main_menu(int select) {
	al_clear_to_color(background);
	// --------------------------Start Boxes-----------------------------

	float y_offset = h / 8;
	float x_origin = w / 2;
	x_origin -= (new_game->x_end) / 2;
	float x_end = x_origin + (new_game->x_end);
	float y_origin = h / 1.8;
	float y_end = y_origin + (new_game->y_end);
	float y_center = ((y_origin + y_end) / 2) - 16; //for the text later

	if (select != 1) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(0, 255, 255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(160, 160, 160), 3);
	}
	if (select == 1) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255-0, 255-255, 255-255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255-160, 255-160, 255-160), 3);
	}

	y_origin += y_offset;
	y_end = y_origin + (new_game->y_end);

	if (select != 2) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(0, 255, 255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(160, 160, 160), 3);
	}
	if (select == 2) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255 - 0, 255 - 255, 255 - 255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255 - 160, 255 - 160, 255 - 160), 3);
	}

	y_origin += y_offset;
	y_end = y_origin + (new_game->y_end);

	if (select != 3) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(0, 255, 255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(160, 160, 160), 3);
	}
	if (select == 3) {
		al_draw_filled_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255 - 0, 255 - 255, 255 - 255));
		al_draw_rounded_rectangle(x_origin, y_origin, x_end, y_end, 5, 10, al_map_rgb(255 - 160, 255 - 160, 255 - 160), 3);
	}

	//----------------------------End Boxes---------------------------

	//----------------------------Start Title-----------------------------
	al_draw_text(title, al_map_rgb(255, 255, 255), (w / 2), (h / 5), ALLEGRO_ALIGN_CENTER, "Alonzo's Game");

	if (select != 1)
		al_draw_text(options, al_map_rgb(58, 117, 89), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "New Game");
	if (select == 1)
		al_draw_text(options, al_map_rgb(0, 0, 0), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "New Game");
	y_center += y_offset;
	if (select != 2)
		al_draw_text(options, al_map_rgb(58, 117, 89), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "Load Game");
	if (select == 2)
		al_draw_text(options, al_map_rgb(0, 0, 0), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "Load Game");
	y_center += y_offset;
	if (select != 3)
		al_draw_text(options, al_map_rgb(58, 117, 89), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "Exit Game");
	if (select == 3)
		al_draw_text(options, al_map_rgb(0, 0, 0), (w / 2), (y_center), ALLEGRO_ALIGN_CENTER, "Exit Game");

	//-----------------------------End Title--------------------------------

	al_flip_display();
}