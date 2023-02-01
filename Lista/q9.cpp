#include <iostream>
using namespace std;

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
    public:
        Lista();
        Lista(const Lista& umaLista);
        ~Lista();
        inline void inserir(int dado);
        void inserirFim(int dado);
        void imprimir();
        void removerFim();
        void removerInicio();
        void removerValor(int valor);
        void concatena(Lista& l1,Lista& l2);
        inline bool vazia();
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
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
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

inline bool Lista::vazia(){
    return (primeiro == NULL);
}

void Lista::removerFim(){
    if(not vazia()){
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
}


void Lista::removerInicio(){
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vazia()) ultimo = NULL;
}
    
void Lista::removerValor(int valor){
    Noh* aux;
    Noh* anterior;
    if(not vazia()){
        aux = primeiro;
        while((aux != NULL) and (aux->dado != valor)){
            anterior  = aux;
            aux = aux->proximo;
        }
        if(aux != NULL){
            if(aux == primeiro)
                removerInicio();
            else if(aux == ultimo)
                removerFim();
            else{
                anterior->proximo = aux->proximo;
                tamanho--;
                delete aux;
            }
        }
    }  
}

void Lista::concatena(Lista& l1,Lista& l2){
    Noh* aux = l1.primeiro;
    for(int i=0;i<5;i++){
        inserir(aux->dado);
        aux = aux -> proximo;
    }
    aux = l2.primeiro;
    for(int i=0;i<5;i++){
        inserir(aux->dado);
        aux = aux -> proximo;
    }
    imprimir();
}

int main(){
    Lista l1,l2,l3;
    int v;
    for(int i=0;i<5;i++){
        cin >> v;
        l1.inserir(v);
    }
    for(int i=0;i<5;i++){
        cin >> v;
        l2.inserir(v);
    }
    l3.concatena(l1,l2);
    l1.imprimir();
    l2.imprimir();
    for(int i=0;i<3;i++){
        cin >> v;
        l3.removerValor(v);
    }
    l3.imprimir();

    return 0;
}
