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
        int currentBit = 8;
        int currentBit_write = 0;

        unsigned char bitBuffer=0;
        char byteRead=0;

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

        /**
         * @brief Destroy the Bit Stream object. Closes Resources first.
         * 
         */
        ~BitStream() {
            this->close();
        }

        /* w */

        //
        void writeBit(int bit) {
            if (mode != 'w')
                throw domain_error("cant write when on read mode");    

            if (bit) {
                bitBuffer |= (0x1<<(7-currentBit_write));
            }

            currentBit_write++;
            if (currentBit_write == 8) {
                //printbincharpad(bitBuffer);
                currentBit_write = 0;
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

        /**
         * @brief 
         * Closes underlying file handlers.
         * If in write mode, writes buffer to file first.
         */
        void close() {
            switch (mode) {
                case 'r':
                    ifile.close();
                    break;
                case 'w':
                    ofile << bitBuffer;
                    ofile.close();
                    break;
            }
        }
        // r        
        char readBit() {
            if (mode != 'r')
                throw domain_error("cant write when on read mode");

            //cout << currentBit;
            if (currentBit == 8) {
                currentBit = 0;
                if (ifile.peek() == EOF) {
                    return EOF;
                }
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
                char c = readBit();
                if (c==EOF) {
                    break;
                }
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