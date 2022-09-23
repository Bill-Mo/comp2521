// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	// TODO
	if (q->size >= q->capacity) {
        q->items = realloc(q->items, 2 * q->capacity * sizeof(Item));
        if (q->items == NULL) {
		    fprintf(stderr, "couldn't resize Queue\n");
		    exit(EXIT_FAILURE);
	    }
	    q->items[q->capacity] = it;
	    q->capacity = q->capacity * 2;
	    q->size = q->size + 1;
	} else {
	    int position = q->size + q->frontIndex;
	    if (position >= q->capacity) {
	        position = position - q->capacity;
	    } 
	    q->items[position] = it;
	    q->size = q->size + 1;
	}
	/*printf("This is Enqueue, frontIndex is %d, front item is %d, size is %d, q is\n", q->frontIndex, q->items[q->frontIndex], q->size);
	for (int i = 0; i < 16; i++) {
	    printf("%d ", q->items[i]);
	}
	printf("\n");*/
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	// TODO
	Item deleted = q->items[q->frontIndex];
	q->items[q->frontIndex] = 0;
	q->size = q->size - 1;
	q->frontIndex = q->frontIndex + 1;
	if (q->frontIndex >= q->capacity) {
	    q->frontIndex = q->frontIndex - q->capacity;
	}
	/*printf("This is Dequeue, frontIndex is %d, front item is %d, size is %d\nq is ", q->frontIndex, q->items[q->frontIndex], q->size);
	for (int i = 0; i < 16; i++) {
	    printf("%d ", q->items[i]);
	}
	printf("\n");*/
	return deleted;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

