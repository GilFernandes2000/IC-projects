//
// Created by jfngsea on 21/12/21.
//

#ifndef PROJECT2_TESTBITSTREAM_H
#define PROJECT2_TESTBITSTREAM_H

#include "BitStream.h"

int test_bitstream_write() {
    string fpath = "../golombsgd.out";
    BitStream s(fpath, 'w');

    s.writeBits("10000");
    s.writeBits("10001");
    s.writeBits("10010");
    s.writeBits("10011");
    s.writeBits("10101");

    s.close();
    return 0;
}

int test_bitstream_read() {
    string fpath = "../golombsgd.out";
    BitStream s(fpath, 'r');
    string f ="";
    int count = 0;
    while(true) {
        char c = s.readBit();
        f+= c;
        if(count == 7){
            f+= ' ';
            count=-1;
        }

        if(c==EOF){
            printf("EOF\n");
            break;
        }
        count++;
    }

    int l = f.length();
    return l;
}

#endif //PROJECT2_TESTBITSTREAM_H
