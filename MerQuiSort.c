// Merge Sort e Quick Sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void quicksort(int *lista, int esq, int dir);
void msort(int *lista, int inicio, int fim);
void merge(int *lista, int inicio, int meio, int fim);
void imprime(int *lista, int quant);
void imprimePart(int *lista, int begin, int end);



int main(int argc, char *argv[]) {
	FILE *f;
	int lista[110000], i = 0, quant = 0;

	f = stdin;


	while(fscanf(f, "%d", &lista[i]) != EOF) {
		quant++;
		i++;
		if(feof(f)) break;
	}

	if (argc > 1) {
		if (!strcmp(argv[1], "-q")) quicksort(lista, 0, quant-1);
		else if (!strcmp(argv[1], "-m")) msort(lista, 0, quant-1);
		else {
			printf("Comando nao valido!\n");
			exit(1);
		}
	}

	imprime(lista, quant);

	return 0;
}


void quicksort(int *lista, int esq, int dir) {
	int i, j, pivo, temp;

	i = esq;
	j = dir;
	pivo = lista[(esq + dir)/2];

	while(i <= j) {
		while(lista[i] < pivo && i < dir) i++;
		while(lista[j] > pivo && j > esq) j--;

		if(i <= j) {
			temp = lista[i];
			lista[i] = lista[j];
			lista[j] = temp;
			i++;
			j--;
		}
	}

	if(j > esq) quicksort(lista, esq, j);
	if(i < dir) quicksort(lista, i, dir);
}


void msort(int *lista, int inicio, int fim) {
	int meio = (inicio + fim)/2;
	if(inicio < fim) {
		msort(lista, inicio, meio);
		msort(lista, meio + 1, fim);
		merge(lista, inicio, meio, fim);
	}

}

void merge(int *lista, int inicio, int meio, int fim) {
	int *listatemp, i = inicio, j = meio + 1, pos = 0;
	listatemp = (int *) malloc((fim - inicio) * sizeof(int));
	if(!listatemp) exit(1);

	while(i <= meio && j <= fim) {
		if(lista[i] <= lista[j]) {
			listatemp[pos] = lista[i];
			i++;
			pos++;
		}

		else {
			listatemp[pos] = lista[j];
			j++;
			pos++;
		}
	}

	while (i <= meio) {
		listatemp[pos] = lista[i];
		pos++;
		i++;
	}

	while (j <= fim) {
		listatemp[pos] = lista[j];
		pos++;
		j++;
	}

	for(i = 0; i < pos; i++) {
		lista[inicio + i] = listatemp[i];
	}

}

void imprime(int *lista, int quant) {
	int i;

	for(i = 0; i < quant; i++) {
		printf("%d\n", lista[i]);
	}
}
