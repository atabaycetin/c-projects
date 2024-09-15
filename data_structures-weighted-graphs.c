#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************     TASK     *****************************************/
/*
 * A weighted, directed, and acyclic graph G = (V, E) includes n vertices. G is stored as an
 * adjacency matrix. The edges’ weights are integer values. Vertices are identified by strings
 * (of undefined length) and possess a unique attribute, i.e., their color. Each vertex can
 * be either WHITE or BLACK (defined as constants or with an enumeration type).
 * Write the function
 *
 * void longest_weight_path (int **g, int *color, char **vertex_id, int n);
 *
 * which displays the identifiers of the vertices belonging to the path whose sum of the weights
 * of its edges is maximum, and it is composed by vertices of alternate color, e.g., WHITE, BLACK,
 * WHITE, BLACK, etc., or BLACK, WHITE, BLACK, WHITE, etc.
 * For example, given the following graph the path with the maximum weight, including edges of
 * alternate color, is the one including the nodes with identifiers ”this”, ”is”, ”the”, ”selected”, ”path”,
 * edges with weights 2, 3, 5, 1, and whose total weight is 2+3+5+1 = 11. The parameter g stores the adjacency
 * matrix of G, the array color reports the colors of the vertices (i.e., WHITE or BLACK), the array of strings
 * (a 2D array) vertex id stores the identifiers of the nodes, and n is the number of vertices V of the graph.
 */

void longest_weight_path (int **g, int *color, char **vertex_id, int n);
void recursivePath(int graph[11][11], int *tmp, int **sol, int n, int row, int *color, int pos,
                   int *maxWeight, int currentWeight, int prevColor, char *vertex_id[11], int *rtrn);

int main() {
    int g[11][11] = {    {0, 4, 0, 0, 2, 2, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 4, 0, 5, 0, 0, 1, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 7},
                         {0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    char *vertex_id[11] = {"this", "abc", "def", "blank", "is", "xxx", "xy", "xyz", "the", "selected", "path"};
    int color[11] = {0, 0, 1, 0, 1, 0,1, 1, 0, 1, 0};
    int n = 11;
    int tmp[11];
    int maxWeight = 0;
    int rtrn = 0;
    int *sol = (int *)malloc(sizeof(int )*n);

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (g[r][c] != 0) {
                tmp[0] = r;
                tmp[1] = c;
                recursivePath(g, tmp, &sol, n, c, color, 2, &maxWeight, g[r][c], color[r], vertex_id, &rtrn);
            }
        }
    }
    for (int i = 0; i < rtrn; i++) {
        printf("%s ", vertex_id[sol[i]]);
    }
    return 0;
}

void recursivePath(int graph[11][11], int *tmp, int **sol, int n, int row, int *color, int pos,
                   int *maxWeight, int currentWeight, int prevColor, char *vertex_id[11], int *rtrn) {
    //printf("POS: %d | ID: %s | Color: %d | currentWeight: %d \n", pos-1, vertex_id[tmp[pos-1]], color[tmp[pos-1]]);
    //printf("ROW: %d | ID: %s | Color: %d | currentWeight: %d \n", row, vertex_id[row], color[row]);

    if (color[row] == prevColor) {
        if (currentWeight > *maxWeight) {
            *rtrn = pos;
            *maxWeight = currentWeight;
            for (int i = 0; i < pos; i++) {
                (*sol)[i] = tmp[i];
            }
        }
        return;
    }

    for (int j = 0; j < n; j++) {
        if (graph[row][j] != 0) {
            tmp[pos] = j;
            recursivePath(graph, tmp, sol, n, j, color, pos + 1, maxWeight,
                          currentWeight + graph[row][j], color[row], vertex_id , rtrn);
        }
    }

    if (currentWeight > *maxWeight) {
        *rtrn = pos;
        *maxWeight = currentWeight;
        for (int i = 0; i < pos; i++) {
            (*sol)[i] = tmp[i];
        }
    }
}
