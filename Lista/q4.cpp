#include <iostream>
using namespace std;

struct Compras{
    string produto;
    int qtd;
};

class Noh{
    friend class Lista;
    private:
        Compras dado;
        Noh* proximo;
    public:
        Noh(Compras dado);
};

Noh::Noh(Compras d){
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
        inline void inserir(Compras dado);
        void inserirFim(Compras dado);
        void imprimir();
        bool repetido(Compras C);
        void removerValor(string valor);
        Compras procurar(string valor);
        inline bool vazia();
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

void Lista::inserir(Compras dado){
    inserirFim(dado);
}

void Lista::inserirFim(Compras dado){
    Noh* novo = new Noh(dado);
    if(vazia()){
        primeiro = novo;
        ultimo = novo;
    }else{
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}


void Lista::imprimir(){
    Noh* aux = primeiro;
    while(aux != NULL){
        cout << aux->dado.produto << " " << aux->dado.qtd << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

inline bool Lista::vazia(){
    return (primeiro == NULL);
}


bool Lista::repetido(Compras C){
    Noh* ver = primeiro;
    while(ver != NULL){
        if(C.produto == ver->dado.produto)
            return true;
        ver = ver -> proximo;
    }
    return false;
}
void Lista::removerValor(string valor){
	Noh* aux = primeiro;
	while((aux!=NULL) and (aux->dado.produto != valor)){
		aux = aux->proximo;
	}
	if(aux != NULL){
		Noh* frente = aux->proximo;
		aux -> proximo = frente->proximo;
		delete frente;
	}
	tamanho--;
	if(vazia()){
		primeiro = NULL;
		ultimo = NULL;
	}
}
Compras Lista::procurar(string valor){
    Noh* aux = primeiro;
    Compras achado;
    while((aux != NULL) and (aux->dado.produto != valor)){
        achado.produto = aux->dado.produto;
        achado.qtd = aux->dado.qtd;
        aux = aux->proximo;
    }
    return achado;
}


int main(){
    char opcao;
    Lista L;
    Compras C,Comp;
    string procura;
    cin >> opcao;
    while(opcao != 'q'){
        if(opcao == 'i'){
            cin >> C.produto >> C.qtd;
            if(not L.repetido(C))
                L.inserir(C);
        }
        else if(opcao == 'r'){
			cin >> procura;
            if(L.vazia())
                cout << "item nao existente" << endl;
            else
                L.removerValor(procura);
        }
        else if(opcao == 'c'){
            cin >> procura;
            Comp = L.procurar(procura);
            if(Comp.produto == procura)
                cout << Comp.produto << " " << Comp.qtd << endl;
            else
                cout << "item nao existente" << endl;
        }
        else{
            if(L.vazia())
                cout << "[]" << endl;
            else
                L.imprimir();
        }
        cin >> opcao;
    }
    if(L.vazia())
        cout << "[]" << endl;
    else
        L.imprimir();
    return 0;
}
