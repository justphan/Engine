#include "screen.h"
#include "main_menu.h"
#include "map.h"
#include "event_manager.h"
#include "unit.h"

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

void initialize_allegro(){
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
}

int main(int argc, char ** argv){
	initialize_allegro();

	Screen disp(width, height, fullscreen); //start at 1280 by 720, implement config file later?
	MainMenu mm(width, height, al_map_rgb(0, 0, 0));
	
	ALLEGRO_TIMER * timer = al_create_timer(1 / FPS);
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
	//Now you have a selction value
	if (selection == 1) {
		//start a new game
		//for now, the plan is to open a hard coded map scenario
		Unit alonzo(1, "Alonzo"); //temporary unit
		alonzo.set_cur_health(20);
		alonzo.set_max_health(20);
		alonzo.set_faction(0);
		Unit zombie(2, "Zombie");
		zombie.set_cur_health(8);
		zombie.set_max_health(22);
		zombie.set_faction(1);
	}
	if (selection == 2) {
		//load a save file
		selection = (selection + 1 - 1); //pass for now
	}
	return 0;
}