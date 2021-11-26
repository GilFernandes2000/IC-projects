//
// Created by joao- on 22/11/2021.
//
#include <vector>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <string>

#ifndef PROJECT2_BITSTREAM_H
#define PROJECT2_BITSTREAM_H

using namespace std;

class BitStream{
    private:
        string fileName;
        char fileProcess;
        char* byteBuff;
    public:
        BitStream(string fileName, char fileProcess){
            assert(!fileName.empty());
            assert(fileProcess == 'w' || fileProcess == 'r');

            if(fileProcess == 'w'){
                ifstream ifs(fileName);
            }
            if(fileProcess == 'r'){
                ofstream ofs(fileName);
            }
        };

        char* getLineBytes(string line){
            vector<char> bytes(line.begin(), line.end());
            bytes.push_back('\0');
            char* c = &bytes[0];
            return c;
        }

        void write_bit(char bit){

        }

        char read_bit(char* byte, int pos){
            char tmp = *byte;
            return (tmp >> pos) & 0x1;
        }
};

#endif //PROJECT2_BITSTREAM_H
