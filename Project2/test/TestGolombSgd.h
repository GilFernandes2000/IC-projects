//
// Created by jfngsea on 21/12/21.
//

#ifndef PROJECT2_TESTGOLOMBSGD_H
#define PROJECT2_TESTGOLOMBSGD_H

#include "GolombSgd.h"
int testgolombsgd() {

    GolombSgd gw("../golombsgd.out", 'w', 10);

    /*for(int i=0; i<20;i++){
        string g = gw.encodeNumber(i);
    }*/

    for(int i = 0; i>-20; i--){
        string g = gw.encodeNumber(i);
        printf("g: %s; ", g.c_str());

    }

    gw.closeStream();

    GolombSgd gr("../golombsgd.out", 'r', 10);

    while(true) {
        int n = gr.readNumber();
        if(gr.getEof()){
            printf("\nEOF\n");
            break;
        }
        printf("d: %d; ", n);
    }

    /*for(int i=0; i<20;i++){
        int n = gr.readNumber();
        if(gr.getEof()){
            printf("\nEOF\n");
        }
        printf("d: %d; ", n);
    }*/
    return  0;
}

#endif //PROJECT2_TESTGOLOMBSGD_H
