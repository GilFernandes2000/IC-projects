#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <assert.h>

using namespace std;

int main(int argc, char* argv[]){
    assert(argc == 3);
    ifstream ifs(argv[1]); // abrir ficheiro para leitura
    ofstream ofs(argv[2]); // criaçao de ficheiro para escrita

    map<char,int> hist; // criaçao do histograma
    char c;

    while(ifs.get(c)){ // vai buscar os caracteres um a um eliminando espaços
        map<char, int>::iterator it = hist.find(c); // iterador para encontrar o char c
        if(it != hist.end()){ // se nao encontra o fim quer dizer que o caracter foi encontrado no mapa
            it -> second++; // incrementa ao segundo fator do mapa
        }
        else{
            hist.insert(make_pair(c,1)); // se nao encontra cria um novo par e incrementa no mapa
        }
    }

    for(auto it = hist.cbegin(); it != hist.cend(); ++it){ // precorre o iterador do mapa
        ofs << it->first << " - " << it->second << endl; // imprime first - second
    }
    ofs.close();
    return 0;
}

