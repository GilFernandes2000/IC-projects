#include<iostream>
#include<fstream>
#include <assert.h>
using namespace std;

int main(int argc, char *argv[]){// dar como argumentos o ficheiro de entrada e o ficheiro para copia
    assert(argc == 3); 

    ifstream ifs(argv[1]);
    ofstream ofs(argv[2]);
    string line;
    char data[100];
    while(ifs.good()){
        ifs >> data;
        if(ifs.good()){
            ofs << data << endl;
        }
    }
    ifs.close();
    ofs.close();

    return 0;
}

// ainda nao faz a copia por espaços