#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define PRIMEIRO_NIVEL 10

typedef struct Objeto {
    char chave[50];
    int valor;
    struct Objeto *prox;
} Objeto;

typedef struct SegundaTabela {
    Objeto **lista;  
    int tamanho;    
} SegundaTabela;

typedef struct TabelaHash {
    SegundaTabela *tabelas[PRIMEIRO_NIVEL];  
    int n;  
} TabelaHash;

// Função Hash 1 (Primeiro Nível)
int hash1(char *chave) {
    unsigned long hash = 5381;
    int c;
    while ((c = *chave++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % PRIMEIRO_NIVEL;
}

// Função Hash 2 (Segundo Nível)
int hash2(char *chave, int tamanho_segundo_nivel) {
    unsigned long hash = 0;
    int c;
    while ((c = *chave++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash % tamanho_segundo_nivel;
}

// Inicializa a tabela hash
TabelaHash* criarTabelaHash(int n) {
    TabelaHash *th = (TabelaHash*)malloc(sizeof(TabelaHash));
    th->n = n;

    for (int i = 0; i < PRIMEIRO_NIVEL; i++) {
        th->tabelas[i] = (SegundaTabela*)malloc(sizeof(SegundaTabela));
        th->tabelas[i]->tamanho = n / 10;
        th->tabelas[i]->lista = (Objeto**)calloc(th->tabelas[i]->tamanho, sizeof(Objeto*));
    }

    return th;
}

// Insere um objeto na tabela hash
void inserir(TabelaHash *th, char *chave, int valor) {
    int pos1 = hash1(chave);
    int pos2 = hash2(chave, th->tabelas[pos1]->tamanho);

    Objeto *novo = (Objeto*)malloc(sizeof(Objeto));
    strcpy(novo->chave, chave);
    novo->valor = valor;
    novo->prox = NULL;

    // Inserção no fim da lista encadeada
    if (th->tabelas[pos1]->lista[pos2] == NULL) {
        th->tabelas[pos1]->lista[pos2] = novo;
    } else {
        Objeto *atual = th->tabelas[pos1]->lista[pos2];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Busca um objeto na tabela hash
Objeto* buscar(TabelaHash *th, char *chave) {
    int pos1 = hash1(chave);
    int pos2 = hash2(chave, th->tabelas[pos1]->tamanho);

    Objeto *atual = th->tabelas[pos1]->lista[pos2];
    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;  
}

// Libera a memória alocada
void destruirTabelaHash(TabelaHash *th) {
    for (int i = 0; i < PRIMEIRO_NIVEL; i++) {
        for (int j = 0; j < th->tabelas[i]->tamanho; j++) {
            Objeto *atual = th->tabelas[i]->lista[j];
            while (atual != NULL) {
                Objeto *temp = atual;
                atual = atual->prox;
                free(temp);
            }
        }
        free(th->tabelas[i]->lista);
        free(th->tabelas[i]);
    }
    free(th);
}

int main() {
    TabelaHash *th = criarTabelaHash(100);

    // Teste de inserções (Baseado no enunciado da atividade)
    inserir(th, "Joao", 10);
    inserir(th, "Marco", 20);
    inserir(th, "Marina", 30);
    inserir(th, "Julia", 40);
    inserir(th, "Antonio", 50);
    inserir(th, "Jose", 60);

    // Teste de busca por "Marina" (exemplo)
    Objeto *obj = buscar(th, "Marina");
    if (obj != NULL) {
        printf("\nChave: %s, Valor: %d\n", obj->chave, obj->valor);
    } else {
        printf("Chave 'Marina' nao encontrada.\n");
    }

    char opcao;
    do {
        printf("\nDeseja buscar outra chave? (s/n): ");
        scanf(" %c", &opcao); 
        opcao = tolower(opcao); 
        if (opcao == 's') {
            char chave[50];
            printf("Digite a chave que deseja buscar: ");
            scanf("%s", chave);

            obj = buscar(th, chave);
            if (obj != NULL) {
                printf("Chave: %s, Valor: %d\n", obj->chave, obj->valor);
            } else {
                printf("Chave '%s' nao encontrada.\n", chave);
            }
        }
    } while (opcao == 's'); 

    destruirTabelaHash(th);
    return 0;
}
