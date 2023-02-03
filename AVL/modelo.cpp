#include <iostream>
#include <cmath>

using namespace std;

class Noh{
    friend class AVL;
    private:
        int valor;
        Noh* esquerdo;
        Noh* direito;
        int altura;
    public:
        Noh(int dado);
        int FatorBalanceamento(Noh* umNoh);
        int InformaAltura(Noh* umNoh);
        int AtualizaAltura(Noh* umNoh);
        
};

Noh::Noh(int dado){
    valor = dado;
    esquerdo = NULL;
    direito = NULL; 
    altura = 1;
}

int Noh::InformaAltura(Noh* umNoh){
    if(umNoh == NULL)
        return 0;
    else
        return umNoh->altura;
}

int Noh::AtualizaAltura(Noh* umNoh){
    int altArvEsq = InformaAltura(umNoh->esquerdo);
    int altArvDir = InformaAltura(umNoh->direito);
    umNoh->altura = 1 + fmax(altArvEsq, altArvDir);
}

int Noh::FatorBalanceamento(Noh* umNoh){
    int altArvEsq = InformaAltura(umNoh->esquerdo);
    int altArvDir = InformaAltura(umNoh->direito);
    int fatorbal = altArvEsq - altArvDir;
    return fatorbal;
}



class AVL{
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
        Noh* ArrumaBalanceamento(Noh* umNoh);
        Noh* RotacaoEsq(Noh* umNoh);
        Noh* RotacaoDir(Noh* umNoh);
        Noh* RotacaoEsqDir(Noh* umNoh);
        Noh* RotacaoDirEsq(Noh* umNoh);
    public:
        AVL();
        ~AVL();
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

AVL::AVL(){
    raiz = NULL;
}

AVL::~AVL(){
    DestruirRec(raiz);
}

void AVL::DestruirRec(Noh* umNoh){
    if(umNoh != NULL){
        DestruirRec(umNoh->esquerdo);
        DestruirRec(umNoh->direito);
        delete umNoh;
    }
}

void AVL::Imprime(Noh* umNoh){
    cout << umNoh->valor << " ";
}

void AVL::InserirRecursiv(int valor){
    raiz = InserirRec(raiz,valor);
}

Noh* AVL::InserirRec(Noh* umNoh,int valor){
    if(umNoh == NULL){
        Noh* novo = new Noh(valor);
        return novo;
    }
    if(valor < umNoh->valor)
        umNoh->esquerdo = InserirRec(umNoh->esquerdo,valor);
    else
        umNoh->direito = InserirRec(umNoh->direito,valor);
    return ArrumaBalanceamento(umNoh);
}

Noh* AVL::RotacaoEsq(Noh* umNoh){
    if(umNoh != NULL){ 
        Noh* aux = umNoh->direito;
        umNoh->direito = aux->esquerdo;
        aux->esquerdo = umNoh;
        umNoh->AtualizaAltura(umNoh);
        umNoh->AtualizaAltura(aux);
        return aux;
    }
    else
        return umNoh;
}

Noh* AVL::RotacaoDir(Noh* umNoh) {
    if(umNoh != NULL){
        Noh* aux = umNoh->esquerdo;
        umNoh->esquerdo = aux->direito;
        aux->direito = umNoh;
        umNoh->AtualizaAltura(umNoh);
        umNoh->AtualizaAltura(aux);

        return aux;
    }else
        return umNoh;
}

Noh* AVL::RotacaoEsqDir(Noh* umNoh){
    umNoh->esquerdo = RotacaoEsq(umNoh->esquerdo);
    return RotacaoDir(umNoh);
}

Noh* AVL::RotacaoDirEsq(Noh* umNoh){
    umNoh->direito = RotacaoDir(umNoh->direito);
    return RotacaoEsq(umNoh);

}

Noh* AVL::ArrumaBalanceamento(Noh* umNoh){
    if(umNoh == NULL)
        return umNoh;
    umNoh->AtualizaAltura(umNoh);
    int fatorBal = umNoh->FatorBalanceamento(umNoh);
    if(((fatorBal >= -1) and (fatorBal <= 1)))
        return umNoh;
    if(fatorBal > 1 and (umNoh->FatorBalanceamento(umNoh->esquerdo) >= 0))
        return RotacaoDir(umNoh);
    else if(fatorBal > 1 and (umNoh->FatorBalanceamento(umNoh->esquerdo) < 0)){
        umNoh->esquerdo = RotacaoEsq(umNoh->esquerdo);
        return RotacaoDir(umNoh);
    }
    else if(fatorBal < -1 and (umNoh->FatorBalanceamento(umNoh->direito) <= 0))
        return RotacaoEsq(umNoh);
    else if(fatorBal < -1 and (umNoh->FatorBalanceamento(umNoh->direito) > 0)){
        umNoh->direito = RotacaoDir(umNoh->direito);
        return RotacaoEsq(umNoh);
    }
    return umNoh;
    
}

int AVL::Minimo(){
    if(raiz == NULL){
        cerr << "Arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        Noh* minimo = MinimoAux(raiz);
        return minimo->valor;
    }
}

Noh* AVL::MinimoAux(Noh* raizSubArvore){
    while(raizSubArvore->esquerdo != NULL){
        raizSubArvore = raizSubArvore->esquerdo;
    }
    return raizSubArvore;
}

int AVL::Maximo(){
    if(raiz == NULL){
        cerr << "Arvore vazia" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        Noh* maximo = MaximoAux(raiz);
        return maximo->valor;
    }
}

Noh* AVL::MaximoAux(Noh* raizSubArvore){
    while(raizSubArvore->direito != NULL){
        raizSubArvore = raizSubArvore->direito;
    }
    return raizSubArvore;
}

void AVL::Busca(int valor){
    Noh* v = BuscaAux(valor);
    if(v == NULL)
        cout << "Nao encontrado" << endl;
    else{
        cout <<  valor << endl;
    }
}

Noh* AVL::BuscaAux(int valor){
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

void AVL :: PercorrePosOrdem(){
    PercorrePosOrdemAux(raiz);
}

void AVL :: PercorrePosOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        PercorrePosOrdemAux(umNoh->esquerdo);
        PercorrePosOrdemAux(umNoh->direito);
        Imprime(umNoh);
    }
}

void AVL :: PercorreEmOrdem(){
    PercorreEmOrdemAux(raiz);
}

void AVL :: PercorreEmOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        PercorreEmOrdemAux(umNoh->esquerdo);
        Imprime(umNoh);
        PercorreEmOrdemAux(umNoh->direito);
    }
}

void AVL :: PercorrePreOrdem(){
    PercorrePreOrdemAux(raiz);
}

void AVL ::PercorrePreOrdemAux(Noh* umNoh){
    if(umNoh != NULL){
        Imprime(umNoh);
        PercorrePreOrdemAux(umNoh->esquerdo);
        PercorrePreOrdemAux(umNoh->direito);
    }
}


Noh* AVL :: RemoveMenor(Noh* raizSub){
    if(raizSub->esquerdo == NULL)
        return raizSub->direito;
    else
        raizSub->esquerdo = RemoveMenor(raizSub->esquerdo);
    return raizSub;
}

void AVL :: RemoveRec(int valor){
    raiz  = RemoveRecAux(raiz,valor);
} 

Noh* AVL :: RemoveRecAux(Noh* umNoh, int valor){
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
    return ArrumaBalanceamento(raizSubArvore);
}

int main(){
    AVL arvore;
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