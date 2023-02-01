#include <iostream>
#include <cstring>
using namespace std;

class Noh{
    friend class ABB;
    private:
        char valor;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(char dado);
        
};

Noh::Noh(char dado){
    valor = dado;
    esquerdo = NULL;
    direito = NULL; 
}
class ABB{
    private:
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, char valor);
        void PercorrePreOrdemAux(Noh* umNoh);
        Noh* BuscaAux(char v);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor);
        void DestruirRec(Noh* raiz);
        void PercorrePreOrdem();
        void Operacao(Noh* umNoh);
};

ABB::ABB(){
    raiz = NULL;
}

ABB::~ABB(){
    DestruirRec(raiz);
}

void ABB::DestruirRec(Noh* umNoh){
    if(umNoh != NULL){
        DestruirRec(umNoh->esquerdo);
        DestruirRec(umNoh->direito);
        delete umNoh;
    }
}

void ABB::Operacao(Noh* umNoh){
}

void ABB::InserirRecursiv(int valor){
    raiz = InserirRec(raiz,valor);
}

Noh* ABB::InserirRec(Noh* umNoh,char valor){
    if(umNoh == NULL){
        Noh* novo = new Noh(valor);
        return novo;
    }
    if(valor < umNoh->valor)
        umNoh->esquerdo = InserirRec(umNoh->esquerdo,valor);
    else
        umNoh->direito = InserirRec(umNoh->direito,valor);
    return umNoh;
}

void ABB :: PercorrePreOrdem(){
    PercorrePreOrdemAux(raiz);
}

void ABB ::PercorrePreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        Operacao(umNoh);
        PercorrePreOrdemAux(umNoh->esquerdo);
        PercorrePreOrdemAux(umNoh->direito);
    }
}

Noh* ABB::BuscaAux(char valor){
    Noh* atual = raiz;
    while(atual != NULL){
        if(atual->valor == valor)
            return atual;
        else if(atual->valor > valor)
            atual = atual->esquerdo;
        else
            atual = atual->direito;
    } 
    return atual;
}

int main(){
    ABB arvore;
    char valor;
    cin >> valor;
    while(valor != '\n'){
        arvore.InserirRecursiv(valor);
    }
    arvore.PercorrePreOrdem();
    return 0;
}
