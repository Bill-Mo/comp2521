// calculateViralTransmission.c ... implementation of
// calculateViralTransmission function

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

/*
    You will submit only this one file.

    Implement the function "calculateViralTransmission" below.
    Read the exam paper for a detailed specification and
    description of your task.

    - DO NOT modify the code in any other files except for debugging
      purposes.
    - If you wish, you can add static variables and/or helper functions
      to this file.
    - DO NOT add a "main" function to this file.
*/
static int shortestPath(Graph g, int src, int dest);
static float power(float base, int power);

void calculateViralTransmission(Graph g, int src, int srcViralLoad,
                                double *trasmissionArray) {
    int nV = GraphNumVertices(g);
    for (int i = 0; i < nV; i++) {
        int path = shortestPath(g, src, i);
        if (path != -1) {
            trasmissionArray[i] = srcViralLoad * (power(0.6, path));
            if (trasmissionArray[i] < 10) {
                trasmissionArray[i] = 0;
            }
        }
    }
}

static int shortestPath(Graph g, int src, int dest) {
    int nV = GraphNumVertices(g);
    int visited[nV];
    for (int i = 0; i < nV; i++) {
        visited[i] = -1;
    }
    bool found = false;
    visited[src] = src;
    Queue q = QueueNew();
    QueueEnqueue(q, src);
    while (!found && !QueueIsEmpty(q)) {
        int v = QueueDequeue(q);
        if (v == dest) {
            found = true;
        } else {
            for (int w = 0; w < nV; w++) {
                if (GraphIsAdjacent(g, v, w) && visited[w] == -1) {
                    visited[w] = v;
                    QueueEnqueue(q, w);
                }
            }
        }
        
    }
    QueueFree(q);
    int path = 0;
    if(found) {
        int start = visited[dest];
        while (start != src) {
            path++;
            start = visited[start];
        }
        if (src != dest) {
            return path + 1;
        }
        return path;
    } else {
        return -1;
    }
}

static float power(float base, int power) {
    float result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
