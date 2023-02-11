#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Registro { // registro com os campos a serem lidos da base de dados
    char anzsic06 [5] = {char(0)};
    char Area [7] = {char(0)};
    char ano [7] = {char(0)};
    char geo_count [7] = {char(0)};
    char ec_count [7] = {char(0)};
    // os vetores de char sempre serão inicializados completos por caracteres nulos
};

void FazerVetor(Registro novoRegistro[]){
	string converter;
	ifstream ler ("CSV.bin"); // abre o arquivo binario para leitura
    ler.seekg (0, ler.end); // posiciona a cabeça de leitura no fim
    long long int tam_bytes = ler.tellg (); // recebe o número de bytes do arquivo
    long long int qntdCadastrados = (tam_bytes / sizeof (Registro)); 
    // divide o tamanho do arquivo pelo tamanho da estrutura Registro para saber o número de registros no arquivo
    ler.seekg (0, ler.beg); // retorna a cabeça de leitura para o início
    if (ler) {
        for (long long int j = 0; j < qntdCadastrados; j++) { // enquanto for possível ler, a variável "registro" recebe um registro lido do arquivo
            ler.read ((char*)(&novoRegistro), sizeof (Registro));
            ler >> converter;
            unsigned cont = 0;
			while (cont < 5 and cont < converter.size ()) {
				novoRegistro->anzsic06 [cont] = converter [cont];
				cont++;
			}
			cont = 0;
			while (cont < 7 and cont < converter.size ()) {
				novoRegistro->Area [cont] = converter [cont];
				cont++;
			}
			cont = 0;
			while (cont < 7 and cont < converter.size ()) {
				novoRegistro->ano [cont] = converter [cont];
				cont++;
			}
			cont = 0;
			while (cont < 7 and cont < converter.size ()) {
				novoRegistro->geo_count[cont] = converter [cont];
				cont++;
			}
			cont = 0;
			while (cont < 7 and cont < converter.size ()) {
				novoRegistro->ec_count [cont] = converter [cont];
				cont++;
			}
            cont++;
        }
    }
    else {
        ler.close (); // fechamento da função de leitura
    }
}

long long int contarTodosRegistros () {
    long long int cont = 0;
    ifstream ler ("CSV.bin"); // abre o arquivo binario para leitura
    ler.seekg (0, ler.end); // posiciona a cabeça de leitura no fim
    long long int tam_bytes = ler.tellg (); // recebe o número de bytes do arquivo
    long long int qntdCadastrados = (tam_bytes / sizeof (Registro)); 
    // divide o tamanho do arquivo pelo tamanho da estrutura Registro para saber o número de registros no arquivo
    ler.seekg (0, ler.beg); // retorna a cabeça de leitura para o início
    if (ler) {
        for (long long int j = 0; j < qntdCadastrados; j++) { // enquanto for possível ler, a variável "registro" recebe um registro lido do arquivo
            Registro registro;
            ler.read ((char*)(&registro), sizeof (Registro));
            cont++;
            
        }
    }
    else {
        ler.close (); // fechamento da função de leitura
    }
    return cont;
}

void intercala(Registro v[], long long int p,long long  int q, long long int r){
    long long int i = p, j = q;
    long long int tamanho = r - p + 1;
    Registro w[tamanho]; // vetor auxiliar
    long long int k = 0;
    while ((i < q) and (j <= r)) {                
       if (v[i].Area <= v[j].Area)  {
           w[k++] = v[i++]; /* w[k] = v[i]; k++; i++; */
		} else  {
			w[k++] = v[j++]; /* w[k] = v[j]; k++; j++; */
		}
	} 
    // terminou um dos vetores, agora copia o outro                           
    while (i < q) {
        w[k++] = v[i++];
    }      
    while (j <= r) {
       w[k++] = v[j++]; 
    }
    // agora copiamos do vetor auxiliar aux[] em v[p:r]
	for (long long int m = 0; m < tamanho; m++){ 
		v[p + m] = w[m];
    }
}

void mergesort(Registro a[], long long int inicio, long long int fim){
	long long int meio;
	if (inicio < fim) {
		meio = (inicio + fim)/2; 
		mergesort(a, inicio, meio);
		mergesort(a, meio+1, fim);
		intercala(a,inicio,meio,fim);
	}
}

int main(){
    long long int fim  = contarTodosRegistros();
    long long int inicio = 0;
    Registro* novoRegistro = new Registro[fim];
    FazerVetor(novoRegistro);
    mergesort(novoRegistro,inicio,fim);
    for(long long int i=0; i < fim; i++){
        cout << "Anzsic06: " << novoRegistro[i].anzsic06
             << "Area: " << novoRegistro[i].Area
             << "Ano: " << novoRegistro[i].ano
             << "Geo_count: " << novoRegistro[i].geo_count
             << "Ec_count: " << novoRegistro[i].ec_count
             << endl;
    }
    return 0;
}
