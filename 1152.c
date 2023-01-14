#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define N 200000
int vertices[N];

// x e y são vértices


typedef struct Road {
    int x, y; 
    int distancia;
}Road;

// ORDENA A STRUCT DE ACORDO COM AS ARESTAS DE MENOR DISTÂNCIA
int compare(const void *a, const void *b){
    return (*(struct Road *)a).distancia - (*(struct Road *)b).distancia;
}

//Cria os conjuntos disjuntos
void make_set(int n){
    for (int i = 0; i <= n; ++i){
        vertices[i] = i;
    }
}

int find_set(int x){
    if (vertices[x] != x){
        vertices[x] = find_set(vertices[x]);
    }
    return vertices[x];
}

int union_set(int i, int j, int p, int *desconto, Road *grafo){
    (*desconto) += grafo[p].distancia;
    if (i > j){
        vertices[i] = j;
    } else{
        vertices[j] = i;
    }
    return 0;
}

int main(){
    for(;;){
            int m; //numero de junções (vértices)
            int n; //numero de estradas (arestas)

            int custo_total = 0;
            int desconto = 0;

            Road grafo[N]; //Vetor de Struct
    
            scanf("%d %d", &m, &n);
            if(m == 0 && n == 0) {
                break;
            }

            for (int i = 0; i < n; ++i) {  
                    //Coloca as arestas e os pesos na struct
                    scanf("%d %d %d",&grafo[i].x, &grafo[i].y, &grafo[i].distancia);
                    custo_total += grafo[i].distancia;
            }

            make_set(m);
            
            qsort(grafo, n, sizeof(grafo[0]), compare);

            for (int k = 0; k < n; ++k){
                int x = grafo[k].x;
                int y = grafo[k].y;
                int i = find_set(x);
                int j = find_set(y);
                if(i != j){
                    union_set(i , j, k, &desconto, grafo);
                }
            }

            int economia = custo_total - desconto;
            printf("%d\n", economia);    
    }
    return 0;
}