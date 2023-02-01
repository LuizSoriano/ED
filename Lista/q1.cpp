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
        void somaListas(Lista& l1,Lista& l2,Lista& l3);
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

Lista& Lista::operator=(const Lista& umaLista){
    removerTudo();
    Noh* aux = umaLista.primeiro;
    while(aux != NULL){
        inserirFim(aux->dado);
        aux = aux->proximo;
    }
    return *this;
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

void Lista::somaListas(Lista& l1,Lista& l2,Lista& l3){
    int t,t1,t2,v1=0,v2=0,sobra=0,soma;
    t1 = l1.tamanho;
    t2 = l2.tamanho;
    if(t1 > t2)
        t = t1;
    else
        t = t2;
    for(int i=0;i<t;i++){
        if(not l1.vaziar()){
            v1 = l1.primeiro->dado;
            l1.removerInicio();
        }
        else
            v1 = 0;
        if(not l2.vaziar()){
            v2 = l2.primeiro->dado;
            l2.removerInicio();
        }
        else
            v2 = 0;
        if(i != t-1){
			soma = v1+v2+sobra;
            if(soma >= 10){
                l3.inserir(soma%10);
                sobra = (soma) / 10;
            }
            else{
				sobra = 0;
                l3.inserir(v1+v2+sobra);
			}
        }
        else
            l3.inserir(v1+v2+sobra);
    }
    l3.imprimir();
}

int main(){
    Lista l1,l2,l3;
    int n,n1;
    cin >> n;
    while(n != -1){
        l1.inserir(n);
        cin >> n;
    }
    cin >> n1;
    while(n1 != -1){
        l2.inserir(n1);
        cin >> n1;
    }
    l3.somaListas(l1,l2,l3);
    return 0;
}
