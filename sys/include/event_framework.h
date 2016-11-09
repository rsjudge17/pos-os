/*
 * event_framework.h
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#ifndef SYS_INCLUDE_EVENT_FRAMEWORK_H_
#define SYS_INCLUDE_EVENT_FRAMEWORK_H_

#include "event.h"
#include "event_handler.h"
#include "event_types.h"
#include "list.h"

/** EventFramework class
 *
 * EventFramework class allows the creation of an event-driven infrastructure in which small "threads" (EventHandler
 *  instances) can handle events in a multithreaded execution context. As other traditional RTOSes, the EventFramework
 * can be configured to act as a cooperative or a fully-preemptive kernel with fixed-priority scheduling.
 * Furthermore, this kernel matches run-to-completion semantics, and hence a single-stack configuration
 * is enough to keep running this multithreaded execution environment. As all running tasks shares processor's
 * stack, a huge quantity of RAM is saved in contrast with traditional RTOSes.
 * This Framework has been designed to be extremely simple, but still powerful. Let's try it. Here comes an
 * example of use:
 *
 * @code
 * // Configuring and starting an EventFramework-based application formed by two threads who interchanges two events.
 * #include "mbed.h"
 * #include "EventFramework.h"
 *
 * // framework creation with fully-preemptive scheduling mechanism.
 * EventFramework kernel(EventFramework::SCHED_VALUE_PREEMPTIVE);
 *
 * // Events creation with priorities 0(max) and 65535(min).
 * Event ev1(65535);
 * Event ev2(0);
 *
 * // EventHandlers creation with priorities 0(max) and 65535(min)
 * EventHandler eh1(0);
 * EventHandler eh2(65535);
 *
 * // declaration of event dispatching functions that will be attached to previous EventHandlers
 * EventDispatchingRoutine ev1_handle_func;
 * EventDispatchingRoutine ev2_handle_func;
 *
 * int main() {
 *     // events must be registered into the framework
 *     kernel.AddEvent(&ev1);
 *     kernel.AddEvent(&ev1);
 *
 *     // handle [eh1] will process [ev1] events through [ev1_handle_func] routine. So it must attach that routine
 *     // handle [eh2] will process [ev2] events through [ev2_handle_func] routine. So it must attach that routine
 *     eh1.Attach(&ev1_handle_func);
 *     eh2.Attach(&ev2_handle_func);
 *
 *     // handlers are registered into the kernel to listen to specific events. [eh1] listens to [ev1], [eh2] listens to [ev2].
 *     kernel.AddEventListener(&ev1, &eh1);
 *     kernel.AddEventListener(&ev1, &eh2);
 *
 *     // application starts. In this case task [eh1] is executed through the interface EventHandler::Execute.
 *     eh1.Execute();
 *
 *     // the event-driven kernel starts its operation.
 *     while(1) {
 *         kernel.Schedule();
 *     }
 * }
 *
 * // user's implementation of the event handlers
 * uint32_t ev1_handle_func(void* me, void* args){
 *     // add code here to process ev1 events and (optionally) publish ev2 events.
 *     // howto: publishing an ev2 event and attaching the value of a variable [time].
 *     uint32_t time = 1000;
 *     kernel.PublishEvent(&ev2, (void*)time);
 * }
 *
 * uint32_t ev2_handle_func(void* me, void* args){
 *     // add code here to process ev2 events and (optionally) publish ev1 events.
 *     // howto: extracting the value of [time] variable attached to [ev1] event
 *     uint32_t time = (uint32_t)args;
 *
 *     // howto: publishing an ev1 event without data attached.
 *     kernel.PublishEvent(&ev1, 0);
 * }
 * @endcode
 *
 */

