#include <iostream>
#include <fstream>
using namespace std;

struct Registro { // criação do registro compatível aos dados que serão lidos do arquivo csv
    char anzsic06 [5] = {char(0)};
    char Area [7] = {char(0)};
    char ano [7] = {char(0)};
    char geo_count [7] = {char(0)};
    char ec_count [7] = {char(0)};
    // os vetores de char sempre serão inicializados completos por caracteres vazios
};

void tratar (string dados, Registro &registro) { // função para converter a linha retirada do arquivo no int main para um registro
    int contVirgulas = 0, pos = 0;
    int tam = dados.size ();
    for (int i = 0; i < tam; i++) { // o laço de repetição vai rodar uma vez para cada caractere contido na linha lida do arquivo csv
        if (dados [i] != ',') {
            if (contVirgulas == 0) { // antes de ser encontrada a primeira vírgula todos os caracteres serão agrupados no vetor de caractere do anzsic06
                registro.anzsic06 [pos] = dados [i];
                pos++;
            }
            else if (contVirgulas == 1) { // depois da primeira vírgula vem a area
                registro.Area [pos] = dados [i];
                pos++;
            }
            else if (contVirgulas == 2) { // depois da segunda vírgula vem o ano
                registro.ano [pos] = dados [i]; 
                pos++;
            }
            else if (contVirgulas == 3) { // após a terceira vígula é convertido o geo_count
                registro.geo_count [pos] = dados [i];
                pos++;
            }
            else if (contVirgulas == 4) { // após a quarta vígula é convertido o ec_count
                registro.ec_count [pos] = dados [i];
                pos++;
            }
        }
        else {
        // se o caractere da posição i na linha lida for uma vírgula, então 
        // o contVírgulas será acrescido e a variável "pos" voltará a ser 0
            pos = 0;
            contVirgulas++;
        }
    }
}

void converterParaBinario (Registro registro) { // função de conversão que será chamada a cada linha lida
    ofstream gravar ("CSV.bin", ios::app); // abertura do arquivo para gravação em binário no final
    gravar.write ((const char*)(&registro), sizeof (Registro)); // gravação em binário
    gravar.close (); // fechamento da escrita no arquivo
}

int main () {
    ifstream ler ("Data7602DescendingYearOrder.csv"); // abertura do arquivo csv para leitura
    string linha;
    if (ler) {
        getline (ler, linha); // leitura do cabeçalho, que não é gravado em binário 
        while (not ler.eof ()) {
            Registro campos;
            getline (ler, linha); // cada linha lida
            tratar (linha, campos); // é usada para criar um registro
            converterParaBinario (campos); // e o registro é gravado no arquivo binário
        }
    }
    else {
        ler.close (); // encerramento da função de leitura quando não é possível ler mais
    }
}
