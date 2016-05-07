#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

class Error {
public:
	//standard if you just want to print message
	static void message(const char* window, const char* title, const char* message) {
		al_show_native_message_box(al_get_current_display(), window, title, message, NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}

	//I think has OK and Cancel buttons, returns different # depending on button pressed
	static short m_box(const char* message = "No message given",
		const char* content_title = "Error",
		const char* title = "Error") {

		switch (al_show_native_message_box(al_get_current_display(),
			title,
			content_title,
			message, NULL,
			ALLEGRO_MESSAGEBOX_ERROR)) {

		case 0: return 0; // User pressed the Cancel button
		case 1: return 1; //  "     "      "    OK     "
		case 2: return 2; // I don't understand what this does

		}
	}
};
#endif ERROR_H
