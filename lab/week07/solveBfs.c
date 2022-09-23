// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "helpers.h"
#include "Maze.h"
#include "Queue.h"

bool solve(Maze m) {
    int height = MazeHeight(m);
    int width = MazeWidth(m);
    Cell **visited = createCellMatrix(height, width);
    Cell start = MazeGetStart(m);
    visited[start.row][start.col] = start;
    bool found = false;
    Cell c, p;
    c.row = 0;
    c.col = 0;
    Queue q = QueueNew();
    QueueEnqueue (q, start);
    MazeVisit(m, start);
    while (!found && !QueueIsEmpty(q)) {
        p = QueueDequeue(q);
        int top, bot, left, right;
        if (p.row == 0) {
            top = 0;
            bot = 1;
            //Start at top left corner
            if (p.col == 0) {
                left = 0;
                right = 1;
            //Start at top right corner
            } else if (p.col == width - 1) {
                left = 1;
                right = 0;
            //Start at top
            } else {
                left = 1;
                right = 1;
            }
        } else if (p.row == height - 1) {
            top = 1;
            bot = 0;
            //Start at lower left corner
            if (p.col == 0) {
                left = 0;
                right = 1;
            //Start at right lower corner
            } else if (p.col == width - 1) {
                left = 1;
                right = 0;
            //Start at bottom
            } else {
                left = 1;
                right = 1;
            }
        //Start at middle
        } else {
            top = 1;
            bot = 1;
            left = 1;
            right = 1;
        }
        //Visit surrounding path
        for (int i = -top; i <= bot && !found; i++) {
            for (int j = -left; j <= right && !found; j++) {
                c.row = p.row + i;
                c.col = p.col + j;
                if ((i == 0 && j != 0) || (i != 0 && j == 0)) {
                    if (!MazeIsWall(m, c) && visited[c.row][c.col].row == 0 && visited[c.row][c.col].col == 0) {
                        visited[c.row][c.col] = p;
                        QueueEnqueue(q, c);
                    }
                }
            }
        }
        found = MazeVisit(m, p);
    }
    if (found) {
        Cell track = p;
        while (track.row != start.row || track.col != start.col) {
            MazeMarkPath(m, track);
            track = visited[track.row][track.col];
        }
        MazeMarkPath(m, start);
        return true;
    }
    QueueFree(q);
    freeCellMatrix(visited);
    if (found) {
    
    }
    return false;
}



int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL);
	
	// have to return the size of int array, path
	int arraySize = 0;

	// create an array which keep tracks of predecessor and whether it has been 
	// visited or not
	int *prev = calloc(g->nV, sizeof(int));

	// update
	// since Azores is 0, calloc will not work
	// change it to -1
	for (int i = 0; i < g->nV; i++) {
		prev[i] = -1;
	}

	// check if calloc succeeded
	assert(prev != NULL);

	// src visited should be src
	prev[src] = src;

	// create a queue for breadth first search
	Queue q = QueueNew();

	// enqueue src vertex to the queue
	QueueEnqueue(q, src);

	// perfrom Bfs 
	while (!QueueIsEmpty(q)) {

		// get the first vertex in the queue
		Vertex currentVertex = QueueDequeue(q);

		// reached destination
		if (currentVertex == dest) {

			// counter for index of array
			int i = 0;

			// while the vertex is not src
			while (currentVertex != src) {

				// fill in path array
				path[i] = currentVertex;

				// back track to src
				currentVertex = prev[currentVertex];

				// increment
				arraySize++;
				i++;
			}

			// increment
			path[i] = currentVertex;
			arraySize++;

			// change order of elements
			swap(g, arraySize, path);

			// free 
			free(prev);
			QueueFree(q);
	
			return arraySize;
		
		// haven't reached destination
		} else {

			// check for neighbors
			for (int neighborVertex = 0; neighborVertex < g->nV; neighborVertex++) {

				// the vertex should be adjacent, its weight shouldn't be bigger than max and haven't been visited yet
				if (0 < g->edges[currentVertex][neighborVertex] && g->edges[currentVertex][neighborVertex] <= max && prev[neighborVertex] == -1) {

					// record previously visited vertex
					prev[neighborVertex] = currentVertex;

					// enqueue the vertex
					QueueEnqueue(q, neighborVertex);
				}
			}

		}
	}

	// free 
	free(prev);
	QueueFree(q);

	return 0;
}
