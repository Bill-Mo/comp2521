
#include "list.h"

void listReverse(List l) {
	/*Node prev = NULL;
	Node curr = l->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		temp->next = prev;
		prev = temp;
	}
	l->head = prev;*/
    Node prev = NULL;
    Node curr = l->head;
    Node temp = curr;
    //1 2 3 4
    while (curr->next != NULL) {
        prev = temp;
        curr = curr->next;
        temp = curr;
        temp->next = prev;
    }
    l->head = prev;
}

