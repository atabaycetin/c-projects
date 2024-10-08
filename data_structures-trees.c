#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************     TASK     *****************************************/
/*
 * An n-ary tree is defined using the data structure reported below. Nodes have a string as a
 * key, and a number of children equal to n_child. The array child individuates these children.
 * For each tree, there is a corresponding set of paths, which is the set of all paths starting
 * from the root and reaching all leaves.
 * Two trees are defined to be equivalent if and only if they generate exactly the same set
 * of paths.
 * For example, the leftmost tree and the one in the middle are equivalent but the rightmost
 * is not. The two trees on the left-hand side of the picture generate the following set of
 * paths: {ABE, ABF, ABG, AC, ADHL, ADI}. On the contrary, the rightmost tree generates
 * the set of paths: {ACE, ACF, ACG, AD, ABHL, ABI}. Notice that, in this example, all keys
 * are single characters only for the sake of mutual understanding. More generally, keys
 * are strings of unknown length.
 * Write the function
 *
 * int equivalent (node_t *root1, node_t *root2);
 *
 * to verify whether two trees are equivalent or not. The function must return 1 if the two
 * trees are equivalent (they do generate the same set of paths) and must return 0, otherwise.
 * Notice that it is not advised to store the entire set of paths generated by a tree to solve
 * the problem. Moreover, it is requested a function whose cost is linear in the size of the
 * trees passed as parameters. Less time-effective or memory-effective solutions will be penalized.
 * */

// Define the structure for a tree node
typedef struct node_s {
    char *key;
    int n_child;
    struct node_s **child;
} node_t;

node_t* create_node(char *key, int n_child); // done by chatgpt to create example trees
void print_tree(node_t *root, int depth); // done by chatgpt to create example trees
void compare(node_t *root1, node_t *root2, int *count);
void countNodes (node_t *root, int *count);
void free_tree(node_t *root);
int equivalent(node_t *root1, node_t *root2);

int main() {
    // Tree 1
    node_t *A1 = create_node("A", 3);
    node_t *B1 = create_node("B", 3);
    node_t *C1 = create_node("C", 0);
    node_t *D1 = create_node("D", 3);
    node_t *E1 = create_node("E", 0);
    node_t *F1 = create_node("F", 0);
    node_t *G1 = create_node("G", 0);
    node_t *H1 = create_node("H", 0);
    node_t *I1 = create_node("I", 0);
    node_t *L1 = create_node("L", 0);

    A1->child[0] = B1;
    A1->child[1] = C1;
    A1->child[2] = D1;
    B1->child[0] = E1;
    B1->child[1] = F1;
    B1->child[2] = G1;
    D1->child[0] = H1;
    D1->child[1] = I1;
    D1->child[2] = L1;

    // Tree 2
    node_t *A2 = create_node("A", 3);
    node_t *B2 = create_node("B", 3);
    node_t *C2 = create_node("C", 0);
    node_t *D2 = create_node("D", 3);
    node_t *E2 = create_node("E", 0);
    node_t *F2 = create_node("F", 0);
    node_t *G2 = create_node("G", 0);
    node_t *H2 = create_node("H", 0);
    node_t *I2 = create_node("I", 0);
    node_t *L2 = create_node("L", 0);

    A2->child[0] = D2;
    A2->child[1] = B2;
    A2->child[2] = C2;
    D2->child[0] = H2;
    D2->child[1] = I2;
    D2->child[2] = L2;
    B2->child[0] = E2;
    B2->child[1] = F2;
    B2->child[2] = G2;

    // Tree 3
    node_t *A3 = create_node("A", 3);
    node_t *B3 = create_node("B", 2);
    node_t *C3 = create_node("C", 0);
    node_t *D3 = create_node("D", 1);
    node_t *E3 = create_node("E", 0);
    node_t *F3 = create_node("F", 0);
    node_t *G3 = create_node("G", 0);
    node_t *H3 = create_node("H", 1);
    node_t *I3 = create_node("I", 0);
    node_t *L3 = create_node("L", 0);

    A3->child[0] = D3;
    A3->child[1] = B3;
    A3->child[2] = C3;
    D3->child[0] = I3;
    B3->child[0] = E3;
    B3->child[1] = H3;
    H3->child[0] = L3;
    int d = equivalent(A1, A3);
    printf("\n%d\n", d);
    // Print Trees
    // printf("Tree 1:\n");
    // print_tree(A1, 0);
    //
    // printf("\nTree 2:\n");
    // print_tree(A2, 0);
    //
    // printf("\nTree 3:\n");
    // print_tree(A3, 0);

    // Free Trees
    free_tree(A1);
    free_tree(A2);
    free_tree(A3);


    return 0;
}

void countNodes (node_t *root, int *count) {
    for (int i = 0; i < root->n_child; i++) {
        (*count) +=1;
        countNodes(root->child[i], count);
    }
}

void compare(node_t *root1, node_t *root2, int *count) {
    if (strcmp(root1->key, root2->key) == 0 && root1->n_child == root2->n_child) {
        printf("root1: %s\troot2: %s\n", root1->key, root2->key);
        (*count) +=1;
        for (int i = 0; i < root1->n_child; i++) {
            for (int j = 0; j < root2->n_child; j++) {
                compare(root1->child[i], root2->child[j], count);
            }
        }
    }
}

int equivalent(node_t *root1, node_t *root2) {
    int count = 0; //count needs to be included in the parameter
                   // code another function to compare
    int node_count1 = 1; // initialized as 1 to include the root 0
    int node_count2 = 1; // initialized as 1 to include the root 0
    countNodes(root1, &node_count1);
    countNodes(root2, &node_count2);
    if (node_count1 != node_count2) {
        printf("Trees are not equivalent");
        return 0;
    }
    compare(root1, root2, &count);
    printf("count: %d\n", count );
    if (count == node_count1)
        return 1;
    return 0;
}

// Function to create a new node
node_t* create_node(char *key, int n_child) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->key = key;
    new_node->n_child = n_child;
    if (n_child > 0) {
        new_node->child = (node_t **)malloc(n_child * sizeof(node_t *));
    } else {
        new_node->child = NULL;
    }
    return new_node;
}

// Function to print the tree
void print_tree(node_t *root, int depth) {
    for (int i = 0; i < depth; ++i) printf("  ");
    printf("%s\n", root->key);
    for (int i = 0; i < root->n_child; ++i) {
        print_tree(root->child[i], depth + 1);
    }
}

// Function to free the tree memory
void free_tree(node_t *root) {
    for (int i = 0; i < root->n_child; ++i) {
        free_tree(root->child[i]);
    }
    free(root->child);
    free(root);
}