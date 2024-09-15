#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************     TASK     *****************************************/

/* A directed graph G=(V,E) including n vertices is represented with an adjacency matrix mat.
 * Write the function
 *
 * void loop (int **mat, int n, int k);
 *
 * which displays all loops in the graph of size k, i.e., all loops including exactly k vertices.
 * For example, given the following graph
 * 0  →  1
 * ↑  ↘  ↓
 * 3  ←  2
 * the function must print the following sequences:
 * 0 2 3
 * 2 3 0
 * 3 0 2
 * */

// My thought process
/* when you find a 1 in the matrix, take the column index of that 1
 * and put it in the function as row, save the row of the 1 as well
 * if you find another 1, again use the column index as input to row index,
 * when you do this k times, if you arrive to the same row you saved in the beginning,
 * this is a loop with k number of vertices. if you don't arrive to the same row,
 * terminate the function and go back to the first loop and continue where you left of
 */

void loop (int **mat, int n, int k);
void DFS (int **mat, int n, int k, int *array, int startRowIndex, int row, int count);

int main() {
    // Example matrix
    int *mat[] = {
            (int[]) {0, 1, 1, 0},
            (int[]) {0, 0, 1, 0},
            (int[]) {0, 0, 0, 1},
            (int[]) {1, 0, 0, 0}
    };
    loop(mat, 4, 3);
    return 0;
}

void loop (int **mat, int n, int k) {
    int *array = (int *) malloc(sizeof(int)*k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                printf("LOOP Func. -> startRowIndex: %d\ti: %d\tj: %d\t count: %d\n", i, i, j, 1);
                array[0] = i;
                DFS(mat, n, k, array, i, j, 1);
            }
        }
    }
}

void DFS(int **mat, int n, int k, int *array, int startRowIndex, int row, int count) {
    if (count >= k) {
        if (row == startRowIndex) {
            printf("Array: ");
            for (int i = 0; i < k; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
            return;
        }
        printf("DFS Func. IF  -> startRowIndex: %d\trow: %d\tcount: %d\n", startRowIndex, row, count);
        return;
    }

    for (int j = 0; j < n; j++) {
        if (mat[row][j] == 1) {
            array[count] = row;
            printf("DFS Func. FOR -> startRowIndex: %d\ti: %d\tj: %d\t count: %d\n", startRowIndex, row, j, count);
            DFS(mat, n, k, array, startRowIndex, j, count+1);
        }
    }

}