#include <iostream>
using namespace std;

class Noh {
    friend class pilha;
    private:
        char dado;
        Noh* pontprox;
    public:
        Noh(int n);
};

Noh::Noh(int n){
    dado = n;
    pontprox = NULL;
}

class pilha {
    private:
        Noh* PTopo;
        int tam;
        int tam1;
    public:
        pilha();
        ~pilha();
        int Desempilhar();
        void Empilhar(int n);
        int tamanho();
        int topo();
        void ordenar(pilha& p1);
};

pilha::pilha(){
    PTopo = NULL;
    tam = 0;
    tam1 = 0;
}

pilha::~pilha(){
    while(PTopo){
        Desempilhar();
    }
}

int pilha::topo(){
    return PTopo -> dado;
}

void pilha::Empilhar(int n){
    Noh* novo = new Noh(n);
    novo->pontprox = PTopo;
    PTopo = novo;
    tam++;
    tam1++;
}

int pilha::Desempilhar(){
    int num = PTopo->dado;
    Noh *temp = PTopo;
    PTopo = PTopo->pontprox;
    delete temp;
    tam--;
    tam1--;
    return num;
}

int pilha::tamanho(){
    return tam;
}

void pilha::ordenar(pilha& p1){
	int var1,var2,x;
	pilha aux;
	for(int i=0;i<tam;i++){
		x=0;
		while(p1.tamanho()>0){
			if(x==0){
				var1 = p1.Desempilhar();
				var2 = p1.Desempilhar();
			}
			x++;
			cout << var1 << " " << var2 << endl;
			if(var1 > var2){
				aux.Empilhar(var2);
				var2 = p1.Desempilhar();
			}
			else{
				aux.Empilhar(var1);
				var1 = p1.Desempilhar();
			}
		}
		if(var1 > var2)
			p1.Empilhar(var1);
		else
			p1.Empilhar(var2);
		for(int j=0;j<aux.tamanho();j++)
			p1.Empilhar(aux.Desempilhar());
	}
	
}

int main(){
    int qtd,n;
    pilha p1;
    cin >> qtd;
    for(int i=0;i<qtd;i++){
        cin >> n;
        p1.Empilhar(n);
    }
    p1.ordenar(p1);
    return 0;
}
