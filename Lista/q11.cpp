#include <iostream>
#include <cstdlib>
using namespace std;


class noh{
	friend class listadup;
	private:
		int dado;
		noh* proximo;
		noh* anterior;
	public:
		noh(int d);
};

noh::noh(int d){
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
		inline void insere(int dado);
		void insereNoFim(int dado);
		void imprime();
		inline bool vazia();
        void remover(listadup& l2,int tam1);
		void removerValor(int valor);
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

void listadup::insere(int dado){
	insereNoFim(dado);
}


void listadup::insereNoFim(int dado){
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
	while(aux!=NULL){
		cout<<aux->dado<<" ";
		aux = aux->proximo;
	}
	cout<<endl << endl;
	aux = ultimo;
	while(aux!=NULL){
		cout<<aux->dado<<" ";
		aux = aux->anterior;
	}
}

void listadup::removerValor(int valor){
	noh* aux = primeiro;
	while((aux!=NULL) and (aux->dado != valor)){
		aux = aux->proximo;
	}
	if(aux != NULL){
		noh* anterior = aux->anterior;
		noh* proximo = aux->proximo;
		if(anterior != NULL)
			anterior->proximo = proximo;
		else
			primeiro = aux->proximo;
		if(proximo != NULL)
			proximo->anterior = anterior;
		else
			ultimo = aux->anterior;
		delete aux;
	}
	tamanho--;
	if(vazia()){
		primeiro = NULL;
		ultimo = NULL;
	}
}

inline bool listadup::vazia(){
	return (tamanho == 0);
}

void listadup::remover(listadup& l2,int tam1){
    noh* aux;
    noh* aux1 = l2.primeiro;
    int cont,v,cont1=0,cont2=0;
    while(aux1 != NULL){
        aux = primeiro;
        v = aux1 -> dado;
        cont = 0;
        cont2++;
        while(aux != NULL){
            if(v == aux->dado)
                cont++;
            aux = aux -> proximo;
        }
        if(cont > 0){
			cont1++;
			cont2--;
            while(cont > 0){
                removerValor(v);
                cont--;
            }
        }
        aux1 = aux1 -> proximo;
    }
    cout << cont1 << endl << cont;
    if(cont1 == tam1 and tam1 != 1 and tam1 != 0)
		cout << -1 << endl;
	else if(cont2 == tam1 and tam1 != 1 and tam1 != 0)
		cout << -1 << endl;
	else 
		imprime();
}

int main(){
    listadup l1,l2;
    int qtd,qtd1,n;
    cin >> qtd;
    for(int i=0;i<qtd;i++){
        cin >> n;
        l1.insere(n);
    }
    cin >> qtd1;
    for(int i=0;i<qtd1;i++){
        cin >> n;
        l2.insere(n);
    }
    l1.remover(l2,qtd1);
    return 0;
}
