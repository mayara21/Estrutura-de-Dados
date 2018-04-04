// Árvore Binária para classificação de IPs de acordo com máscaras determinadas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crio minha estrutura de arvore binária para armazenar meus IPs e as máscaras associadas
typedef struct _BTREE {
    struct _BTREE *left, *right;
    char mask[256];
} BTREE;


void insertOnTree(BTREE **tree, char *bits, int turn, int nbits, char *dns) { // Insiro o IP na árvore
    //int i = 0;

    if (turn < nbits) {
        if (bits[turn] == '0') {
            if (((*tree)->left) == NULL) {
                (*tree)->left = malloc(sizeof(BTREE));
                if(!((*tree)->left)){
                  printf("Problema alocando memória");
                }
                (*tree)->left->left = NULL;
                (*tree)->left->right = NULL;
                strcpy((*tree)->left->mask, "");
            }
            insertOnTree(&(*tree)->left, bits, turn + 1, nbits, dns);
        }
        if (bits[turn] == '1') {
            if (((*tree)->right) == NULL) {
                (*tree)->right = malloc(sizeof(BTREE));
                if(!((*tree)->right)){
                  printf("Problema alocando memória");
                }
                (*tree)->right->left = NULL;
                (*tree)->right->right = NULL;
                strcpy((*tree)->right->mask, "");
            }
            insertOnTree(&(*tree)->right, bits, turn + 1, nbits, dns);
        }
    }
    else {
        strcpy((*tree)->mask, dns);
        // Copio o dns associado ao IP para a máscara da árvore (no caso, copio assim que ultrapassar o números
        // de bits especificado)
    }
}

void findOnTree(BTREE *tree, char *bits, int turn, char **result) { // Procuro a máscara associada ao IP na árvore
    if (turn < 32) {
        if (bits[turn] == '0') {
            if (tree->left != NULL) {
                findOnTree(tree->left, bits, turn + 1, result);
            }
        }
        else {
            if (tree->right != NULL) {
                findOnTree(tree->right, bits, turn + 1, result);
            }
        }
    }
    //printf("%d\t\t\t%s\t\t\t%s\n", turn, tree->mask, *result);
    if ((*result)[0] == '\0')
        *result = tree->mask;
}

char* decToBinary (int num) { // Função para converter para binário
    char *result;
    result = malloc(sizeof(char) * 9);
    if(!result){
      printf("Problema alocando memória");
    }
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = '0';
    }
    result[8] = '\0';
    i = 7;
    do {
        if (num % 2) {
            result[i] = '1';
        }
        else {
            result[i] = '0';
        }
        i--;
        num /= 2;
    } while (num > 0);
    return result;
}

// Função criada para checar se a arvore estava sendo montada corretamente

/*
void printTree(BTREE *tree) {
    if (tree->mask[0] != '\0') {
        printf("%s\n", tree->mask);
    }
    if (tree->left != NULL) {
        printTree(tree->left);
    }
    if (tree->right != NULL) {
        printTree(tree->right);
    }
}
*/
int main(int argc, char const *argv[]){
    int i, j, quant, numBits, count = 0, turn = 0, whichByte = 0, ipCounter,
        ip[4];
    char c, num[4], stringao[33], dns[256], search[256], *resultSearch;

    resultSearch = malloc(sizeof(char) * 256);
    if(!resultSearch){
      printf("Problema alocando memória");
    }

    FILE *f;
    /*if(argc > 1){
      f = fopen(argv[1], "r");
    }
    */

    f = fopen("entrada.txt",  "r"); // Abro o meu arquivo contendo os IPs
    if(!f){
      printf("Problema abrindo arquivo");
    }


    BTREE *test;
    test = malloc(sizeof(BTREE));
    if(!test){
      printf("Problema alocando memória");
    }

    fscanf(f, "%d", &quant);
    for(i = 0; i < quant; i++){ // Leio os IPs e suas máscaras
        for (j = 0; j < 32; j++) {
            stringao[j] = '0';
        }

        fscanf(f, "%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &numBits);

        for (j = 0; j < 4; j++) {
            strcpy(&stringao[j*8], decToBinary(ip[j]));
            // Copio a conversão binária dos números do meu IP para uma string
            // Multiplico por 8 porque cada numero convertido terá 8 bits, totalizando 32 na string
        }
        fscanf(f, "%c", &c); // Pula o espaço entre a máscara e o DNS
        fscanf(f, "%[^\n]", &dns); // Pega o restante da linha, armazenando a máscara associada
        //printf("%s %d %s\n", stringao, numBits, dns);
        insertOnTree(&test, stringao, 0, numBits, dns); // Chamo a função para inserir o IP na árvore
    }
    //printTree(test);
    getchar();
    fscanf(f, "%s", search);
    while (!feof(f)) { // Enquanto o arquivo não terminar, leio os IPs que preciso identificar

        sscanf(search, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
        for (j = 0; j < 4; j++) {
            strcpy(&stringao[j*8], decToBinary(ip[j]));
        }

        resultSearch[0] = '\0';
        findOnTree(test, stringao, 0, &resultSearch); // Procuro na árvore o IP, e "retorno" a máscara associada
        //puts(resultSearch);
        printf("%s %s\n", search, resultSearch);
        fscanf(f, "%s", search);
    }
    fclose(f);
    return 0;
}
