#include <iostream>
#include <queue>

typedef int Dado;

enum Posicao {DIR, ESQ};

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
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, int valor);
        void SucessorAux(Noh* umNoh,int suc);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor);
        void DestruirRec(Noh* raiz);
        void Sucessor(int suc);
        void Imprime(int v);
        void EscreverNivelANivel(ostream& saida);
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

void ABB::Imprime(int v){
    cout << v << " ";
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

void ABB :: Sucessor(int suc){ 
    SucessorAux(raiz,suc);
}

void ABB ::SucessorAux(Noh* umNoh,int suc){
    if(umNoh != NULL){
        SucessorAux(umNoh->esquerdo,suc);
        if(suc < umNoh->valor){
            Imprime(umNoh->valor);
        }
        SucessorAux(umNoh->direito,suc);
    }
}

void ABB::EscreverNivelANivel(ostream& saida) {
    queue<Noh*> filhos;
    Noh noh = Dado();
    Noh* fimDeNivel = &noh; // noh especial para fim de nivel
    filhos.push(raiz);
    filhos.push(fimDeNivel);
    while (not filhos.empty()) {
        Noh* ptNoh = filhos.front();
        filhos.pop();
        if (ptNoh == fimDeNivel) {
            saida << "\n";
            if (not filhos.empty())
                filhos.push(fimDeNivel);
        }
        else {
            saida << '[';
            if (ptNoh != NULL) {
                saida << ptNoh->valor;
                filhos.push(ptNoh->esquerdo);
                filhos.push(ptNoh->direito);
            }
            saida << ']';
        }
    }
}

// === Programa ================================================================
int main() {
    ABB arvore;
    Dado chave;
    char operacao;
    do {
        cin >> operacao;
        switch (operacao) {
            case 'i': // Inserir
                cin >> chave;
                arvore.InserirRecursiv(chave);
                break;
            case 'e': // Escrever
                arvore.EscreverNivelANivel(cout);
                break;
            case 's': { // Sucessor
                cin >> chave;
                arvore.Sucessor(chave);
                cout << endl;
                break;
            }
        }
    } while (operacao != 'f');
    return 0;
}
