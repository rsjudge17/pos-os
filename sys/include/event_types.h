/*
 * types.h
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#ifndef SYS_INCLUDE_EVENT_TYPES_H_
#define SYS_INCLUDE_EVENT_TYPES_H_


/** Types required by the EventFramework
 *
 * These header file includes all common definitions required by the EventFramework
 * library.
 *
 */
#include <stdint.h>
#ifndef NULL
#define NULL    0
#endif

/** eventDispatchingRoutine typedef
 *
 *  Event dispatching routines must follow this typedef.
 *
 *  @param me attached data object to be notified about the event processing action.
 *  @param args event's attached data.
 *
 *  @returns error code in uint32_t format, or 0 if success.
 */
typedef uint32_t eventDispatchingRoutine(void* me, void* args);


#endif /* SYS_INCLUDE_EVENT_TYPES_H_ */
