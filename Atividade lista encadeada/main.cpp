#include <iostream>
using namespace std;

class No {
public:
    int dado;
    No* proximo;

    No(int valor) {
        dado = valor;
        proximo = nullptr;
    }
};

class ListaEncadeada {
private:
    No* cabeca;
    int tamanho;

public:
    ListaEncadeada() : cabeca(nullptr), tamanho(0) {}

    ~ListaEncadeada() {
        while (cabeca != nullptr) {
            No* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
    }

    bool estaVazia() const {
        return (cabeca == nullptr);
    }

    int obterTamanho() const {
        return tamanho;
    }

    bool obterModificarValor(int posicao, int &valor, int novoValor = -1, bool modificar = false) {
        if (posicao < 1 || posicao > tamanho) {
            return false;
        }
        No* atual = cabeca;
        int cont = 1;
        while (cont < posicao) {
            atual = atual->proximo;
            cont++;
        }
        if (modificar) {
            atual->dado = novoValor;
        }
        valor = atual->dado;
        return true;
    }

    bool inserir(int posicao, int valor) {
        if (posicao < 1 || posicao > tamanho + 1) {
            return false;
        }
        No* novoNo = new No(valor);
        if (posicao == 1) {
            novoNo->proximo = cabeca;
            cabeca = novoNo;
        } else {
            No* atual = cabeca;
            int cont = 1;
            while (cont < posicao - 1) {
                atual = atual->proximo;
                cont++;
            }
            novoNo->proximo = atual->proximo;
            atual->proximo = novoNo;
        }
        tamanho++;
        return true;
    }

    bool retirar(int posicao, int &valorRetirado) {
        if (posicao < 1 || posicao > tamanho) {
            return false;
        }
        No* removido;
        if (posicao == 1) {
            removido = cabeca;
            cabeca = cabeca->proximo;
        } else {
            No* atual = cabeca;
            int cont = 1;
            while (cont < posicao - 1) {
                atual = atual->proximo;
                cont++;
            }
            removido = atual->proximo;
            atual->proximo = removido->proximo;
        }
        valorRetirado = removido->dado;
        delete removido;
        tamanho--;
        return true;
    }

    void imprimir() const {
        No* atual = cabeca;
        cout << "Lista: ";
        while (atual != nullptr) {
            cout << atual->dado << " -> ";
            atual = atual->proximo;
        }
        cout << "NULL" << endl;
    }
};

void exibirMenu() {
    cout << "\n===== OPERACOES =====" << endl;
    cout << "1. Criar lista vazia" << endl;
    cout << "2. Verificar se a lista esta vazia" << endl;
    cout << "3. Obter tamanho da lista" << endl;
    cout << "4. Obter/modificar valor de um elemento" << endl;
    cout << "5. Inserir um elemento" << endl;
    cout << "6. Retirar um elemento" << endl;
    cout << "7. Imprimir lista" << endl;
    cout << "8. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

int main() {
    ListaEncadeada* lista = nullptr;
    int opcao;

    do {
        exibirMenu();
        cin >> opcao;

        if (opcao != 1 && lista == nullptr) {
            cout << "Crie a lista primeiro!" << endl;
            continue;
        }

        switch (opcao) {
            case 1:
                if (lista) delete lista;
                lista = new ListaEncadeada();
                cout << "Lista criada com sucesso." << endl;
                break;
            case 2:
                cout << (lista->estaVazia() ? "A lista esta vazia." : "A lista NAO esta vazia.") << endl;
                break;
            case 3:
                cout << "Tamanho da lista: " << lista->obterTamanho() << endl;
                break;
            case 4: {
                int pos, valor, novoValor;
                char escolha;
                cout << "Digite a posicao: ";
                cin >> pos;
                if (lista->obterModificarValor(pos, valor)) {
                    cout << "Valor na posicao " << pos << ": " << valor << endl;
                    cout << "Deseja modificar esse valor? (s/n): ";
                    cin >> escolha;
                    if (escolha == 's' || escolha == 'S') {
                        cout << "Digite o novo valor: ";
                        cin >> novoValor;
                        lista->obterModificarValor(pos, valor, novoValor, true);
                        cout << "Valor modificado com sucesso." << endl;
                    }
                } else {
                    cout << "Posicao invalida!" << endl;
                }
                break;
            }
            case 5: {
                int pos, valor;
                cout << "Digite a posicao para inserir: ";
                cin >> pos;
                cout << "Digite o valor: ";
                cin >> valor;
                cout << (lista->inserir(pos, valor) ? "Elemento inserido." : "Posicao invalida!") << endl;
                break;
            }
            case 6: {
                int pos, valorRetirado;
                cout << "Digite a posicao para retirar: ";
                cin >> pos;
                if (lista->retirar(pos, valorRetirado)) {
                    cout << "Elemento retirado: " << valorRetirado << endl;
                } else {
                    cout << "Posicao invalida!" << endl;
                }
                break;
            }
            case 7:
                lista->imprimir();
                break;
            case 8:
                cout << "Encerrando o programa." << endl;
                break;
            default:
                cout << "Opcao invalida, tente novamente." << endl;
                break;
        }
    } while (opcao != 8);

    delete lista;
    return 0;
}
