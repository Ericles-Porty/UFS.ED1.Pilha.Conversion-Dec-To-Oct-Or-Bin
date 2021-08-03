#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

typedef struct no
{

    int conv;
    struct no *proxNo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

void inicializa(tipoLista *pilha)
{
    pilha->inicio = NULL;
    pilha->fim = NULL;
    pilha->quant = 0;
}

int convert(tipoLista *pilha, int valor, int base)
{
    int resto;
    do
    {
        if (pilha->quant == 0)
        {
            if (valor > 0)
            {
                resto = valor % base;
                tipoNo *novoNo;
                novoNo = (tipoNo *)malloc(sizeof(tipoNo));
                novoNo->proxNo = NULL;
                novoNo->conv = resto;
                pilha->inicio = novoNo;
                pilha->fim = novoNo;
                pilha->quant++;
                valor /= base;
            }
        }
        else
        {
            if (valor > 0)
            {
                resto = valor % base;
                tipoNo *novoNo;
                novoNo = (tipoNo *)malloc(sizeof(tipoNo));
                novoNo->proxNo = pilha->inicio;
                novoNo->conv = resto;
                pilha->inicio = novoNo;
                pilha->quant++;
                valor /= base;
            }
        }
    } while (valor > 0);
    return 1;
}

void exibePilha(tipoLista *pilha)
{
    tipoNo *atual;
    atual = pilha->inicio;
    if (atual == NULL)
    {
        cout << 0;
    }
    else
    {
        while (atual != NULL)
        {
            cout << atual->conv;
            atual = atual->proxNo;
        }
    }
}

void removeDaFrente(tipoLista *pilha)
{
    tipoNo *aux;
    aux = pilha->inicio;
    pilha->inicio = pilha->inicio->proxNo;
    if (pilha->quant == 1)
        pilha->fim = NULL;
    pilha->quant--;
    free(aux);
}

int estaVazia(tipoLista *pilha)
{
    if (pilha->inicio == NULL)
        return 1;
    else
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
            if (convert(&lista, aux, 8))
            {
                cout << "NUMBER INSERTION SUCCESSFULLY" << endl
                     << endl;
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
            if (convert(&lista, aux, 2))
            {
                cout << "NUMBER INSERTION SUCCESSFULLY" << endl
                     << endl;
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
            break;
        default:

            cout << "CHOOSE A VALID OPTION!";
        }
    } while (op != 0);
}