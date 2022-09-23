
#include "list.h"

int numDupesInOrderedList(List l) {
	int dup = 0;
	Node curr = l->head;
	while (curr != NULL) {
	    int count = -1;
	    int num = curr->value;
	    while (curr != NULL && curr->value == num) {
	        curr = curr->next;
	        count++;
	    }
	    dup += count;
	}
	return dup;
}

