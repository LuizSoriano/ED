
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Torneio{
    private:
        int* mheap;
        int mcapacidade;
        int mtamanho;
    public:
        Torneio(int*vet, int tam);
        ~Torneio();
        void Arruma();
        void Copia_maior(int i);
        void Insere(int d);
        int Maior(int i);
        inline int esquerdo(int i){return 2*i+1;}
        inline int direito(int i){return 2*i+2;}
};

Torneio::Torneio(int *vet, int tam){
    int cont = 0;
    mcapacidade = 1;
    while(mcapacidade < tam){
        mcapacidade *= 2;
    }
    mcapacidade = mcapacidade + tam -1;
    mheap = new int [mcapacidade];
    mtamanho = tam;
    for (int i = mcapacidade - tam; i < mcapacidade; i++) {
        mheap[i] = vet[cont];
        cont++;
    }
    Arruma();
}

Torneio::~Torneio(){
    delete [] mheap;
}

void Torneio::Arruma(){
    for(int i = mcapacidade - mtamanho -1; i>=0; i--){
        Copia_maior(i);
    }
}

void Torneio::Copia_maior(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior = 0,menor = 0;
    if(esq < mcapacidade and mheap[esq] != -1){
        if(dir < mcapacidade and mheap[dir] > mheap[esq]){
            maior = mheap[dir];
            menor = mheap[esq];
        }else{
            maior = mheap[esq]; 
            if(dir < mcapacidade and mheap[dir] != -1)
                menor = mheap[dir];
        }
        mheap[i] = maior - menor;
    }else{
        mheap[i] = -1;
    }
}

int Torneio::Maior(int i){
    int m = i;
    while (esquerdo(m) < mcapacidade)
    {
        int esq = esquerdo(m);
        int dir = direito(m);
        if(esq < mcapacidade and (mheap[esq] > mheap[dir] or dir >= mcapacidade)){
            m = esq;
        }
        else if(dir < mcapacidade)
            m = dir;
    }
    return mheap[m];
}

int main(){
    int qtd;
    cin >> qtd;
    int *vetor = new int[qtd];
    for(int i=0;i<qtd;i++){
        cin >> vetor[i];
    }
    Torneio t(vetor,qtd);
    cout << t.Maior(0);
    return 0;
}