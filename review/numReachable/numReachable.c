
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

static int *component(Graph g);
static void dfsComponent(Graph g, int v, int *componentOf, int id);

int numReachable(Graph g, int src) {
	int *comp = component(g);
	int nV = GraphNumVertices(g);
	int subGraph = comp[src];
	int count = 0;
	for (int i = 0; i < nV; i++) {
	    if (comp[i] == subGraph) {
	        count++;
	    }
	}
	return count;
}

static int *component(Graph g) {
    int nV = GraphNumVertices(g);
	int *componentOf = malloc(nV * sizeof(int));
	for (int i = 0; i < nV; i++) {
	    componentOf[i] = -1;
	}
	int compID = 0;
	for (int i = 0; i < nV; i++) {
	    if (componentOf[i] == -1) {
	        dfsComponent(g, i, componentOf, compID);
	        compID++;
	    }
	}
	return componentOf;
}

static void dfsComponent(Graph g, int v, int *componentOf, int id) {
    int nV = GraphNumVertices(g);
    componentOf[v] = id;
    for (int w = 0; w < nV; w++) {
        if (GraphIsAdjacent(g, v, w)) {
            if (componentOf[w] == -1) {
                dfsComponent(g, w, componentOf, id);
            }
        }
    }
}
