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
        int esq = 0,dir = 0;
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, int valor);
    public:
        ABB();
        ~ABB();
        void DestruirRec(Noh* raiz);
        void InserirRecursiv(int valor);
        void Imprime(int qtd);
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

void ABB::InserirRecursiv(int valor){
    if(raiz != NULL){
        if(valor > raiz->valor)
            dir++;
        else
            esq++;
    }
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

void ABB :: Imprime(int qtd){
    cout << qtd << " " << esq-dir << endl;
}

int main(){
    ABB arvore;
    int n,cont = 0;
    cin >> n;
    while(n != -1){
        arvore.InserirRecursiv(n);
        cin >> n;
        cont++;
    }
    arvore.Imprime(cont);
    return 0;
}