class EventFramework{
    public:
    /** Creates an EventFramework instance. This constructor accepts up to four arguments:
     *
     * @param schpol is the selected scheduling policy: EventFramework::SCHED_VALUE_COOPERATIVE or EventFramework::SCHED_VALUE_PREEMPTIVE
     * @param cbEI is a (void (*)(void)) callback to enable all the interrupts of the processor.
     * @param lock is a (void (*)(void)) callback to enter into a critial region.
     * @param unlock is a (void (*)(void)) callback to exit from a critial region.
     */
    EventFramework(uint32_t schpol, void (*cbEI)(void)=NULL, void (*lock)(void)=NULL, void (*unlock)(void)=NULL);

     /** Default destructor
     *
     * Deallocates reserved memory for an EventFramework instance.
     */
    ~EventFramework();

    /** Registers a new Event into the framework.
     *
     * @param ev Event to be registered into the framework
     */
    void AddEvent(Event* ev);

    /** Unregisters an existing Event from the framework.
     *
     * @param ev Event to be unregistered from the framework
     */
    void RemoveEvent(Event* ev);

    /** Registers a new EventHandler to listen Event notifications. It can accept up to three arguments:
     *
     * @param ev Event instance to listen to.
     * @param hnd EventHandler who will listen to [ev] events.
     * @param func Event dispatching function to attach to [hnd] for [ev] events processing.
     */
    void AddEventListener(Event* ev, EventHandler* hnd, EventDispatchingRoutine* func=NULL);

    /** Unregister an existing EventHandler listener from the framework.
     *
     * @param ev Event instance to which [hnd] is listening to.
     * @param hnd EventHandler to remove from the [ev] listener list.
     */
    void RemoveEventListener(Event* ev, EventHandler* hnd);

    /** Publish an Event with (optionally) attached data.
     *
     * @param evt Event published to be processed.
     * @param args (optional) attached data reference. If not used then set 0.
     */
    void PublishEvent(Event* evt, void* args);

    /** Configure specific features of the EventFramework.
     *
     * @param key feature key to update
     * @param value feature value to setup
     */
    void Configure(uint32_t key, uint32_t value);

    /** Gets a reference of the Event in process.
     *
     * @returns Event reference of the Event in process.
     */
    Event* GetEvent(void);

    /** Saves actual context on ISR entry. It allows ISR nesting in fully-preemptive scheduling.
     * Must be the first instruction on ISR entry.
     * Example:
     * @code
     * void ISR_Handler(void){
     *      kernel.SaveContext();
     *      // add here your isr code.
     *      ....
     *      kernel.RestoreContext();
     * }
     * @endcode
     *
     */
    void SaveContext(void);

    /** Restores previous context on ISR exit. It must be the last instruction before ISR exit.
     * Example:
     * @code
     * void ISR_Handler(void){
     *      kernel.SaveContext();
     *      // add here your isr code.
     *      ....
     *      kernel.RestoreContext();
     * }
     * @endcode
     *
     */
    void RestoreContext(void);

    /** Executes the EventFramework according with the selected scheduling policy.
     *
     */
    void Schedule(void);

    /// Feature key to select the SCHEDULING execution model
    const static uint32_t SCHED_KEY = 0x00000001;
    /// Feature value to setup the SCHEDULING model as COOPERATIVE
    const static uint32_t SCHED_VALUE_COOPERATIVE = 0;
    /// Feature value to setup the SCHEDULING model as PREEMPTIVE
    const static uint32_t SCHED_VALUE_PREEMPTIVE = 1;

    private:
    bool IsPreemptive(void);
    void AddEventToList(Event* ev, list_p list);
    void AddPendingEvent(Event* ev);
    void RemovePendingEvent(Event* ev);
    uint8_t nesting;
    uint16_t currPrio;
    void (*cbEnableInterrupts)(void);
    void (*cbLock)(void);
    void (*cbUnlock)(void);
    list_p list;
    list_p queue;
    Event* event;
    uint32_t ctflags;
};




#endif /* SYS_INCLUDE_EVENT_FRAMEWORK_H_ */
