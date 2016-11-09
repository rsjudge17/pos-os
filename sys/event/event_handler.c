/*
 * event_handler.c
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#include "event_handler.h"

struct _event_handler_t {
	uint32_t(*func)(void*, void*);
	uint16_t prio;
	void* data;
};


void eventHandlerCreate(eventHandler_p hnd, uint16_t prio, eventDispatchingRoutine* func, void* data){
    hnd->func = func;
    hnd->prio = prio;
    hnd->data = data;
}

void eventHandlerDestroy(eventHandler_p hnd){
    hnd->func = NULL;
    hnd->prio = (uint16_t)-1;
    hnd->data = NULL;
}

uint16_t wventHandlerGetPrio(eventHandler_p hnd){
    return hnd->prio;
}

uint32_t execute(eventHandler_p hnd, void* args){
    return func(hnd->data, args);
}

void eventHandlerAttach(eventHandler_p hnd, eventDispatchingRoutine* funct){
    if(funct){
        hnd->func = funct;
    }
}
