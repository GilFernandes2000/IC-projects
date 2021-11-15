#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv) {

    cout << "input: " << argv[1] << endl;
    cout << "output: " << argv[2] << endl;

    ifstream ifile;
    ofstream ofile;

    ifile.open(argv[1]);
    ofile.open(argv[2]);

    char c;
    while (ifile.get(c)) {
        //c = ifile.get();
        cout << c << endl;

        ofile << c;
    }

    ofile.close();
    
}