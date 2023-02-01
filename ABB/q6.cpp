#include <iostream>

using namespace std;

class Noh{
    friend class ABB;
    private:
        int altura;
        int cont;
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
    altura = 0;
    cont = 0;
}

class ABB{
    private:
        int aux;
        Noh* raiz;
        Noh* InserirRec(Noh* umNoh, int valor);
        Noh* MinimoAux(Noh* raizSubArvore);
        Noh* BuscaAux(int valor);
        void PercorreEmOrdemAux(Noh* umNoh);
        Noh* RemoveMenor(Noh* raizSub);
        Noh* RemoveRecAux(Noh* umNoh, int valor);
    public:
        ABB();
        ~ABB();
        void InserirRecursiv(int valor);
        void DestruirRec(Noh* raiz);
        int Minimo();
        void PercorreEmOrdem();
        void RemoveRec(int valor);
        void Depura(Noh * umNoh);
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

void ABB::Depura(Noh* umNoh){
    Noh* novo = BuscaAux(umNoh->valor);
    cout << novo->valor << "(" << novo->cont << ")/" << novo->altura << " ";
}

void ABB::InserirRecursiv(int valor){
    aux++;
    Noh* ver = BuscaAux(valor);
    if(ver == NULL)
        raiz = InserirRec(raiz,valor);
    else
        ver->cont++;
}

Noh* ABB::InserirRec(Noh* umNoh,int valor){
    if(umNoh == NULL){
        Noh* novo = new Noh(valor);
        novo->cont++;
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

Noh* ABB::BuscaAux(int valor){
    aux=0;
    Noh* atual = raiz;
    while(atual != NULL){
        if(atual->valor == valor){
            atual->altura = aux;
            return atual;
        }
        else if(atual->valor > valor){
            atual = atual->esquerdo;
            aux++;
        }
        else {
            atual = atual->direito;
            aux++;
        }
    }
    return atual;
}

void ABB :: PercorreEmOrdem(){
    PercorreEmOrdemAux(raiz);
}

void ABB :: PercorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        PercorreEmOrdemAux(umNoh->esquerdo);
        Depura(umNoh);
        PercorreEmOrdemAux(umNoh->direito);
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
    Noh* aux = BuscaAux(valor);
    if(aux != NULL){
        if(aux->cont == 1)    
            raiz  = RemoveRecAux(raiz,valor);
        else
            aux->cont--;
    }
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
    int v;
    for(int i=0;i<10;i++){
        cin >> v;
        arvore.InserirRecursiv(v);
    }
    arvore.PercorreEmOrdem();
    cout << endl;
    for(int i=0;i<5;i++){
        cin >> v;
        arvore.RemoveRec(v);
    }
    arvore.PercorreEmOrdem();
    cout << endl;
     for(int i=0;i<10;i++){
        cin >> v;
        arvore.InserirRecursiv(v);
    }
    arvore.PercorreEmOrdem();
    cout << endl;
    for(int i=0;i<5;i++){
        cin >> v;
        arvore.RemoveRec(v);
    }
    arvore.PercorreEmOrdem();
    cout << endl;
    return 0;
}
