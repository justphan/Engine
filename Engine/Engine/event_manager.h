#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <allegro5/allegro.h>

class EventManager {
public:
	ALLEGRO_EVENT_QUEUE * event_queue = NULL;

	EventManager(ALLEGRO_TIMER * timer, ALLEGRO_DISPLAY * display);
	~EventManager();
};

#endif