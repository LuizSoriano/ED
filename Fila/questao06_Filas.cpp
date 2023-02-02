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

int main(){
    Fila f,aux;
    int n,qtd,num,x,cont=0;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> num;
        f.enfileira(num);
    }
    cin >> qtd;
    while(f.tamanho() > 0){
        for(int i=0;i<qtd;i++){
            x = f.desenfileira();
            if(i == 0 and x < 0){
                cout << x << " ";
            }
            else if(x < 0 and cont != 0){
				aux.enfileira(x);
                cout << x <<  " ";
            }
            else{
                aux.enfileira(x);
                cont++;
            }
        }
        if(cont == qtd)
            cout << "inexistente";
    }
    return 0;
}
