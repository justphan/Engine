#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

class Error {
public:
	static void message(const char* window, const char* title, const char* message) {
		al_show_native_message_box(al_get_current_display(), window, title, message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}

};
#endif ERROR_H
