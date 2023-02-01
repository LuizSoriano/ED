#include <iostream>
using namespace std;

class Noh{
    friend class ABB;
    private:
        int valor;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int dado);
        
};

Noh::Noh(int dado){
    valor = dado;
    esquerdo = NULL;
    direito = NULL; 
}
class ABB{
    private:
        int folha;
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, int valor);
        void PercorrePreOrdemAux(Noh* umNoh);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor);
        void DestruirRec(Noh* raiz);
        void PercorrePreOrdem();
        void Imprime();
};

ABB::ABB(){
    raiz = NULL;
    folha = 0;
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

void ABB::Imprime(){
    cout << folha << endl;
}

void ABB::InserirRecursiv(int valor){
    raiz = InserirRec(raiz,valor);
}

Noh* ABB::InserirRec(Noh* umNoh,int valor){
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
        if(umNoh->esquerdo == NULL and umNoh->direito == NULL)
            folha++;
    }
    if(umNoh != NULL){
        PercorrePreOrdemAux(umNoh->esquerdo);
        PercorrePreOrdemAux(umNoh->direito);
    }
}

int main(){
    ABB arvore;
    int qtd,n;
    cin >> qtd;
    for(int i=0;i<qtd;i++){
        cin >> n;
        arvore.InserirRecursiv(n);
    }
    arvore.PercorrePreOrdem();
    arvore.Imprime();
    return 0;
}

