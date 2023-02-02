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
        void iguais();
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

void Fila::iguais(){
    Fila aux;
    int var1,var2=0,T=Tamanho;
    for(int i=0;i<T;i++){
		var1 = desenfileira();
        if(var2 != var1 and i > 0){
            aux.enfileira(var2);
            aux.enfileira(var1);
        }
        var2 = var1;
    }
    int T1 = aux.tamanho();
    for(int i=0;i<T1;i++){
        enfileira(aux.desenfileira());
    }
}

int main(){
    Fila f1,f2,f3;
    bool teste = true;
    int qtd1,qtd2,v1,v2,cont=1,Taux;
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
    f1.iguais();
    f2.iguais();
    int Tf1 = f1.tamanho();
    int Tf2 = f2.tamanho();
    for(int i=0;i<Tf1;i++)
		cout << f1.desenfileira() << " ";
	cout << endl;
	for(int i=0;i<Tf2;i++)
		cout << f2.desenfileira() << " ";
	cout << endl;
	 
    while(teste){
        int menorv;
        if(cont % 2 != 0){
            int var1 = f1.desenfileira();
            for(int j=0;j<Tf2;j++){
                int var2 = f2.desenfileira();
                if(var1 > var2){
                    f2.enfileira(var1);
                    menorv = var2;
                }    
                else{
                    aux.enfileira(var2);
                    menorv = var1;
                }
            }
            resultante.enfileira(menorv);
        }
        Taux = aux.tamanho();
        for(int j=0;j<Taux;j++){
            f2.enfileira(aux.desenfileira());
        }
        if(cont % 2 == 0){
			int var2 = f2.desenfileira();
			int menorv;
            for(int j=0;j<Tf1;j++){
                int var1 = f1.desenfileira();
                if(var1 > var2){
                    aux.enfileira(var1);
                    menorv = var2;
                }    
                else{
                    aux.enfileira(var2);
                    menorv = var1;
                }
            }
            resultante.enfileira(menorv);
        }
        Taux = aux.tamanho();
        for(int j=0;j<Taux;j++){
            f1.enfileira(aux.desenfileira());
        }
        if(cont == Tf1 + Tf2)
            teste = false;
        cont++;
        cout << resultante.desenfileira() << " ";
    }
    /*int Tresult = resultante.tamanho();
    for(int i=0;i<Tresult;i++)
        cout << resultante.desenfileira() << " ";*/
    return 0;
}
/*
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

void Fila::debuga(){
    while(Inicio != NULL){
        int valor = Inicio -> valor;
        Inicio = Inicio -> Prox;
        cout << valor << " ";
    }
    cout << endl;
}

int main(){
    Fila f1,f2,aux,copia1,copia2;
    char opcao,fila;
    int v,cont=0;
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
			if(f1.tamanho() == f2.tamanho()){
				while(f1.tamanho() > 0 and f2.tamanho() > 0){
					aux.enfileira(f1.desenfileira());
					aux.enfileira(f2.desenfileira());
					cont+=2;
				}
			}
			else{
				if(f1.tamanho() > f2.tamanho()){
					while(f1.tamanho() > 0){
						aux.enfileira(f1.desenfileira());
						if(f2.tamanho() > 0){
							aux.enfileira(f2.desenfileira());
							cont++;
						}
						cont++;
					}
				}
				else{
					while(f2.tamanho() > 0){
						aux.enfileira(f2.desenfileira());
						if(f1.tamanho() > 0){
							aux.enfileira(f1.desenfileira());
							cont++;
						}
						cont++;
					}
				}
			}	
            for(int i=0;i<cont;i++)
                cout << aux.desenfileira() << " ";
            cout << endl;
        }
        cin >> opcao;
    }
    return 0;
}*/
