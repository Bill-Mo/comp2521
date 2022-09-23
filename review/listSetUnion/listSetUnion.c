
#include "list.h"

List listSetUnion(List s1, List s2) {
	/*List l1 = listSortedCopy(s1);
    List l2 = listSortedCopy(s2);
    Node curr = l1->head;
    int len = 1;
    while (curr->next != NULL) {
        curr = curr->next;
        len++;
    }
    curr->next = l2->head;
    Node last1 = curr;
    while(curr->next != NULL) {
        for (Node n1 = l1->head; n1 != last1; n1 = n1->next) {
            if (curr->next->value == n1->value) {
                Node temp = curr->next;
                curr->next = curr->next->next;
                free(temp);
            }
        }
        curr = curr->next;
    }
    return l1;*/
    List l1 = newList();
    Node first = s1->head;
    Node b = newNode(first->value);
    l1->head = b;
    while (first != NULL) {
        b = newNode(first->value);
        b = b->next;
        first = first->next;
    }
    return l1;
}

