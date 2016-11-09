/*
 * list.c
 *
 *  Created on: Nov 10, 2016
 *      Author: ruelsison
 */
#include "list.h"
#include <stdlib.h>
#include <string.h>

struct _linked_node_t {
	void* data;
	struct _linked_node_t* next;
	struct _linked_node_t* prev;
};

struct _list_t {
	int length;
	lnode_p first;
	lnode_p last;
	void (*destructor)(void*);
};

struct _list_iter_t {
	lnode_p current;
	char started;
};

list_p listCreate(){
	list_p list = (list_p) malloc(sizeof(struct list));
	list->length = 0;
	list->first = NULL;
	list->last = NULL;
	list->destructor = free;
	return list;
}

list_iter_p listIterator(list_p list, char init){
	list_iter_p iter = (list_iter_p)malloc(sizeof(struct list_iter));
	if(init==FRONT){
		iter->current = list->first;
	}
	else if(init==BACK){
		iter->current = list->last;
	}
	else return NULL;
	iter->started = 0;
	return iter;
}

void listAdd(list_p list, void* data, int size){
	lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
	node->data = malloc(size);
	memcpy(node->data, data, size);

	if(list->first==NULL){
		node->prev = NULL;
		node->next = NULL;
		list->first = node;
		list->last = node;
	}
	else{
		list->last->next = node;
		node->prev = list->last;
		node->next = NULL;
		list->last = node;
	}
	list->length++;
}

void* listCurrent(list_iter_p iter){
	if(iter->started&&iter->current!=NULL)
		return iter->current->data;
	return NULL;
}

void* listNext(list_iter_p iter){
	if(!iter->started&&iter->current!=NULL){
		iter->started=1;
		return iter->current->data;
	}
	if(iter->current!=NULL){
		iter->current = iter->current->next;
		return listCurrent(iter);
	}
	return NULL;
}

void* listPrev(list_iter_p iter){
	if(!iter->started&&iter->current!=NULL){
		iter->started=1;
		return iter->current->data;
	}
	if(iter->current!=NULL){
		iter->current = iter->current->prev;
		return listCurrent(iter);
	}
	return NULL;
}

void* listFirst(list_p list){
	return list->first->data;
}

void* listLast(list_p list){
	return list->last->data;
}

void* listPop(list_p list){
	lnode_p last = list->last;
	if(last == NULL) return NULL;

	if (list->first == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else {
		list->last = last->prev;
		last->prev->next = NULL;
	}

	void* data = last->data;
	free(last);
	list->length--;
	return data;
}

void* listPoll(list_p list){
	lnode_p first = list->first;

	if(first == NULL)
		return NULL;

	if (list->first == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else {
		list->first = first->next;
		first->next->prev = NULL;
	}

	void* data = first->data;
	free(first);
	list->length--;
	return data;
}

void listRemove(list_p list, char end){
	void * data;
	if(end == FRONT)
		data = listPoll(list);
	else if (end == BACK)
		data = listPop(list);
	else return;
	list->destructor(data);
}

void listDestroy(list_p list){
	lnode_p cur = list->first;
	lnode_p next;
	while(cur!=NULL){
		next = cur->next;
		list->destructor(cur->data);
		free(cur);
		cur = next;
	}
	free(list);
}

void listInsert(list_p list, lnode_p before, void *data, int size){
    if (list->first == NULL) {
        listAdd(list, data, size);
    }
    else if (before == list->last) {
        listAdd(list, data, size);
    }
    else if (before == NULL) {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = list->first;
        node->prev = NULL;
        node->next->prev = node;
        list->first = node;
        list->length++;
    }
    else {
        lnode_p node = (lnode_p)malloc(sizeof(struct linked_node));
        node->data = malloc(size);
        memcpy(node->data, data, size);

        node->next = before->next;
        node->prev = before;
        before->next = node;
        node->next->prev = node;
        list->length++;
    }
}

void* listPluck(list_p list, lnode_p removed){
    if(removed == NULL){
        return NULL;
    }
    else if(list->first == removed && list->last == removed){
        list->first = NULL;
        list->last = NULL;
    }
    else if(list->first == removed){
        list->first = removed->next;
        removed->next->prev = NULL;
    }
    else if(list->last == removed){
        list->last = removed->prev;
        removed->prev->next = NULL;
    }
    else{
        removed->prev->next = removed->next;
        removed->next->prev = removed->prev;
    }

    void* data = removed->data;
    free(removed);
    list->length--;
    return data;
}



