#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ifstream ifs("nums.txt");
    ofstream ofs("../out.txt");

    char data[100];
    while(ifs.good()){
        ifs >> data;
        if(ifs.good()){
            ofs << data << endl;
        }
    }
    ofs.close();
    return 0;
}

// ainda nao faz a copia por espaços