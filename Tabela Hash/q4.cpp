#include <iostream>
using namespace std;

int funcaoHash(int c, int n) {
    return c % n;
}

class Noh{
    friend class Lista;
    friend class TabelaHash;
    private:
        int chave;
        string valor;
        Noh* proximo;
    public:
        Noh(int c,string v);
};

Noh::Noh(int c,string v){
    chave = c;
    valor = v;
    proximo = NULL;
}

class Lista{
    friend class TabelaHash;
    private:
        Noh *primeiro;
        Noh *ultimo;
        int tamanho;
        void removerTudo();
    public:
        Lista();
        ~Lista();
        void inserirFim(int c,string v);
        void removerInicio();
        void removerFim();
        void removerValor(int c);
        void procurar(int cha);
        inline bool vazia();
};

Lista::Lista(){
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
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
    primeiro = NULL;
    ultimo = NULL;
}

void Lista::procurar(int cha){
    Noh* aux = primeiro;
    bool achou = true;
    while(aux != NULL and achou){
        if(aux->chave == cha){
            cout<<aux->valor<<endl;
            achou = false;
        }
        aux = aux->proximo;
    }
}

void Lista::inserirFim(int c,string v){
    Noh* novo = new Noh(c,v);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

inline bool Lista::vazia(){
    return (primeiro == NULL);
}

void Lista::removerFim(){
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
    Noh* removido = primeiro;
    primeiro = primeiro->proximo;
    delete removido;
    tamanho--;
    if(vazia()) ultimo = NULL;
}

void Lista::removerValor(int c){
    Noh* aux;
    Noh* anterior;
    bool removeu = false;
    if(not vazia()){
        aux = primeiro;
        while((aux != NULL) and (aux->chave != c)){
            anterior  = aux;
            aux = aux->proximo;
        }
        if(aux != NULL){
            removeu = true;
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
    if(!removeu)
        cout<<"ERRO"<<endl;
}

class TabelaHash{
    private:
        int capacidade;
        Lista* hash;
        int* vetorP;
    public:
        TabelaHash(int cap);
        ~TabelaHash();
        void inserir(int c,string v);
        void buscar(int c);
        void remover(int c);
        void imprimir();
        void redimensionar();
        void destruir();
};

TabelaHash::TabelaHash(int cap){
    hash = new Lista[cap];
    capacidade = cap;
}

TabelaHash::~TabelaHash(){
    destruir();
}

void TabelaHash::destruir(){
    for(int i=0;i<capacidade;i++){
        hash[i].removerTudo();
    }
    delete[] hash;
}


void TabelaHash::inserir(int chave, string valor){
    int pos = funcaoHash(chave,capacidade);
    hash[pos].inserirFim(chave, valor);
    float cont = 0;
    for(int i=0;i<capacidade;i++){
        if(hash[i].primeiro != NULL)
            cont++;
    }
    if(float(0.7*capacidade)<=cont)
        redimensionar();
}

void TabelaHash::remover(int c){
    int pos = funcaoHash(c,capacidade);
    hash[pos].removerValor(c);
}

void TabelaHash::buscar(int c){
    int pos = funcaoHash(c,capacidade);
    hash[pos].procurar(c);
}

void TabelaHash::imprimir(){
    Noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << "Posicao " << i << ": ";
        atual = hash[i].primeiro;
        if(atual != NULL){
            cout<<atual->chave<<" "<<atual->valor<<endl;
        }
        if(atual == NULL)
            cout<<endl;
        else if(atual->proximo != NULL){
            cout<<"Lista de colisao: ";
            atual = atual->proximo;
            while(atual!=NULL){
                cout<<atual->chave<<" "<<atual->valor;
                atual = atual->proximo;
                if(atual!=NULL)
                    cout<<", ";
            }
            cout<<endl;
        }
    }
    cout << "-----------------------" << endl;
}

void TabelaHash::redimensionar(){
    TabelaHash tAux(capacidade*2);
    Noh* aux;
    for (int i = 0; i < capacidade; i++) {
        aux = hash[i].primeiro;
        while (aux != NULL) {
            tAux.inserir(aux->chave,aux->valor);
            aux = aux->proximo;
        }
    }
    capacidade *= 2;
    delete[] hash;
    hash = new Lista[capacidade];
    imprimir();
    for (int i = 0; i < capacidade; i++) {
        aux = tAux.hash[i].primeiro;
        while (aux != NULL) {
            inserir(aux->chave,aux->valor);
            aux = aux->proximo;
        }
    }
    delete[] aux;
}

int main(){
    int tam,chave;
    cin>>tam;
    TabelaHash t(tam);
    char op;
    string valor;
    cin>>op;
    while(op!='S'){
        switch(op){
        case 'I':
            cin>>chave>>valor;
            t.inserir(chave,valor);
            break;
        case 'R':
            cin>>chave;
            t.remover(chave);
            break;
        case 'B':
            cin>>chave;
            t.buscar(chave);
            break;
        case 'P':
            t.imprimir();
            break;
        }
        cin>>op;
    }
    return 0;
}
