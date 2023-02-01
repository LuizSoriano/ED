#include <iostream>
using namespace std;

struct equipe{
    
};

class Noh{
    friend class Lista;
    private:
        int dado;
        Noh* proximo;
    public:
        Noh(int dado);
};

Noh::Noh(int d){
    dado = d;
    proximo = NULL;
}

class Lista{
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
        void imprimirReversoAux(Noh* umNoh);
    public:
        Lista();
        Lista(const Lista& umaLista);
        ~Lista();
        Lista& operator=(const Lista& umaLista);
        inline void inserir(int dado);
        void inserirFim(int dado);
        void inserirInicio(int dado);
        void removerInicio();
        void removerFim();
        void imprimir();
        inline bool vaziar();
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

Lista::Lista(const Lista& umaLista){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    Noh* aux = umaLista.primeiro;
    while(aux != NULL){
        inserirFim(aux->dado);
        aux = aux->proximo;
    }
}

Lista::~Lista(){
    removerTudo();
}

void Lista::removerTudo(){
    Noh* aux = primeiro;
    Noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void Lista::inserir(int dado){
    inserirFim(dado);
}

void Lista::inserirFim(int dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void Lista::inserirInicio(int dado){
    Noh* novo = new Noh(dado);
    if(vaziar()){
        primeiro = novo;
        ultimo = novo;
    }else{
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}


void Lista::imprimir(){
    Noh* aux = primeiro;
    while(aux != NULL){
        cout << aux->dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

inline bool Lista::vaziar(){
    return (primeiro == NULL);
}

void Lista::removerFim(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* aux = primeiro;
    Noh* anterior;
    while(aux->proximo != NULL){
        anterior = aux;
        aux = aux->proximo;
    }
    delete ultimo;
    anterior->proximo = NULL;
    ultimo = anterior;
    tamanho--;
    if(tamanho == 0) primeiro = NULL;
    
}

void Lista::removerInicio(){
    if(vaziar()){
        cerr << "Remoção em lista vazia!" << endl;
        exit(EXIT_FAILURE);
    }
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vaziar()) ultimo = NULL;
}

int main(){
    
}