#include<iostream>
#include<fstream>

using namespace std;

class BitStream{
    public:
        char mode;
        int currentBit;
        char bitBuffer;
        char byteRead;

        ifstream ifile;
        ofstream ofile;

        BitStream(string fname, char m) {
            
            if (m == 'w') {
                ofile.open(fname);
                mode = m;
            } else if (m == 'r') {
                ifile.open(fname);
                mode = m;
            } else {
                throw invalid_argument("mode has to be \'w\' or \'r\'");
            }
        }

        /* w */

        //
        void writeBit(int bit) {
            if (mode != 'w')
                throw domain_error("cant write when on read mode");    

            if (bit) {
                bitBuffer |= (1<<(7-currentBit));
            }

            currentBit++;
            if (currentBit == 8) {
                //printbincharpad(bitBuffer);
                currentBit = 0;
                ofile << bitBuffer;
                bitBuffer = 0;
            }         
        }

        void writeBits(string bits) {
            if (mode != 'w')
                throw domain_error("cant write when on read mode");
            
            //string bits_str = to_string(bits);

            for (char& c : bits) {
                //cout << c - '0';
                writeBit(c - '0');
            }
            
        }   

        void close() {
            while (currentBit) {
                writeBit(0);
            }

            //ofile << "test";
        }
        // r        
        char readBit() {
            if (mode != 'r')
                throw domain_error("cant write when on read mode");
            
            //cout << currentBit;
            if (currentBit == 8) {
                currentBit = 0;
            }

            if (currentBit == 0) {
                ifile.get(byteRead);
            }

            char byteAux = (1<<(7-currentBit));
            char out = (byteRead & byteAux) ? '1' : '0';

            currentBit++;
            return out;
            
        }

        char readBits() {
            if (mode != 'r')
                throw domain_error("cant write when on read mode"); 
        }

        //tester func
        void printbincharpad(char c) {
            for (int i = 7; i >= 0; --i)
            {
                putchar( (c & (1 << i)) ? '1' : '0' );
            }
            putchar('\n');
        }
};

int main(void) {
   /* BitStream b("out", 'w');
    
    b.writeBits("00100011");
    b.writeBits("00100010");
    b.writeBits("00100100");
    
    /*
    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(1);
    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(1);
    b.writeBit(1);
    
    b.close();
*/



    BitStream bin("out", 'r');
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();
    cout << bin.readBit();


    //bin.close();

}