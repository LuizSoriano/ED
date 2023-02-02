#include <iostream>
using namespace std;

class filaCircular{
    private:
        int mInicio;
        int mFim;
        int* dados;
        int mCapacidade;
        int mTamanho;
    public:
        filaCircular(int capacidade);
        ~filaCircular();
        void enfileira(int valor);
        int desenfileira();
        void informacoes();
        int mTam();
};

filaCircular::filaCircular(int capacidade){
    mInicio = 0;
    mFim = 0;
    mCapacidade = capacidade;
    dados = new int[capacidade];
    mTamanho = 0;
}

filaCircular::~filaCircular(){
    delete[] dados;
}

void filaCircular::informacoes(){
    cout<<"tamanho="<<mTamanho<<" "<<"capacidade="<<mCapacidade<<" "<<"inicio="<<mInicio<<" "<<"fim="<<mFim<<endl;
    int inicio = mInicio; 
    for(int i=0; i<mTamanho; i++){
        if(inicio == mCapacidade){
            inicio = 0;
        }
        cout << dados[inicio] << " ";
        inicio++;
    }
    cout<<endl;
}

void filaCircular::enfileira(int valor){
    if(mTamanho == 0){
        mFim = 0;
        dados[mFim] = valor;
        mTamanho++;
    }
    else{
        mFim++;
        if(mFim == mCapacidade)
            mFim = 0;
        dados[mFim] = valor;
        mTamanho++;
    }

}

int filaCircular::desenfileira(){
    int aux = mInicio;
    mInicio++;
    if (mInicio == mCapacidade)
        mInicio = 0;
    mTamanho--;
    return dados[aux];
}

int filaCircular::mTam(){
    return mTamanho;
}

int main(){
    char opcao;
    int cap,num;
    cin >> cap;
    filaCircular fc(cap);
    cin >> opcao;
    while(opcao != 't'){
        if(opcao == 'e'){
            cin >> num;        
            fc.enfileira(num);
        }
        else if(opcao == 'd'){
            if(fc.mTam() > 0)
                cout << fc.desenfileira() << endl;
        }
        else
            fc.informacoes();
        cin >> opcao;
    }
    return 0;
}
