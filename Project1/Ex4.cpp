#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    
    ifstream ifile;
    ofstream ofile;

    ifile.open(argv[1]);
    cout << argv[1] << endl;

    char * magic = new char [3];
    ifile >> magic;

    cout << magic << endl;

    char * width = new char [3];
    ifile >> width;

    cout << width << endl;
    

    char * height = new char [3];
    ifile >> height;

    cout << height << endl;

    char * max = new char [3];
    ifile >> max;

    cout << max << endl;

    ofile.open("out.ppm");
    ofile << magic << endl;
    ofile << width << " " << height << endl;
    ofile << max;

    
    char * buffer = new char [3];
    while (ifile.good()) {
        ifile.read(buffer, 3);
        
        ofile.write(buffer, 3);
    }
        
    //ifile.read(c, 1);

    
}