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

void adicionarElemento () {
    fstream gravarNovoDado, reposicionarResto;
    string converter;
    // criação das funções de manipulação do arquivo binário
    gravarNovoDado.open ("CSV.bin", ios::in | ios::out | ios::ate);
    reposicionarResto.open ("CSV.bin", ios::in | ios::out | ios::ate);
    Registro novoRegistro, registro, gravar;
    int numLinha;
    cout << "Informe a posicao de insercao do registro: ";
    cin >> numLinha;
    // entrada de novos dados do registro que será inserido
    cout << "anzsic06: ";
    cin >> converter;
    unsigned cont = 0;
    while (cont < 5 and cont < converter.size ()) {
        novoRegistro.anzsic06 [cont] = converter [cont];
        cont++;
    }
    cout << "Area: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        novoRegistro.Area [cont] = converter [cont];
        cont++;
    }
    cout << "ano: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        novoRegistro.ano [cont] = converter [cont];
        cont++;
    }
    cout << "geo_count: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        novoRegistro.geo_count[cont] = converter [cont];
        cont++;
    }
    cout << "ec_count: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        novoRegistro.ec_count [cont] = converter [cont];
        cont++;
    }
    // posicionamento da cabeça de leitura na posição em que será inserido o novo registro
    reposicionarResto.seekg (numLinha * sizeof (Registro));
    // leitura do registro que ocupa a posição que será ocupada pelo novo
    reposicionarResto.read ((char*)(&registro), sizeof (Registro));
    // posicionamento da cabeça de escrita na posição em que deve ser inserido o novo registro
    gravarNovoDado.seekp (numLinha * sizeof (Registro));
    // inserção do novo registro
    gravarNovoDado.write ((const char*)(&novoRegistro), sizeof (Registro));
    while (not reposicionarResto.eof ()) {
        // "gravar" é usado para armazenar o registro que teve sua posição ocupada pelo registro que teve sua posição substituída para que ele ocupe a posição do seu sucessor
        gravar = registro;
        // antes de gravar o registro que foi "empurrado", é preciso ler seu sucessor também, que
        // será igualado a "gravar" no próximo looping para que o processo se repita e nenhum
        // registro seja perdido
        reposicionarResto.read ((char*)(&registro), sizeof (Registro));
        // gravação do registro substituído na posição de seu sucessor, que já foi lido para não ser
        // perdido também, fazendo necessária a repetição desse looping por toda a extensão do arquivo
        gravarNovoDado.write ((const char*)(&gravar), sizeof (Registro));
    }
    cout << endl << "Novo registro inserido!" << endl;
    // encerramento das funções
    gravarNovoDado.close ();
    reposicionarResto.close ();
}

void lerIntervalo () {
    Registro registro;
    ifstream leitura ("CSV.bin"); // criação da função de leitura do arquivo binário
    int linhaInicio, linhaFim;
    // entrada do intervalo de linhas que serão depuradas
    cout << "Digite a posicao da linha de inicio da leitura: ";
    cin >> linhaInicio;
    cout << "Digite a posicao da linha de termino da leitura: ";
    cin >> linhaFim;
    cout << endl;
    // posicionamento da cabeça de leitura na posição inicial
    leitura.seekg ((linhaInicio) * sizeof (Registro));
    for (int j = linhaInicio; j <= linhaFim; j++) {
        // a cada repetição é lido e depurado um registro
        leitura.read ((char*)(&registro), sizeof (Registro));
        for (int i = 0; i < 5; i++)
            cout <<  registro.anzsic06 [i];
        cout << ",";
        for (int i = 0; i < 7; i++)
            cout << registro.Area [i];
        cout << ",";
        for (int i = 0; i < 7; i++)
            cout << registro.ano [i];
        cout << ",";
        for (int i = 0; i < 7; i++)
            cout << registro.geo_count [i];
        cout << ",";
        for (int i = 0; i < 7; i++)
            cout << registro.ec_count [i];
        cout << endl;
    }
    leitura.close (); // fechamento da função
}

