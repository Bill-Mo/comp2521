// Girvan-Newman Algorithm for community discovery
// COMP2521 Assignment 2

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "FloydWarshall.h"
#include "CentralityMeasures.h"
#include "GirvanNewman.h"
#include "Graph.h"

static Dendrogram doGirvanNewman(Graph g, float highest, int *preComm);
static int *removal(Graph g, float highest, int *preComm);
static float getHighest(Graph g);
static Graph removeEdges(Graph g, float highest, int *preComm);
static bool isIn(int *preComm, int v, int nV);
static Dendrogram newLeaf(int v);
static int *components(Graph g, int *preComm, int nV);
static int *initializeArray(int nV);
static bool isSeparate (Graph g, int v, int w);
static int length(int *a, int nV);
static int *getAnother(int *preComm, int *community, int nV);
static void dofreeDendrogram(Dendrogram d);

/**
 * Generates  a Dendrogram for the given graph g using the Girvan-Newman
 * algorithm.
 * 
 * The function returns a 'Dendrogram' structure.
 */

Dendrogram GirvanNewman(Graph g) {
    float highest = getHighest(g);
    int nV = GraphNumVertices(g);
    int *community = initializeArray(nV);
    for (int i = 0; i < nV; i++) {
        community[i] = i;
    }
    Dendrogram d = doGirvanNewman(g, highest, community);
	return d;
}

static Dendrogram doGirvanNewman(Graph g, float highest, int *preComm) {
    Dendrogram d = malloc(sizeof(DNode));
    int nV = GraphNumVertices(g);
    int lenPre = length(preComm, nV);
    // Is preComm contains only one vertex
    if (lenPre == 1) {
        int v = preComm[0];
        free(preComm);
        return newLeaf(v);
    }

    int *community = removal(g, highest, preComm);
    highest = getHighest(g);
    int lenComm = length(community, nV);

    d->vertex = -1;
    // Do removal until a new parts is generated
    while (lenPre == lenComm) {
        community = removal(g, highest, community);
        highest--;
        lenComm = length(community, nV);
    }

    int *another = getAnother(preComm, community, nV);
    d->left = doGirvanNewman(g, highest, community);
    d->right = doGirvanNewman(g, highest, another);
    free(preComm);
    return d;
}

// Generate new a part
static int *removal(Graph g, float highest, int *preComm) {
    int nV = GraphNumVertices(g);
    
    g = removeEdges(g, highest, preComm);

    // Get new community
    int *community = components(g, preComm, nV);
    return community;
}
// Calculate the edge betweenness of all edges affected by the removal
static float getHighest(Graph g) {
    float highest = -2.0;
    EdgeValues e = edgeBetweennessCentrality(g);
    int nV = e.numNodes;
	for (int i = 0; i < nV; i++) {
        for (int j = 0; j < nV; j++) {
	        if (highest < e.values[i][j]) {
	            highest = e.values[i][j];
	        }
	    }
    }
    freeEdgeValues(e);
    return highest;
}

// Remove the edge(s) with the highest edge betweenness
static Graph removeEdges(Graph g, float highest, int *preComm) {
    EdgeValues e = edgeBetweennessCentrality(g);
    int nV = e.numNodes;
    for (int i = 0; i < nV; i++) {
	    for (int j = 0; j < nV; j++) {
	        if (highest == e.values[i][j]) {
	            if (isIn(preComm, i, nV) && isIn(preComm, j, nV)) {
	                GraphRemoveEdge(g, i, j);
	            }
	        }
	    }
    }
    freeEdgeValues(e);
    return g;
}

// Check is vertex in array
static bool isIn(int *preComm, int v, int nV) {
    for (int i = 0; i < nV; i++) {
        if (preComm[i] == v) {
            return true;
        }
    }
    return false;
}

// Create a new leaf
static Dendrogram newLeaf(int v) {
    Dendrogram new = malloc(sizeof(DNode));
    new->vertex = v;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Generate an array of components
static int *components(Graph g, int *preComm, int nV) {
    int *community = initializeArray(nV);
    int j = 0;
    for (int i = 0; i < nV && preComm[i] != -1; i++) {
        if (!isSeparate(g, preComm[0], preComm[i])) {
            community[j] = preComm[i];
            j++;
        }
    }
    return community;
}

// Initialize an array with -1 in
static int *initializeArray(int nV) {
    int *a = (int *)malloc(nV * sizeof(int));
    for (int i = 0; i < nV; i++) {
        a[i] = -1;
    }
    return a;
}

// Check is two vertices loss connection
static bool isSeparate (Graph g, int v, int w) {
    ShortestPaths sps = FloydWarshall(g);
    if (sps.dist[v][w] != INFINITY || sps.dist[w][v] != INFINITY) {
        return false;
    }
    return true;
}

// Get the length of an array
static int length(int *a, int nV) {
    int len = 0;
    for (int i = 0; i < nV && a[i] != -1; i++) {
        len++;
    }
    return len;
}

// Generate a list contains vertices which is in preComm but not in community
static int *getAnother(int *preComm, int *community, int nV) {
    int *a = initializeArray(nV);
    int j = 0;
    for (int i = 0; i < nV; i++) {
        if (isIn(preComm, i, nV) && !isIn(community, i, nV)) {
            a[j] = i;
            j++;
        }
    }
    return a;
}

/**
 * Frees all memory associated with the given Dendrogram  structure.  We
 * will call this function during testing, so you must implement it.
 */
void freeDendrogram(Dendrogram d) {
    dofreeDendrogram(d);	
}

static void dofreeDendrogram(Dendrogram d) {
    if (d != NULL) {
        dofreeDendrogram(d->left);
        dofreeDendrogram(d->right);
    }
    free(d);
}
