#ifndef GRAFO_H
#define GRAFO_H

typedef struct {
    int** matriz;
    int** lista;
    int* tamanho_lista;
    int num_vertices;
} Grafo;

Grafo* criar_grafo(int n);
void carregar_arquivo(Grafo* g, const char* nome_arquivo);
void bfs(Grafo* g, int source, int target);
void dfs_pilha(Grafo* g, int source);
void liberar_grafo(Grafo* g);

#endif