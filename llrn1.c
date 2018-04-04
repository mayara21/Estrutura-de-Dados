// Left-leaning Red-Black Tree

#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

#define FALSE 0
#define TRUE 1

typedef struct _llrb_node {
    int value, color;
    struct _llrb_node *left, *right;
} llrb_node;

llrb_node** root;

int getColor(llrb_node *node) {
    if (node == NULL) return BLACK;
    else return node->color;
}

void changeColor(llrb_node *node) {
    node->color = !node->color;

    if (node->left != NULL) node->left->color = !node->left->color;
    if (node->right != NULL) node->right->color = !node->right->color;
}

llrb_node* rotate2Left(llrb_node *nodeA) {
    llrb_node *nodeB = nodeA->right;
    nodeA->right = nodeB->left;
    nodeB->left = nodeA;
    nodeB->color = nodeA->color;
    nodeA->color = RED;

    return nodeB;
}

llrb_node* rotate2Right(llrb_node *nodeA) {
    llrb_node *nodeB = nodeA->left;
    nodeA->left = nodeB->right;
    nodeB->right = nodeA;
    nodeB->color = nodeA->color;
    nodeA->color = RED;

    return nodeB;
}

llrb_node* modeRNode2Left(llrb_node *node) {
    changeColor(node);

    if (getColor(node->right->left) == RED) {
        node->right = rotate2Right(node->right);
        node = rotate2Left(node);
        changeColor(node);
    }

    return node;
}

llrb_node* modeRNode2Right(llrb_node *node) {
    changeColor(node);

    if (getColor(node->left->left) == RED) {
        node = rotate2Right(node);
        changeColor(node);
    }

    return node;
}

llrb_node* balanceTree(llrb_node *node) {

    if (getColor(node->right) == RED) node = rotate2Left(node);
    if ((node->left != NULL) && (getColor(node->right) == RED) && (getColor(node->left->left) == RED)) node = rotate2Right(node);
    if ((getColor(node->left) == RED) && (getColor(node->right) == RED)) changeColor(node);

    return node;
}

llrb_node* insertNode(llrb_node *node, int value, int *success) {
    if (node == NULL) {
        llrb_node *new;
        new = (llrb_node *) malloc(sizeof(llrb_node));
        if(!new) {
            *success = FALSE;
            return NULL;
        }
        new->value = value;
        new->color = RED;
        new->right = NULL;
        new->left = NULL;
        *success = TRUE;
        return new;
    }

    if (node->value == value) *success = FALSE;
    else {
        if (value < node->value) node->left = insertNode(node->left, value, success);
        else node->right = insertNode(node->right, value, success);
    }

    // Consertar configurações da LLRB
    if ((getColor(node->right) == RED) && (getColor(node->left) == BLACK)) node = rotate2Left(node);
    if ((getColor(node->left) == RED) && (getColor(node->left->left) == RED)) node = rotate2Right(node);
    if ((getColor(node->right) == RED) && (getColor(node->left) == RED)) changeColor(node);

    return node;
}

int insertOnLLRBTree(llrb_node **root, int value) {
    int success;
    *root = insertNode(*root, value, &success);
    if((*root) != NULL) (*root)->color = BLACK;

    return success;
}

void printTree(llrb_node *root) {
    if (root == NULL) return;
    printf("%d%c ", root->value, (root->color == RED) ? 'R' : 'N');
    if (root->left != NULL) printTree(root->left);
    if (root->right != NULL) printTree(root->right);
}

int main() {
    int value;
    root = (llrb_node**) malloc(sizeof(llrb_node*));
    *root = NULL;
    while(scanf("%d", &value) > 0) {
        insertOnLLRBTree(root, value);
    }
    printTree(*root);
    printf("\n");

    return 0;
}


/*
Entrada:
------------------------
|1 |
|2 |
|3 |
|4 |
|5 |
|6 |
Saida:
------------------------
Saida Esperada:
------------------------
|4N 2R 1N 3N 6N 5R |
*/
