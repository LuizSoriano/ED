#include <iostream>
using namespace std;

class Torneio {
    private:
        int *arranjo;
        int capacidade;
        int tamanhoInicial;
    public:
        Torneio (int *vetor, int tam);
        ~Torneio ();
        //em todas as funções, o parâmetro i representa a posição de um elemento no arranjo
        int esquerdo (int i) {return 2 * i + 1; }
        int direito (int i) {return 2 * i + 2; }
        void copiaMaior (int i);
        void arruma ();
        int campeao (int i);
};

Torneio::Torneio (int *vetor, int tam) {
    int numPais = 1, cont = 0;
    while (numPais < tam)
        numPais *= 2;
    capacidade = numPais + tam - 1;
    arranjo = new int [capacidade];
    tamanhoInicial = tam;
    for (int i = capacidade - tam; i < capacidade; i++) {
        arranjo [i] = vetor [cont];
        cont++;
    }
}

Torneio::~Torneio () {
    delete [] arranjo;
}

void Torneio::arruma () {
    for (int i = capacidade - tamanhoInicial - 1; i >= 0; i--)
        copiaMaior (i);
}

void Torneio::copiaMaior (int i) {
    int filhoEsquerdo = esquerdo (i);
    int filhoDireito = direito (i);
    int maior = 0, menor = 0;
    if (filhoEsquerdo < capacidade and arranjo [filhoEsquerdo] != -1) {
        if (filhoDireito < capacidade and arranjo [filhoDireito] > arranjo [filhoEsquerdo]) {
            maior = arranjo [filhoDireito];
            menor = arranjo [filhoEsquerdo];
        }
        else {
            maior = arranjo [filhoEsquerdo];
            if (filhoDireito < capacidade and arranjo [filhoDireito] != -1)
                menor = arranjo [filhoDireito];
        }
        arranjo [i] = maior - menor;
    }
    else
        arranjo [i] = -1;
}

int Torneio::campeao (int i) {
    int maior = i;
    while (esquerdo (maior) < capacidade) {
        int filhoEsquerdo = esquerdo (maior);
        int filhoDireito = direito (maior);
        if (filhoEsquerdo < capacidade and (arranjo [filhoEsquerdo] > arranjo [filhoDireito] or filhoDireito >= capacidade)) 
            maior = filhoEsquerdo;
        else if (filhoDireito < capacidade) 
            maior = filhoDireito;
    }
    return arranjo [maior];
}

int main() {
    int qtdParticipantes;
    cin >> qtdParticipantes;
    int *vetor = new int [qtdParticipantes];
    for (int i = 0; i < qtdParticipantes; i++)
        cin >> vetor [i];
    Torneio torneio (vetor, qtdParticipantes);
    torneio.arruma ();
    cout << torneio.campeao (0);

    return 0;
}
