#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INFINITO 100000
#define MAX 101010

int analise[MAX];
int dist[MAX];

typedef struct no{
	int u; //vértice
    int w; //peso
	struct no *prox;
} no;

void dijkstra(no *grafo, int s, int n_vert){

	no *aux;

    int v;
    
    //SETANDO O VETOR DISTÂNCIA COMO INFINITO
	for (int i = 0; i < n_vert; ++i)
		dist[i] = INFINITO;

    //SETANDO TODOS OS VÉRTICES COMO NÃO VISITADOS
	memset(analise, false, sizeof(analise));

	dist[s] = 0;
	// Percorrer todas as vértices verificando se elas já foram vitadas
	for (int i = 0; i < n_vert; ++i){

		v = -1;

		for (int j = 0; j < n_vert; ++j){
			if (analise[j] == false && (v == -1 || dist[j] < dist[v]))
				v = j;
		}
		if (dist[v] == INFINITO){
			break;
		}
		analise[v] = true; //visitado

        // Percorrer todas as arestas da vértice
        aux = grafo[v].prox;

        while (aux != NULL){

            int vertex = aux->u;
			int peso = aux->w;
            
            //RELAXAMENTO
			if (dist[vertex] > dist[v] + peso)
				dist[vertex] = dist[v] + peso;
                
            aux = aux->prox;
        }
	}
}


no *inicializar_grafo(int n_vert){
    no *grafo = (no *)malloc(sizeof(no) * (n_vert + 1)); //vetor
    for (size_t i = 0; i < (n_vert + 1); i++){
        grafo[i].prox = NULL;
    }

    return grafo;
}

void leitura(no *grafo, int u, int v, int peso){

    no *novo = (no *) malloc(sizeof(no));

    novo->u = u;
	novo->w = peso; 

	novo->prox = grafo[v].prox;
	grafo[v].prox = novo;
}

int main(){	

	int i;
	int n, m, c, k;
    int u, v, p;

	for(;;){	

        scanf("%d %d %d %d", &n, &m, &c, &k);
        if (c == 0 && n == 0 && m == 0 && k == 0) {
            break;
        }

		no *grafo = inicializar_grafo(n + 1);

		for (i = 0; i < m; ++i){

			scanf("%d %d %d", &u, &v, &p);

			if (((v < c) && (u < c) && (abs(u - v) == 1)) || (u >= c && v >= c) ){
				leitura(grafo, u, v, p), leitura(grafo, v, u, p);
			}
			if ((u >= c) && (v < c)){
				leitura(grafo, v, u, p);
			}
			if ((v >= c) && (u < c)){
				leitura(grafo, u, v, p);
			}
		}

		dijkstra(grafo, k, n);
		printf("%d\n", dist[c - 1]);

		
		while (grafo != NULL) {
    		no *NoFREE = grafo;
   			grafo = grafo->prox;
    		free(NoFREE);
		}

		free(grafo);

	}
	return 0;
}