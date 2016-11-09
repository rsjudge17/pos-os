/*
 * event_andler.h
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#ifndef SYS_INCLUDE_EVENT_HANDLER_H_
#define SYS_INCLUDE_EVENT_HANDLER_H_


#include "event_types.h"

typedef struct _event_handler_t* eventHandler_p;

/** Creates an EventHandler with up to two arguments: the event dispatching function
 * and a fixed priority
 *
 * @param func Dispatching routine to be invoked to process a published event.
 * @param data event handler attached data object reference
 * @param prio EventHandler priority in the range: 0[max] - 65535[min].
 */
void eventHandlerCreate(eventHandler_p hnd, uint16_t prio, eventDispatchingRoutine* func, void* data);

void eventHandlerDestroy(eventHandler_p hnd);

/** Gets the EventHandler priority.
 *
 * @returns EventHandler priority
 */
uint16_t eventHandlerGetPrio(eventHandler_p hnd);

/** Executes its dispatching function to process a published event.
 *
 * @param args data reference to be notified about the event processing.
 * @returns Error code in uint32_t format or 0 if success.
 */
uint32_t eventHandlerExecute(eventHandler_p hnd, void * args);

/** Attaches a dispatching function to this handler, if NULL is passed, then has no effect.
 *
 * @param func Dispatching function to be invoked for event processing.
 */
void eventHandlerAttach(eventHandler_p hnd, eventDispatchingRoutine* func);


#endif /* SYS_INCLUDE_EVENT_HANDLER_H_ */
