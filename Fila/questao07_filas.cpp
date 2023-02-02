#include <iostream>
using namespace std;

class Noh{
    friend class Fila;
    private:
        int valor;
        Noh* Prox;
    public:
        Noh(int dado);
};

Noh::Noh(int dado){
    valor = dado;
    Prox = NULL;
}

class Fila{
    private:
        Noh* Inicio;
        Noh* Fim;
        int Tamanho;
    public:
        Fila();
        ~Fila();
        void enfileira(int dado);
        int tamanho();
        int desenfileira();
        void debuga();
        bool vazia();
};

Fila::Fila(){
    Tamanho = 0;
    Inicio = NULL;
    Fim = NULL;
}

Fila::~Fila(){
    while(Tamanho > 0){
        desenfileira();
    }
}

int Fila::tamanho(){
    return Tamanho;
}

void Fila::enfileira(int dado){
    Noh *novo = new Noh(dado);
    if(Tamanho == 0)
        Inicio = novo;
    else
        Fim -> Prox = novo;
    Fim = novo;
    Tamanho++;
}

int Fila::desenfileira(){
    int valor = Inicio -> valor;
    Noh* temp = Inicio;
    Inicio = Inicio -> Prox;
    delete temp;
    Tamanho--;
    return valor;
}

bool Fila::vazia(){
    if(Tamanho == 0)
        return true;
    return false;
}

void Fila::debuga(){
    Noh *copia = Inicio;
    while(Inicio != NULL){
        int valor = Inicio -> valor;
        Inicio = Inicio -> Prox;
        cout << valor << " ";
    }
    Inicio = copia;
    cout << endl;
}

int main(){
    Fila f1,f2,aux,copia1,copia2;
    char opcao,fila;
    int v,cont=0,tamt,tf1,tf2;
    cin >> opcao;
    while(opcao != 't'){
        if(opcao == 'i'){
            cin >> fila;
            cin >> v;
            if(fila == 'a')
                f1.enfileira(v);
            else
                f2.enfileira(v);
            copia1 = f1;
            copia2 = f2;
        }
        else if(opcao == 'e'){
            cin >> fila;
            if(fila == 'a')
                copia1.debuga();
            else
                copia2.debuga();
        }
        else{
            while(f1.tamanho() > 0 and f2.tamanho() > 0){
                aux.enfileira(f1.desenfileira());
                aux.enfileira(f2.desenfileira());
                cont++;
            }
            if(f1.tamanho() > 0){
                tf1 = f1.tamanho();
                for(int i=0;i<tf1;i++)
                    aux.enfileira(f1.desenfileira());
            }
            else if(f2.tamanho() > 0){
                tf2 = f2.tamanho();
                for(int i = 0;i<tf2;i++)
                    aux.enfileira(f2.desenfileira());
            }
            tamt = copia1.tamanho() + copia2.tamanho();
            for(int i=0;i<tamt;i++){
                int aux1 = aux.desenfileira();
                cout << aux1 << " ";
                if(i%2 == 0 and tf1 != f1.tamanho())
                    f1.enfileira(aux1);
                else if (i%2 != 0 and tf2 != f1.tamanho())
                    f2.enfileira(aux1);
            }
            cout << endl;
        }
        cin >> opcao;
    }
    
    return 0;
}
