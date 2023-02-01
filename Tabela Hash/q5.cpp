#include <iostream>
using namespace std;

class Noh {
    friend class lista;
    friend class Hash;
    private:
        int dia,mes,ano;
        Noh* Prox;
    public:
        Noh (int d, int m, int a);
};

Noh::Noh (int d, int m, int a) {
    dia = d;
    mes = m;
    ano = a;
    Prox = NULL;
}

class lista {
    friend class Hash;
    private:
        int contador = 0;
        Noh* Inicio;
        Noh* Fim;
        int Tamanho;
    public:
        lista ();
        ~lista ();
        void inserir(int dia,int mes, int ano);
        bool Vazia () {return Tamanho == 0; }
        int tamanho () {return Tamanho; }
        void removerTudo ();
        void buscar (int dia, int mes);
        int tam(){return contador;}
};

lista::lista () {
    Inicio = NULL;
    Fim = NULL;
    Tamanho = 0;
}

lista::~lista () {
    while (not Vazia ())
        removerTudo ();
}

void lista::inserir(int dia, int mes, int ano) {
    if (Vazia ()){
        Noh* aux = new Noh(dia,mes,ano);
        Inicio = aux;
        Fim = aux;
        Tamanho++;
        contador++;
    }
    else {
        Noh* novo = new Noh (dia,mes,ano);
        Fim->Prox = novo;
        Fim = novo;
        Tamanho++;
    }
}

void lista::removerTudo(){
    Noh* aux = Inicio;
    Noh* temp;
    while(aux != NULL){
        temp = aux;
        aux = aux->Prox;
        delete temp;
    }
    Tamanho = 0;
    Inicio = NULL;
    Fim = NULL;
}


void lista::buscar (int dia, int mes) {
    int cont = 0;
    Noh* aux = Inicio;
    while(aux != NULL){
        if(aux->dia == dia and aux->mes == mes)
            cont++;
        aux = aux->Prox;
        }
    cout << cont << " ";
}

class Hash {
    friend class lista;
    private:
        int capacidade;
        lista* l1;
    public:
        Hash (int cap);
        ~Hash ();
        void inserir (int dia, int mes, int ano);
        void Buscar (int dia, int mes);
        void porcentagem();
};

Hash::Hash (int cap) {
    capacidade = cap;
    l1 = new lista[cap];
}

Hash::~Hash () {
    delete[] l1;
}

void Hash::porcentagem(){
    float aux=0;
    for(int i=0;i<capacidade;i++){
        if(l1[i].Inicio != NULL)
            aux++;
    }
    cout << aux/float(capacidade) << endl;
}

void Hash::inserir (int dia, int mes, int ano) {
    int hash = ((dia * mes) - 1) % capacidade;
    l1[hash].inserir (dia,mes,ano);
}

void Hash::Buscar (int dia, int mes) {
    int hash = ((dia * mes) - 1) % capacidade;
    l1[hash].buscar (dia , mes);
}

int main () {
    int cap, qtd, dia, mes,ano;
    cin >> cap >> qtd;
    string nome;
    Hash Tabela (cap);
    for (int i = 0; i < qtd; i++) {
        cin >> nome >> dia >> mes >> ano;
        Tabela.inserir (dia,mes,ano);
    }
    cin >> dia >> mes;
    Tabela.Buscar (dia, mes);
    Tabela.porcentagem();
    return 0;
}