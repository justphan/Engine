#include "screen.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


void initialize_allegro(){
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
}
int main(int argc, char ** argv){
	initialize_allegro();
	Screen disp(1280, 720, false);
	disp.refresh_display(); //temp
	al_rest(10);			//temp
	return 0;
}