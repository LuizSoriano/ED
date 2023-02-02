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
	while(Tamanho >0){
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
    Fila f1,f2,aux;
    int qtd1,qtd2,v1,v2,y,x,aux1;
    cin >> qtd1;
    for(int i=0;i<qtd1;i++){
        cin >> v1;
        f1.enfileira(v1);
    }
    cin >> qtd2;
    for(int i=0;i<qtd2;i++){
        cin >> v2;
        f2.enfileira(v2);
    }
    for(int i=0;i<qtd2;i++){
        x = f2.desenfileira();
        aux1=0;
        for(int j=0;j<qtd1;j++){
            y = f1.desenfileira();
            if(x != y){
                aux.enfileira(y);
            }
            else
				aux1++;
        }
        qtd1 -= aux1;
        for(int i=0;i<qtd1;i++){
			f1.enfileira(aux.desenfileira());
		}
    }
    for(int i=0;i<qtd1;i++)
		cout << f1.desenfileira() << " ";
    return 0;
}
