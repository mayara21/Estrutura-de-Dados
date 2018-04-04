// Ordenação Topológica, usando busca em profundidade

#include <stdio.h>
#include <stdlib.h>

#define UNMARK 0
#define TEMPORARY_MARK 1
#define PERMANENT_MARK 2
#define LINE_MAX_SIZE 1024


typedef struct _node {
    int index, value, mark;
} node;

typedef struct _linkedNode {
    node n;
    struct _linkedNode *next;
} linkedNode;

int *adjMatrix;
node *listOfNodes;
linkedNode *finalL;

void insert_head(node n) {
    linkedNode *newNode;
    newNode = (linkedNode*) malloc(sizeof(linkedNode));
    newNode->next = finalL;
    newNode->n = n;

    finalL = newNode;
}

int visit(node *n, int quantNodes) {
    int i;

    if (n->mark == PERMANENT_MARK) return 0;
    if (n->mark == TEMPORARY_MARK) {
        printf("Not a DAG");
        exit(0);
    }

    n->mark = TEMPORARY_MARK;
    for (i = 0; i < quantNodes; i++) {

        if (adjMatrix[n->index * quantNodes + i] != 0) {
            visit(&listOfNodes[i], quantNodes);
        }
    }
    n->mark = PERMANENT_MARK;
    insert_head(*n);

    return 0;
}

int DFS_algorithm(int quantNodes) {
    int i;

    for (i = 0; i < quantNodes; i++) {
        if(listOfNodes[i].mark == UNMARK) {
            visit(&listOfNodes[i], quantNodes);
        }
    }

    return 0;
}

int main() {
    char line[LINE_MAX_SIZE];
    int i, quantNodes, m, readBytes, value;
    size_t lineSize;

    scanf("%d %d", &quantNodes, &m);

    adjMatrix = malloc(sizeof(int) * quantNodes * quantNodes);
    if (!adjMatrix) {
        printf("Trouble allocating memory");
        exit(0);
    }
    else {
        for (i = 0 ; i < quantNodes * quantNodes; i++) adjMatrix[i] = 0;
    }

    finalL = (linkedNode *) malloc(sizeof(linkedNode));
    if (!finalL) {
        printf("Trouble allocating memory");
        exit(0);
    }

    listOfNodes = (node *) malloc(sizeof(node) * quantNodes);
    if (!listOfNodes) {
        printf("Trouble allocating memory");
        exit(0);
    }

    fgets(line, LINE_MAX_SIZE, stdin); // Terminando de ler primeira linha
    for (i = 0; i < quantNodes; i++) {
        listOfNodes[i].index = i;
        listOfNodes[i].value = i + 1;
        listOfNodes[i].mark = UNMARK;

        fgets(line, LINE_MAX_SIZE, stdin);
        readBytes = 0;
        while (sscanf(line + readBytes, "%d ", &value) > 0) {
            readBytes += 2;
            adjMatrix[i * quantNodes + value - 1] = 1;
        }
    }

    DFS_algorithm(quantNodes);
    linkedNode *aux;
    for (aux = finalL; aux->next != NULL; aux = aux->next) {
        printf("%d ", aux->n.value);
    }
    printf("\n");

}
