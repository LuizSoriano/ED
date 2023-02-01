#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Noh{
    friend class ABB;
    private:
        string valor;
        string posicao;
        Noh* esquerdo;
        Noh* direito;
    public:
        Noh(string dado,int pos);
};

Noh::Noh(string dado,int pos){
    posicao = to_string(pos);
    valor = dado;
    esquerdo = NULL;
    direito = NULL; 
}
class ABB{
    private:
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, string valor,int pos);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(string valor,int pos);
        void DestruirRec(Noh* raiz);
        void Imprime(string palavra);
        Noh* BuscaAux(string valor);
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

void ABB::Imprime(string palavra){
    Noh* n = BuscaAux(palavra);
    if(n == NULL)
        cout << -1 << endl;
    else
        cout << n->posicao << endl;
}

void ABB::InserirRecursiv(string valor,int pos){
    string v = " ";
    Noh* aux = BuscaAux(valor);
    if(aux != NULL){
        aux->posicao += v;
        aux->posicao += to_string(pos);
    }
    else
        raiz = InserirRec(raiz,valor,pos);
}

Noh* ABB::InserirRec(Noh* umNoh,string valor,int pos){
    if(umNoh == NULL){
        Noh* novo = new Noh(valor,pos);
        return novo;
    }
    if(valor < umNoh->valor)
        umNoh->esquerdo = InserirRec(umNoh->esquerdo,valor,pos);
    else
        umNoh->direito = InserirRec(umNoh->direito,valor,pos);
    return umNoh;
}

Noh* ABB::BuscaAux(string valor){
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
    string palavra;
    int cont = 1;
    ifstream ler("entrada.txt");
    if(ler){
        while(ler >> palavra){
            arvore.InserirRecursiv(palavra,cont);
            cont++;
        }
    }
    cin >> palavra;
    arvore.Imprime(palavra);
    return 0;
}