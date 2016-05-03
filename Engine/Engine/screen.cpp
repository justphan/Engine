#include "screen.h"

Screen::Screen(int x, int y, bool fscreen){
	width = x;
	height = y;
	fullscreen = fscreen;
	if (fullscreen)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	else
		al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

Screen::~Screen(){
	al_destroy_display(display);
}

void Screen::refresh_display(){
	al_flip_display();
}

void Screen::set_resolution(int x, int y){
	al_destroy_display(display);
	if (fullscreen)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(x, y);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	width = x;
	height = y;
}

void Screen::set_fullscreen(bool fscreen){
	fullscreen = fscreen;
	al_destroy_display(display);
	if (fullscreen)
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	else
		al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(width, height);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

int Screen::get_height(){
	return height;
}

int Screen::get_width(){
	return width;
}

bool Screen::get_fullscreen(){
	return fullscreen;
}

ALLEGRO_DISPLAY * Screen::get_display(){
	return display;
}