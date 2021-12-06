//
// Created by joao- on 22/11/2021.
//
#include<iostream>
#include<fstream>

#ifndef PROJECT2_BITSTREAM_H
#define PROJECT2_BITSTREAM_H

using namespace std;

class BitStream{
    private:
        char mode;
        int currentBit;
        char bitBuffer;
        char byteRead;

        ifstream ifile;
        ofstream ofile;
    
    public:
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

        string readBits(int len) {
            if (mode != 'r')
                throw domain_error("cant write when on read mode"); 

            string s = "";
            for (int i=0; i < len; i++) {
                s += readBit();
            }

            return s;
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
    cout << bin.readBits(8);


    //bin.close();
}

#endif 