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
        // fname -> file name
        // m -> mode
        //      - 'w' for writing
        //      - 'r' for reading
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

        // Writes 1 bit to file
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

        // writes bits to file
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
            if (mode == 'w') {
                while (currentBit) 
                    writeBit(0);
                
                ofile.close();
            } else
                ifile.close();
        }
        
        
        // r        
        // Reads one bit from file
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
        
        // Reads len bits from file
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
#endif 