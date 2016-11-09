/*
 * event_node.h
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */

#ifndef SYS_INCLUDE_EVENT_NODE_H_
#define SYS_INCLUDE_EVENT_NODE_H_


#include "event_types.h"

/** Node class
 *
 * Node objects are elements contained in a List, and linked to the previous and
 * next one. A Node can contain attached data as and object reference. It's a
 * utility class in the Framework to create Queues.
 *
 */
class Node{
    public:

    /** Creates a Node with a specified item attached.
     *
     * @param item data object reference to attach to this Node.
     */
    Node(void* item);
    Node();
    ~Node();

    /** Sets the reference to the next Node in the list.
     *
     * @param node node reference to the next node.
     */
    void   SetNext(Node* node);

    /** Sets the reference to the previous Node in the list.
     *
     * @param node node reference to the previous node.
     */
    void   SetPrev(Node* node);

    /** Gets the reference to the next Node in the list.
     *
     * @returns node reference to the next node.
     */
    Node*  GetNext(void);

    /** Gets the reference to the previous Node in the list.
     *
     * @returns node reference to the previous node.
     */
    Node*  GetPrev(void);

    /** Sets the attached data object item in the Node
     *
     * @param item data object reference to attach to this Node.
     */
    void   SetData(void* item);

    /** Gets the reference to the attached data object
     *
     * @returns attached data object reference.
     */
    void*  GetData(void);

    private:
    Node*  prev;
    Node*  next;
    void* data;
};



#endif /* SYS_INCLUDE_EVENT_NODE_H_ */
