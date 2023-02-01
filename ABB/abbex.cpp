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
        Noh* MinimoAux(Noh* raizSubArvore);
        Noh* MaximoAux(Noh* raizSubArvore);
        Noh* BuscaAux(int valor);
        void PercorrePosOrdemAux(Noh* umNoh);
        void PercorreEmOrdemAux(Noh* umNoh);
        void PercorrePreOrdemAux(Noh* umNoh);
        Noh* RemoveMenor(Noh* raizSub);
        Noh* RemoveRecAux(Noh* umNoh, int valor);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor);
        void DestruirRec(Noh* raiz);
        int Minimo();
        int Maximo();
        void Busca(int valor);
        void PercorrePosOrdem();
        void PercorreEmOrdem();
        void PercorrePreOrdem();
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

int ABB::Minimo(){
    if(raiz == NULL){
        cerr << "Arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        Noh* minimo = MinimoAux(raiz);
        return minimo->valor;
    }
}

Noh* ABB::MinimoAux(Noh* raizSubArvore){
    while(raizSubArvore->esquerdo != NULL){
        raizSubArvore = raizSubArvore->esquerdo;
    }
    return raizSubArvore;
}

int ABB::Maximo(){
    if(raiz == NULL){
        cerr << "Arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        Noh* maximo = MaximoAux(raiz);
        return maximo->valor;
    }
}

Noh* ABB::MaximoAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void ABB::Busca(int valor){
    Noh* v = BuscaAux(valor);
    if(v == NULL)
        cout << "Nao encontrado" << endl;
    else{
        cout <<  valor << endl;
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

void ABB :: PercorrePosOrdem(){
    PercorrePosOrdemAux(raiz);
}

void ABB :: PercorrePosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        PercorrePosOrdemAux(umNoh->esquerdo);
        PercorrePosOrdemAux(umNoh->direito);
        Imprime(umNoh);
    }
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

void ABB :: PercorrePreOrdem(){
    PercorrePreOrdemAux(raiz);
}

void ABB ::PercorrePreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        Imprime(umNoh);
        PercorrePreOrdemAux(umNoh->esquerdo);
        PercorrePreOrdemAux(umNoh->direito);
    }
}


Noh* ABB :: RemoveMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL)
        return raizSub->direito;
    else
        raizSub->esquerdo = RemoveMenor(raizSub->esquerdo);
    return raizSub;
}

void ABB :: RemoveRec(int valor){
    raiz  = RemoveRecAux(raiz,valor);
} 

Noh* ABB :: RemoveRecAux(Noh* umNoh, int valor){
    if(umNoh == NULL){
        cerr << "No nao encontrado";
        exit(EXIT_FAILURE);
    }
    Noh* raizSubArvore = umNoh;
    if(valor < umNoh->valor)
        umNoh->esquerdo = RemoveRecAux(umNoh->esquerdo, valor); //valor menor que o no atual vai pra subarvore esquerda
    else if(valor > umNoh->valor)
        umNoh->direito = RemoveRecAux(umNoh->direito,valor); //valor maior que o no atual vai pra sub direita
    else{
        if(umNoh->esquerdo == NULL)
            raizSubArvore = umNoh->direito;
        else if(umNoh->direito == NULL)
            raizSubArvore = umNoh->esquerdo;
        else{
            raizSubArvore = MinimoAux(umNoh->direito);
            raizSubArvore->direito = RemoveMenor(umNoh->direito);
            raizSubArvore->esquerdo = umNoh->esquerdo;
        }
        delete umNoh;
    }
    return raizSubArvore;
}

int main(){
    ABB arvore;
    int valor;
    char opcao;
    cin>>opcao;
    while(opcao!='s'){
        switch (opcao){
        case 'i':
            cin>>valor;
            arvore.InserirRecursiv(valor);
            break;
        case 'r':
            cin>>valor;
            arvore.RemoveRec(valor);
            break;
        case 'b':
            cin>>valor;
            arvore.Busca(valor);
            cout<<endl;
            break;
        case 'M':
            cout<<arvore.Maximo()<<endl;
            break;
        case 'm':
            cout<<arvore.Minimo()<<endl;
            break;
        case 'p':
            arvore.PercorrePreOrdem();
            cout<<endl;
            arvore.PercorreEmOrdem();
            cout<<endl;
            arvore.PercorrePosOrdem();
            cout<<endl;
            break;
        default:
            break;
        }
        cin>>opcao;
    }
    return 0;
}
