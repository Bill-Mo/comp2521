// containsSequence.c ... implementation of containsSequence function

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
    You will submit only this one file.

    Implement the function "containsSequence" below. Read the exam paper
    for a detailed specification and description of your task.

    - DO NOT modify the code in any other files except for debugging
      purposes.
    - If you wish, you can add static variables and/or helper functions
      to this file.
    - DO NOT add a "main" function to this file.
*/

int containsSequence(List seq1, List seq2) {
    Node f = seq1->first;
    Node s = seq2->first;
    while (s != NULL) {
        bool match = false;
        while (f != NULL) {
            if (f->value == s->value) {
                match = true;
                f = f->next;
                break;
            }
            f = f->next;
        }
        if (match == false) {
            return 0;
        }
        s = s->next;
    }
    return 1;
}

