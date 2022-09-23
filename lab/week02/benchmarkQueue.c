
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();
	
	// TODO
	// Write a benchmark test to demonstrate the difference between
	// ArrayQueue and CircularArrayQueue
	for(int i = 1; i < 40000; i++) {
	    QueueEnqueue(q, i);
	}
	for(int j = 1; j < 20000; j++) {
	    QueueDequeue(q);
	}
	for(int i = 1; i < 40000; i++) {
	    QueueEnqueue(q, i);
	}
	for(int j = 1; j < 30000; j++) {
	    QueueDequeue(q);
	}
	
	
	QueueFree(q);
}

