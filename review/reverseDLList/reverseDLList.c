
#include "list.h"

void reverseDLList(List l) {
	Node prev = NULL;
    Node curr = l->last;
    while (curr != NULL) {
        Node temp = curr;
        temp->next = prev;
        prev = temp;
        curr = curr->prev;
    }
}

