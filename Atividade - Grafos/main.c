#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void testar_arquivo(const char* nome_arquivo, int vertice_origem, int vertice_destino) {
    printf("\n=== Testando arquivo: %s ===\n", nome_arquivo);
   
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Erro: Arquivo %s não encontrado!\n", nome_arquivo);
        return;
    }
    
    int num_vertices;
    fscanf(arquivo, "%d", &num_vertices);
    fclose(arquivo);
    
    Grafo* g = criar_grafo(num_vertices);
    carregar_arquivo(g, nome_arquivo);

    printf("\n[BFS] Caminho de %d para %d:\n", vertice_origem, vertice_destino);
    bfs(g, vertice_origem, vertice_destino);

    printf("\n[DFS] A partir de %d:\n", vertice_origem);
    dfs_pilha(g, vertice_origem);
    
    liberar_grafo(g);
}

int main() {

    const char* arquivos[] = {
        "pcv4.txt",
        "pcv10.txt",
        "pcv50.txt",
        "pcv177.txt"
    };
    
    int testes[][2] = {
        {0, 3}, 
        {0, 9},  
        {0, 49}, 
        {0, 176}
    };
    
    for (int i = 0; i < 4; i++) {
        testar_arquivo(arquivos[i], testes[i][0], testes[i][1]);
    }
    
    return 0;
}