void editarRegistro () {
    Registro registro;
    string converter;
    int numLinha;
    fstream gravarNovoDado;
    // criação da função para manipular o registro a ser editado no arquivo binário
    gravarNovoDado.open ("CSV.bin", ios::in | ios::out | ios::ate);
    cout << "Informe a posicao do registro: ";
    cin >> numLinha;
    // entrada de novos dados do registro
    cout << "anzsic06: ";
    cin >> converter;
    unsigned cont = 0;
    while (cont < 5 and cont < converter.size ()) {
        registro.anzsic06 [cont] = converter [cont];
        cont++;
    }
    cout << "Area: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        registro.Area [cont] = converter [cont];
        cont++;
    }
    cout << "ano: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        registro.ano [cont] = converter [cont];
        cont++;
    }
    cout << "geo_count: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        registro.geo_count[cont] = converter [cont];
        cont++;
    }
    cout << "ec_count: ";
    cin >> converter;
    cont = 0;
    while (cont < 7 and cont < converter.size ()) {
        registro.ec_count [cont] = converter [cont];
        cont++;
    }
    // posicionamento da cabeça de escrita na posição desejada pelo usuário
    gravarNovoDado.seekp (numLinha * sizeof (Registro));
    // gravação do registro com novos valores na posição solicitada
    gravarNovoDado.write ((const char*)(&registro), sizeof (Registro));
    gravarNovoDado.close (); // encerramento da função
    cout << endl << "Registro editado!" << endl;
}

void inverterPosicoes () {
    Registro registro1, registro2;
    fstream receber1, receber2;
    receber1.open ("CSV.bin", ios::in | ios::out | ios::ate); // declaração das funções de manipulação do arquivo binário
    receber2.open ("CSV.bin", ios::in | ios::out | ios::ate);
    int pos1, pos2;
    cout << "Posicao de um registro: ";
    cin >> pos1;
    cout << "Posicao de outro registro: ";
    cin >> pos2;
    // posicionamento das cabeças de leitura nas posições desejadas
    receber1.seekg (pos1 * sizeof (Registro));
    receber2.seekg (pos2 * sizeof (Registro));
    // leitura dos registros nas posições solicitadas
    receber1.read ((char*)(&registro1), sizeof (Registro));
    receber2.read ((char*)(&registro2), sizeof (Registro));
    // posicionamento das cabeças de escrita invertendo as posições
    receber1.seekp (pos2 * sizeof (Registro));
    receber2.seekp (pos1 * sizeof (Registro));
    // gravação dos registros com as posições trocadas
    receber1.write ((const char*)(&registro1), sizeof (Registro));
    receber2.write ((const char*)(&registro2), sizeof (Registro));
    cout << endl << "Troca realizada!" << endl;
    // encerramento das funções
    receber1.close ();
    receber2.close ();
}

void depurarTodosRegistros () {
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
            // a cada registro lido são depurados seus atributos
            for (int i = 0; i < 5; i++)
                cout << registro.anzsic06 [i];
            cout << ",";
            for (int i = 0; i < 7; i++)
                cout << registro.Area [i];
            cout << ",";
            for (int i = 0; i < 7; i++)
                cout << registro.ano [i];
            cout << ",";
            for (int i = 0; i < 7; i++)
                cout << registro.geo_count [i];
            cout << ",";
            for (int i = 0; i < 7; i++)
                cout << registro.ec_count [i];
            cout << endl;
        }
    }
    else {
        ler.close (); // fechamento da função de leitura
    }
}

void ordena(){
    
}


int main () {
    int comando = 0;
    while (comando != 6) { // impressão do menu de comandos
        cout << "Selecione uma opcao" << endl
             << "[ 1 ] = adicionar elemento" << endl
             << "[ 2 ] = ler posicoes espicificas" << endl
             << "[ 3 ] = editar um registro" << endl
             << "[ 4 ] = trocar registros de posicao" << endl
             << "[ 5 ] = depurar arquivo binario completo" << endl
             << "[ 6 ] = ordenar arquivo" << endl
             << "[ 7 ] = sair" << endl
             << "Sua escolha: ";
        cin >> comando;
        cout << endl;
        if (comando == 1)
            adicionarElemento ();
        else if (comando == 2)
            lerIntervalo ();
        else if (comando == 3)
            editarRegistro ();
        else if (comando == 4)
            inverterPosicoes ();
        else if (comando == 5)
            depurarTodosRegistros ();
        else if(comando == 6)
            ordena();
        else if (comando == 7)
            cout << "Encerrando sistema...";
        else
            cout << "ERRO! Comando invalido" << endl;
        cout << endl;
    }

    return 0;
}