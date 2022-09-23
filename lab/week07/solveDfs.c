// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "helpers.h"
#include "Maze.h"
#include "Stack.h"

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
    Stack s = StackNew();
    StackPush(s, start);
    MazeVisit(m, start);
    while (!found && !StackIsEmpty(s)) {
        p = StackPop(s);
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
                    if (!MazeIsWall(m, c) && (visited[c.row][c.col].row == 0 && visited[c.row][c.col].col == 0)) {
                        StackPush(s, c);
                        visited[c.row][c.col] = p;
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
    StackFree(s);
    freeCellMatrix(visited);
    return false;
}
