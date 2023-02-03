#include <iostream>   

typedef unsigned TCodProcesso;

struct prioridade{
    TCodProcesso codigo;
    int prioridade;
};

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        bool Inserir(TCodProcesso codigo, int prioridade);
        // Retira e retorna a raiz
        bool Retirar(TCodProcesso* ptCodigo, int* ptPrioridade);
        // Verifica se a heap está vazia
        bool Vazia();
    private:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        int capacidade;
        int tamanho;
        TCodProcesso* heap;
};

using namespace std;

Heap::Heap(int cap) {
    capacidade = cap;
    heap = new TCodProcesso[cap];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] heap;

}

void Heap::ArrumarDescendo(int i) {
    int esq = Esquerdo(i);
    int dir = Direito(i);
    int maior = i;
    if((esq < tamanho) and (heap[esq] > heap[maior])){
        maior = esq;
    }
    if((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }

    if(maior!=i){
        swap(heap[i], heap[maior]);
        ArrumarSubindo(maior);
    }
}

void Heap::ArrumarSubindo(int i) {
    int p = Pai(i);
    if(heap[i] > heap[p]){
        swap(heap[i], heap[p]);
        ArrumarSubindo(p);
    }
}

int Heap::Pai(int i) {
    return (i-1)/2;
}

int Heap::Esquerdo(int i) {
    return 2*i+1;
}

int Heap::Direito(int i) {
    return 2*i+2;
}

bool Heap::Retirar(TCodProcesso* ptCodigo, int* ptPrioridade) {
    // Retira um codigo/prioridade, retornando os dois valores.
    // Retorna falso se o heap estiver vazio.
    if(tamanho == 0)
        return false;
    
}

bool Heap::Vazia() {
    if(tamanho == 0)
        return true;
    return false;
}

bool Heap::Inserir(TCodProcesso codigo, int prioridade) {
    if(tamanho == capacidade)
        return false;
    heap[tamanho] = codigo;
    ArrumarSubindo(tamanho);
    tamanho++;
    return true;
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Heap heap(capacidade);
    char comando;
    TCodProcesso codigo;
    int prioridade;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir um processo no heap
                cin >> codigo >> prioridade;
                heap.Inserir(codigo, prioridade);
                break;
            case 'o': // obter um processo do heap
                if (heap.Retirar(&codigo, &prioridade))
                    cout << codigo << ' ' << prioridade << endl;
                else
                    cout << "Nao encontrado" << endl;
                break;
            case 's': //sair
                break;
        }
    } while (comando != 's');
    return 0;
}
