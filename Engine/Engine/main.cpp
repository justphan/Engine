#include "screen.h"
#include "main_menu.h"
#include "map.h"
#include "event_manager.h"

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

	Screen disp(width, height, false); //start at 1280 by 720, implement config file later?
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
		
		if (redraw && al_is_event_queue_empty(em.event_queue)) {
			redraw = false;
			mm.draw_main_menu(selection);
		}
	}

	return 0;
}