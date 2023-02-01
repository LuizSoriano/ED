#include <iostream>
#include <cstdlib>
using namespace std;

struct Dado{
    int matricula,periodo;
    string nome;
};

class noh{
	friend class listadup;
	private:
		Dado dado;
		noh* proximo;
		noh* anterior;
	public:
		noh(Dado d);
};

noh::noh(Dado d){
	dado = d;
	proximo = NULL;
	anterior = NULL;
};

class listadup{
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos();
	public:
		listadup();
		listadup(const listadup& umaLista);
		~listadup();
		listadup& operator=(const listadup& umaLista);
		inline void insere(Dado dado);
		void insereNoFim(Dado dado);
		void imprime();
		inline bool vazia();
};

listadup::listadup(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

listadup::listadup(const listadup& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
	noh* aux = umaLista.primeiro;
	while(aux!=NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
}

listadup::~listadup(){
	removeTodos();
}

void listadup::removeTodos(){
	noh* aux = primeiro;
	noh* temp;
	while(aux!=NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

void listadup::insere(Dado dado){
	insereNoFim(dado);
}


void listadup::insereNoFim(Dado dado){
	noh* novo = new noh(dado);
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}
	else{
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}


void listadup::imprime(){
	noh* aux = primeiro;
    cout << "[";
	while(aux!=NULL){
		cout << aux->dado.matricula << " - " << aux->dado.nome;
		aux = aux->proximo;
        if(aux != NULL)
            cout << ", ";
	}
    cout << "]" << endl;
	aux = ultimo;
    cout << "[";
	while(aux!=NULL){
		cout << aux->dado.matricula << " - " << aux->dado.nome;
        if(aux->anterior != NULL)
            cout << ", ";
		aux = aux->anterior;
	}
    cout << "]" << endl;
}


inline bool listadup::vazia(){
	return (tamanho == 0);
}

int main(){
    listadup L;
    Dado D;
    int qtd;
    cin >> qtd;
    for(int i=0;i<qtd;i++){
        cin >> D.matricula >> D.nome >> D.periodo;
        L.insere(D);
    }
    L.imprime();
    return 0;
}
