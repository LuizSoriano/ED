#include <iostream>
#include <string>

using namespace std;

class elemento{
    friend class lista;
    private:
        int chave;
        elemento *proximo;
        elemento *anterior;
    public:
        elemento (int c){
            chave = c;
            proximo = NULL;
            anterior = NULL;
        }
};

class lista{
    private:
        elemento *inicio;
        elemento *fim;
    public:
        lista();
        ~lista();        
        void insereInicio(int c);
        void insereFim (int c);
        int removeRepetidos();//retorna a quantidade de elementos restantes na lista
        bool vazia();
        void imprimeLista();
};
    
lista::lista(){
    inicio = NULL;
    fim = NULL;
}
        
lista::~lista(){
    elemento* aux = inicio;
	elemento* temp;
	while(aux!=NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	inicio = NULL;
	fim = NULL;
}  

void lista::insereInicio (int c){
    elemento* novo = new elemento(c);
	if(vazia()){
		inicio = novo;
		fim = novo;
	}
	else{
		novo->proximo = inicio;
		inicio->anterior = novo;
		inicio = novo;
	}
}
        
void lista::insereFim (int c){
    elemento* novo = new elemento(c);
	if(vazia()){
		inicio = novo;
		fim = novo;
	}
	else{
		fim->proximo = novo;
		novo->anterior = fim;
		fim = novo;
	}
}
        
int lista::removeRepetidos(){
    int n,n1,cont,r=0;
    elemento* aux = inicio;
    elemento* aux1;
    while(aux != NULL){
		aux1 = aux;
		cont = 0;
        n = aux -> chave;
        while(aux1 != NULL){
            n1 = aux1->chave;
            if(n == n1)
                cont++;
            aux1 = aux1 -> proximo;
        }
        if(cont > 1){
			while(cont > 1){
				aux1 = fim;
				while((aux1!=NULL) and (aux1->chave != n)){
					aux1 = aux1->anterior;
				}
				if(aux1 != NULL){
					elemento* anterior = aux1->anterior;
					elemento* proximo = aux1->proximo;
					if(anterior != NULL)
						anterior->proximo = proximo;
					else
						inicio = aux1->proximo;
					if(proximo != NULL)
						proximo->anterior = anterior;
					else
						fim = aux1->anterior;
					delete aux1;
				}
				if(not vazia()){
					inicio = NULL;
					fim = NULL;
				}
				cont--;
			}
		}
        aux = aux -> proximo;
    }
    elemento *percorre = inicio;
    while(percorre != NULL){
		r++;
		percorre = percorre -> proximo;
	}
    return r;
}
        
void lista::imprimeLista(){
    if (inicio != NULL){
        elemento *auxiliar = inicio;
        while (auxiliar->proximo != NULL){
            cout<<"("<<auxiliar->chave<<") ";
            auxiliar =  auxiliar->proximo;
        }
        cout<<"("<<auxiliar->chave<<")"<<endl;
    } else {
            cout<<"VAZIA";
    }
}

bool lista::vazia(){
    if(inicio == NULL)
        return true;
    return false;
}
    
int main(){
    
    lista listaD;
    
    int chave;
    string dado;
    
    cin>>chave;
    
    while (chave != -1){
        listaD.insereFim(chave);        
        cin>>chave;  
    }
    cout<<listaD.removeRepetidos()<<endl;
    listaD.imprimeLista();
    
    
    return 0;
}
