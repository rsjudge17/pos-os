/*
 * event.c
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#include "event.h"

struct _event_t {
	uint16_t prio;
	void* data;
	list_p hlist;
	event_p base;
};


