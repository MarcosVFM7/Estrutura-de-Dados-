#include <iostream>
using namespace std;

class ListaSeq {
private:
    int dados[100];
    int tamAtual;
    int tamMax;

public:
    ListaSeq() {
        tamMax = 100;
        tamAtual = 0;
    }

    bool vazia() {
        return tamAtual == 0;
    }

    bool cheia() {
        return tamAtual == tamMax;
    }

    int tamanho() {
        return tamAtual;
    }

    int elemento(int pos) {
        if (pos <= 0 || pos > tamAtual) {
            return -1;
        }
        return dados[pos - 1];
    }

    bool modificarElemento(int pos, int novoValor) {
        if (pos <= 0 || pos > tamAtual) {
            return false;
        }
        dados[pos - 1] = novoValor;
        return true;
    }

    int posicao(int dado) {
        for (int i = 0; i < tamAtual; i++) {
            if (dados[i] == dado) {
                return i + 1;
            }
        }
        return -1;
    }

    bool insere(int pos, int dado) {
        if (cheia() || pos > tamAtual + 1 || pos <= 0) {
            return false;
        }
        for (int i = tamAtual; i >= pos; i--) {
            dados[i] = dados[i - 1];
        }
        dados[pos - 1] = dado;
        tamAtual++;
        return true;
    }

    int remove(int pos) {
        if (pos <= 0 || pos > tamAtual) {
            return -1;
        }
        int dado = dados[pos - 1];
        for (int i = pos - 1; i < tamAtual - 1; i++) {
            dados[i] = dados[i + 1];
        }
        tamAtual--;
        return dado;
    }

    void criarListaVazia() {
        tamAtual = 0;
        cout << "Lista vazia criada com sucesso!" << endl;
    }
};

int main() {
    ListaSeq lista;
    int opcao, posicao, valor;

    do {
        cout << "\nMenu de operacoes: \n";
        cout << "1. Criar lista vazia\n";
        cout << "2. Verificar se a lista esta vazia\n";
        cout << "3. Verificar se a lista esta cheia\n";
        cout << "4. Obter o tamanho da lista\n";
        cout << "5. Obter/modificar um elemento da lista\n";
        cout << "6. Inserir um elemento na lista\n";
        cout << "7. Remover um elemento da lista\n";
        cout << "8. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                lista.criarListaVazia();
                break;
            case 2:
                cout << (lista.vazia() ? "A lista esta vazia." : "A lista nao esta vazia.") << endl;
                break;
            case 3:
                cout << (lista.cheia() ? "A lista esta cheia." : "A lista nao esta cheia.") << endl;
                break;
            case 4:
                cout << "Tamanho da lista: " << lista.tamanho() << endl;
                break;
            case 5:
                cout << "Digite a posicao do elemento: ";
                cin >> posicao;
                valor = lista.elemento(posicao);
                if (valor == -1) {
                    cout << "Posicao invalida!" << endl;
                } else {
                    cout << "Elemento na posicao " << posicao << ": " << valor << endl;
                    cout << "Deseja modificar o valor? (1 - Sim / 0 - Nao): ";
                    int modificar;
                    cin >> modificar;
                    if (modificar == 1) {
                        cout << "Digite o novo valor: ";
                        cin >> valor;
                        if (lista.modificarElemento(posicao, valor)) {
                            cout << "Elemento modificado com sucesso!" << endl;
                        } else {
                            cout << "Falha ao modificar elemento!" << endl;
                        }
                    }
                }
                break;
            case 6:
                cout << "Digite a posicao para inserir o elemento: ";
                cin >> posicao;
                cout << "Digite o valor do elemento: ";
                cin >> valor;
                cout << (lista.insere(posicao, valor) ? "Elemento inserido com sucesso!" : "Falha ao inserir elemento!") << endl;
                break;
            case 7:
                cout << "Digite a posicao do elemento a ser removido: ";
                cin >> posicao;
                valor = lista.remove(posicao);
                cout << (valor == -1 ? "Falha na remocao!" : "Elemento removido: " + to_string(valor)) << endl;
                break;
            case 8:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
    } while (opcao != 8);

    return 0;
}
