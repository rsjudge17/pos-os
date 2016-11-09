/*
 * event.h
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#ifndef SYS_INCLUDE_EVENT_H_
#define SYS_INCLUDE_EVENT_H_



#include "list.h"
#include "event_handler.h"

typedef struct _event_t* event_p;
/** Event class
 *
 * Events are the inter-process communication mechanism within the EventFramework. Each
 * event registered in the framework stands for a type of signal, which can accept
 * attached data to be processed by any processing entity; in this case by EventHandlers
 * through its attached EventDispatchingRoutine.
 * Each event has a fixed priority in the range: 0 (max) to 65535 (min) and can keep track
 * of a list of installed EventHandlers to invoke when the event is published. Published
 * events are queued into a PendingList managed by the EventFramework scheduler, who will
 * dispatch them accordingly with their priority (from highest to lowest).
 */

/** Creates an Event with a specified priority
 *
 * @param prio Event priority. Range 0[max] - 65535[min]
 */
void eventCreate(event_p event, uint16_t prio);
void eventDestroy(event_p event);

/** Gets the Event priority.
 *
 * @returns event priority
 */
uint16_t eventGetPrio(event_p event);

/** Gets the base event reference
 *
 * To explain the way in which a base reference is used, it is necessary to explain what
 * happens on event publishing. Within the framework, only registered events can be published.
 * while publishing an event of one type, a new event is allocated (by: new Event()) and it is referenced
 * to the existing one by its private [base] property. This base reference allows the scheduler to invoke
 * to all its listeners.
 *
 * @returns event reference to the base event.
 */
event_p   eventGetBase(event_p event, void);

/** Sets the Event reference to which this is based from.
 *
 * @param ev event reference to link with.
 */
void     eventSetBase(event_p event, event_p base);

/** Sets attached data to the Event.
 *
 * Events can attach extra data to be processed by the listener. Through this interface, a data
 * reference can be attached to the event.
 *
 * @param data data reference to be attached to the event for further processing.
 */
void     eventSetData(event_p event, void* data);

/** Gets event's attached data.
 *
 * @returns reference to the attached data.
 */
void*    eventGetData(event_p event);

/** Adds an EventHandler to process this kind of events.
 *
 * Each event manages an internal list of handlers. If an event of this kind is published
 * all handlers in this list will be fired to process the event.
 *
 * @param hnd EventHandler reference to subscribe to this Event.
 */
void     eventSubscribe(event_p event, eventHandler_p hnd);

/** Erases an EventHandler to stop processing this kind of events.
 *
 * @param hnd EventHandler reference to unsubscribe from this Event.
 */
void     eventUnsubscribe(event_p event, eventHandler_p hnd);

/** Gets the list of subscribed EventHandlers
 *
 * @returns reference to the list of subscribed EventHandlers.
 */
list_p    eventGetList(event_p event);

#endif /* SYS_INCLUDE_EVENT_H_ */
