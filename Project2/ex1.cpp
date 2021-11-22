#include<iostream>
#include<fstream>

using namespace std;

class BitStream{
    public:
        char mode;
        int currentBit;
        char bitBuffer;

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
                printbincharpad(bitBuffer);
                currentBit = 0;
                ofile << bitBuffer;
                bitBuffer = 0;

            }         
        }

        void writeBits(int bit) {
            if (mode != 'w')
                throw domain_error("cant write when on read mode"); 
        }   

        void close() {
            while (currentBit) {
                writeBit(0);
            }

            //ofile << "test";
        }
        // r        
        char readBit() {
            if (mode != 'w')
                throw domain_error("cant read when on write mode"); 
        }

        char readBits() {
            if (mode != 'w')
                throw domain_error("cant read when on write mode"); 
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
    BitStream b("out", 'w');

    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(1);
    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(0);
    b.writeBit(1);
    b.writeBit(1);

    b.close();

}