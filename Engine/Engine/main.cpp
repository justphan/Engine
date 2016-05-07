#include "screen.h"
#include "main_menu.h"
#include "map.h"
#include "event_manager.h"
#include "error.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 60;
int width = 1280;
int height = 720; //currently hard coded!!!
bool fullscreen = false;

int initialize_allegro(){
	if (!al_init()) {
		Error::message("Error", "Initialize", "Failure to initialize Allegro.");
		return -1;
	}

	if (!al_init_font_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize font addons.");
		return -1;
	}

	if (!al_init_image_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize image addons.");
		return -1;
	}

	if (!al_init_native_dialog_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize dialog addons.");
		return -1;
	}

	if (!al_install_audio()) {
		Error::message("Error", "Initialize", "Failure to install audio.");
		return -1;
	}

	if (!al_init_acodec_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize acodec addons.");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize ttf addons.");
		return -1;
	}

	if (!al_init_primitives_addon()) {
		Error::message("Error", "Initialize", "Failure to initialize primitives addons.");
		return -1;
	}

	if (!al_install_keyboard()) {
		Error::message("Error", "Initialize", "Failure to install keyboard.");
		return -1;
	}

	if (!al_install_mouse()) {
		Error::message("Error", "Initialize", "Failure to install mouse.");
		return -1;
	}
	return 0;
}

int main(int argc, char ** argv){
	int error = initialize_allegro();
	if (error == -1) { return -1; }

	Screen disp(width, height, fullscreen); //start at 1280 by 720, implement config file later?
	MainMenu mm(width, height, al_map_rgb(0, 0, 0));
	
	ALLEGRO_TIMER * timer = al_create_timer(1 / FPS);
	if (timer == NULL) {
		Error::message("Error", "Timer", "Failure to create timer");
		return -1;
	}
	EventManager em(timer, disp.get_display());
	mm.draw_main_menu(1);

	int selection = 1;
	bool selected = false;
	bool changed = false;
	bool redraw = false;
	al_start_timer(timer);
	while (!selected) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(em.event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			break;
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (changed) {
				changed = false;
				redraw = true;
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				if (selection == 1)
					selection = 3;
				else
					selection--;
				changed = true;
				break;
			case ALLEGRO_KEY_DOWN:
				if (selection == 3)
					selection = 1;
				else
					selection++;
				changed = true;
				break;
			case ALLEGRO_KEY_ENTER:
				selected = true;
				break;
			case ALLEGRO_KEY_SPACE:
				selected = true;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
			int mouse_x = ev.mouse.x;
			int mouse_y = ev.mouse.y;
			if (mouse_x >= mm.x_bound_left() && mouse_x <= mm.x_bound_right()) {
				if (mouse_y >= mm.y_bound_top_new_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_new_game())) { //in new game box
					selection = 1;
					changed = true;
				}
				if (mouse_y >= mm.y_bound_top_load_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_load_game())) { //in new game box
					selection = 2;
					changed = true;
				}
				if (mouse_y >= mm.y_bound_top_exit_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_exit_game())) { //in new game box
					selection = 3;
					changed = true;
				}
			}
		}

		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			int mouse_x = ev.mouse.x;
			int mouse_y = ev.mouse.y;
			if (mouse_x >= mm.x_bound_left() && mouse_x <= mm.x_bound_right()) {
				if (mouse_y >= mm.y_bound_top_new_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_new_game())) { //in new game box
					selected = true;
					break;
				}
				if (mouse_y >= mm.y_bound_top_load_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_load_game())) { //in new game box
					selected = true;
					break;
				}
				if (mouse_y >= mm.y_bound_top_exit_game() && mouse_y <= (mm.y_bound_offset() + mm.y_bound_top_exit_game())) { //in new game box
					selected = true;
					break;
				}
			}
		}

		
		if (redraw && al_is_event_queue_empty(em.event_queue)) {
			redraw = false;
			mm.draw_main_menu(selection);
		}
	}

	return 0;
}