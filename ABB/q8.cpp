#include <iostream>
using namespace std;

class Noh{
    friend class ABB;
    private:
        int valor;
        string p;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(int dado,string palavra);
        
};

Noh::Noh(int dado, string palavra){
    p = palavra;
    valor = dado;
    esquerdo = NULL;
    direito = NULL; 
}
class ABB{
    private:
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, int valor,string p);
        Noh* BuscaAux(int valor);
        void PercorreEmOrdemAux(Noh* umNoh);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor,string p);
        void DestruirRec(Noh* raiz);
        int Minimo();
        int Maximo();
        void Busca(int valor);
        void PercorreEmOrdem();
        void RemoveRec(int valor);
        void Imprime(Noh* umNoh);
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

void ABB::Imprime(Noh* umNoh){
    cout << umNoh->valor << " ";
}

void ABB::InserirRecursiv(int valor,string p){
    raiz = InserirRec(raiz,valor,p);
}

Noh* ABB::InserirRec(Noh* umNoh,int valor,string p){
    if(umNoh == NULL){
        Noh* novo = new Noh(valor,p);
        return novo;
    }
    if(valor < umNoh->valor)
        umNoh->esquerdo = InserirRec(umNoh->esquerdo,valor,p);
    else
        umNoh->direito = InserirRec(umNoh->direito,valor,p);
    return umNoh;
}

void ABB::Busca(int valor){
    Noh* v = BuscaAux(valor);
    if(v == NULL)
        cout << "INEXISTENTE" << endl;
    else{
        cout <<  v->p << endl;
    }
}

Noh* ABB::BuscaAux(int valor){
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


void ABB :: PercorreEmOrdem(){
    PercorreEmOrdemAux(raiz);
}

void ABB :: PercorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        PercorreEmOrdemAux(umNoh->esquerdo);
        Imprime(umNoh);
        PercorreEmOrdemAux(umNoh->direito);
    }
}

int main(){
    ABB arvore;
    int valor;
    string palavra;
    char opcao;
    cin>>opcao;
    while(opcao!='f'){
        switch (opcao){
        case 'i':
            cin >> valor >> palavra;
            arvore.InserirRecursiv(valor,palavra);
            break;
        case 'b':
            cin>>valor;
            arvore.Busca(valor);
            break;
        case 'e':
            arvore.PercorreEmOrdem();
            cout << endl;
            break;
        default:
            break;
        }
        cin>>opcao;
    }
    return 0;
}