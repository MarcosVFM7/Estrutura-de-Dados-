#include <iostream>
using namespace std;

const int TAM_MAX = 100;

class FilaSeq {
private:
    int dados[TAM_MAX];
    int inicio;
    int fim;
    int nElementos;

public:
    FilaSeq() {
        inicio = 0;
        fim = -1;
        nElementos = 0;
    }

    bool estaVazia() {
        return nElementos == 0;
    }

    bool estaCheia() {
        return nElementos == TAM_MAX;
    }

    int tamanho() {
        return nElementos;
    }

    int consultarInicio() {
        if (estaVazia()) {
            cout << "Fila vazia!" << endl;
            return -1; 
        }
        return dados[inicio];
    }

    void inserir(int elemento) {
        if (estaCheia()) {
            cout << "Fila cheia!" << endl;
            return;
        }
        fim = (fim + 1) % TAM_MAX;
        dados[fim] = elemento;
        nElementos++;
    }

    void remover() {
        if (estaVazia()) {
            cout << "Fila vazia!" << endl;
            return;
        }
        inicio = (inicio + 1) % TAM_MAX;
        nElementos--;
    }

    void alterarElemento(int posicao, int novoValor) {
        if (posicao < 0 || posicao >= nElementos) {
            cout << "Posicao invalida!" << endl;
            return;
        }
        int indice = (inicio + posicao) % TAM_MAX;
        dados[indice] = novoValor;
    }

    int obterElemento(int posicao) {
        if (posicao < 0 || posicao >= nElementos) {
            cout << "Posicao invalida!" << endl;
            return -1; 
        }
        int indice = (inicio + posicao) % TAM_MAX;
        return dados[indice];
    }

    void visualizarLista() {
        if (estaVazia()) {
            cout << "Fila vazia!" << endl;
            return;
        }
        cout << "Fila: ";
        for (int i = 0; i < nElementos; i++) {
            int indice = (inicio + i) % TAM_MAX;
            cout << dados[indice] << " ";
        }
        cout << endl;
    }
};

void menu() {
    FilaSeq fila;
    int opcao, valor, posicao;

    do {
        cout << "\nMenu:\n";
        cout << "1. Inserir elemento\n";
        cout << "2. Remover elemento\n";
        cout << "3. Consultar elemento do inicio\n";
        cout << "4. Obter tamanho da fila\n";
        cout << "5. Verificar se a fila esta cheia\n";
        cout << "6. Verificar se a fila esta vazia\n";
        cout << "7. Obter elemento por posicao\n";
        cout << "8. Alterar elemento por posicao\n";
        cout << "9. Visualizar lista completa\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o valor a ser inserido: ";
                cin >> valor;
                fila.inserir(valor);
                break;
            case 2:
                fila.remover();
                break;
            case 3:
                valor = fila.consultarInicio();
                if (valor != -1) {
                    cout << "Elemento do inicio: " << valor << endl;
                }
                break;
            case 4:
                cout << "Tamanho da fila: " << fila.tamanho() << endl;
                break;
            case 5:
                if (fila.estaCheia()) {
                    cout << "A fila esta cheia." << endl;
                } else {
                    cout << "A fila nao esta cheia." << endl;
                }
                break;
            case 6:
                if (fila.estaVazia()) {
                    cout << "A fila esta vazia." << endl;
                } else {
                    cout << "A fila nao esta vazia." << endl;
                }
                break;
            case 7:
                cout << "Digite a posicao do elemento: ";
                cin >> posicao;
                valor = fila.obterElemento(posicao);
                if (valor != -1) {
                    cout << "Elemento na posicao " << posicao << ": " << valor << endl;
                }
                break;
            case 8:
                cout << "Digite a posicao do elemento: ";
                cin >> posicao;
                cout << "Digite o novo valor: ";
                cin >> valor;
                fila.alterarElemento(posicao, valor);
                break;
            case 9:
                fila.visualizarLista();
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
