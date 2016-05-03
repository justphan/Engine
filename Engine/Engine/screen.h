#ifndef SCREEN_H
#define SCREEN_H

#include <allegro5/allegro.h>

class Screen{
private:
	int width;
	int height;
	bool fullscreen;
	ALLEGRO_DISPLAY * display;
public:
	Screen(int x, int y, bool fscreen);
	~Screen();
	void refresh_display();
	void set_resolution(int x, int y);
	void set_fullscreen(bool f);

	int get_height();
	int get_width();
	bool get_fullscreen();
	ALLEGRO_DISPLAY * get_display();
};

#endif