#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

const int OCTAL = 8;
const int BINARIO = 2;

typedef struct no
{
    int valor;
    struct no *proximo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quantidade;
} tipoLista;

void inicializa(tipoLista *pilha)
{
    pilha->inicio = NULL;
    pilha->fim = NULL;
    pilha->quantidade = 0;
}

/*
    Função que converte um número decimal para uma base qualquer
    @param pilha: ponteiro para a pilha
    @param valor: valor a ser convertido
    @param base: base para a conversão
    @return 1 se a conversão foi bem sucedida, 0 caso contrário
*/
int converter(tipoLista *pilha, int valor, int base)
{
    int resto;
    do
    {
        // Verifica se a pilha está vazia
        if (pilha->quantidade == 0 && valor > 0)
        {
            tipoNo *novoNo;
            novoNo = (tipoNo *)malloc(sizeof(tipoNo));

            if (novoNo == NULL)
                return 0;

            resto = valor % base;

            novoNo->proximo = NULL;
            novoNo->valor = resto;

            pilha->inicio = novoNo;
            pilha->fim = novoNo;
            pilha->quantidade++;

            valor /= base;
        }

        if (valor > 0)
        {
            tipoNo *novoNo;
            novoNo = (tipoNo *)malloc(sizeof(tipoNo));

            if (novoNo == NULL)
                return 0;

            resto = valor % base;

            novoNo->proximo = pilha->inicio;
            novoNo->valor = resto;

            pilha->inicio = novoNo;
            pilha->quantidade++;

            valor /= base;
        }

    } while (valor > 0);
    return 1;
}

void exibePilha(tipoLista *pilha)
{
    if (pilha->inicio == NULL)
    {
        cout << "EMPTY STACK" << endl;
        return;
    }

    tipoNo *atual;
    atual = pilha->inicio;

    cout << "< ";
    while (atual != NULL)
    {
        cout << atual->valor << " ";
        atual = atual->proximo;
    }
    cout << ">" << endl;
}

void removeDaFrente(tipoLista *pilha)
{
    tipoNo *aux;
    aux = pilha->inicio;
    pilha->inicio = pilha->inicio->proximo;

    if (pilha->quantidade == 1)
        pilha->fim = NULL;

    pilha->quantidade--;

    free(aux);
}

int estaVazia(tipoLista *pilha)
{
    if (pilha->inicio == NULL)
        return 1;

    return 0;
}

void destruirPilha(tipoLista *pilha)
{
    while (!estaVazia(pilha))
        removeDaFrente(pilha);
}

int main()
{

    tipoLista lista;
    int aux, aux2, op;
    inicializa(&lista);
    system("cls");
    do
    {

        cout << endl
             << endl
             << "MENU" << endl;
        cout << "1 - DEC TO OCT" << endl;
        cout << "2 - DEC TO BIN" << endl;
        cout << "0 - EXIT" << endl;
        cout << "CHOOSE A OPTION:" << endl;
        cin >> op;
        system("cls");
        switch (op)
        {
        case 1:
            system("cls");

            cout << "TYPE A NUMBER: ";
            cin >> aux;

            if (converter(&lista, aux, OCTAL))
            {
                system("cls");

                cout << "DECIMAL INSERTION TO OCTAL BATTERY: ";

                exibePilha(&lista);
                destruirPilha(&lista);
            }
            else
                cout << "INSERTION PROBLEM" << endl
                     << endl;

            break;
        case 2:
            system("cls");
            cout << "TYPE A NUMBER: ";
            cin >> aux;
            if (converter(&lista, aux, BINARIO))
            {
                system("cls");

                cout << "DECIMAL INSERTION TO BINARY BATTERY: ";

                exibePilha(&lista);
                destruirPilha(&lista);
            }
            else
                cout << "INSERTION PROBLEM" << endl
                     << endl;

            break;
        case 0:
            system("cls");

            cout << "CLOSING THE SYSTEM" << endl;

            destruirPilha(&lista);

            return 0;
        default:
            cout << "CHOOSE A VALID OPTION!";
        }
    } while (op != 0);
}