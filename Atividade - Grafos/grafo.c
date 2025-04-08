#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

Grafo* criar_grafo(int n) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->num_vertices = n;


    g->matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->matriz[i] = (int*)calloc(n, sizeof(int));
    }

    g->lista = (int**)malloc(n * sizeof(int*));
    g->tamanho_lista = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }

    return g;
}

void carregar_arquivo(Grafo* g, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int n;
    fscanf(arquivo, "%d", &n);

    if (n != g->num_vertices) {
        fprintf(stderr, "Número de vértices incompatível!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(arquivo, "%d", &g->matriz[i][j]);
            if (g->matriz[i][j] != 0) {
                g->tamanho_lista[i]++;
                g->lista[i] = (int*)realloc(g->lista[i], g->tamanho_lista[i] * sizeof(int));
                g->lista[i][g->tamanho_lista[i] - 1] = j;
            }
        }
    }

    fclose(arquivo);
}

// Função recursiva para imprimir o caminho (usada pelo BFS)
void imprimir_caminho(int* pred, int target) {
    if (pred[target] == -1) {
        printf("%d", target);
        return;
    }
    imprimir_caminho(pred, pred[target]);
    printf(" -> %d", target);
}

void bfs(Grafo* g, int source, int target) {
    int* visitados = (int*)calloc(g->num_vertices, sizeof(int));
    int* pred = (int*)malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) pred[i] = -1;

    int* fila = (int*)malloc(g->num_vertices * sizeof(int));
    int inicio = 0, fim = 0;

    fila[fim++] = source;
    visitados[source] = 1;

    while (inicio < fim) {
        int v = fila[inicio++];
        for (int i = 0; i < g->tamanho_lista[v]; i++) {
            int u = g->lista[v][i];
            if (!visitados[u]) {
                visitados[u] = 1;
                pred[u] = v;
                fila[fim++] = u;
            }
        }
    }

    if (pred[target] == -1 && source != target) {
        printf("Não há caminho entre %d e %d\n", source, target);
    } else {
        printf("Caminho BFS de %d para %d: ", source, target);
        imprimir_caminho(pred, target);
        printf("\n");
    }

    free(visitados);
    free(pred);
    free(fila);
}

// DFS iterativo com pilha (não recursivo)
void dfs_pilha(Grafo* g, int source) {
    int* visitados = (int*)calloc(g->num_vertices, sizeof(int));
    int* pilha = (int*)malloc(g->num_vertices * sizeof(int));
    int topo = 0;

    pilha[topo++] = source;
    visitados[source] = 1;

    printf("DFS a partir de %d: ", source);

    while (topo > 0) {
        int v = pilha[--topo];
        printf("%d ", v);

        for (int i = g->tamanho_lista[v] - 1; i >= 0; i--) {
            int u = g->lista[v][i];
            if (!visitados[u]) {
                visitados[u] = 1;
                pilha[topo++] = u;
            }
        }
    }

    printf("\n");
    free(visitados);
    free(pilha);
}

void liberar_grafo(Grafo* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        free(g->matriz[i]);
        free(g->lista[i]);
    }
    free(g->matriz);
    free(g->lista);
    free(g->tamanho_lista);
    free(g);
}