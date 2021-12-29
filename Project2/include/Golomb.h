#include <vector>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <math.h>
#include <bitset>
#include <iostream>

#ifndef PROJECT2_GOLOMB_H
#define PROJECT2_GOLOMB_H

using namespace std;

class Golomb{
    private:
        int M;
    public:

        /**
         * @brief Constroi um nvov objeto Golomb
         * 
         * @param m divisor para encoding/decoding
         */
        Golomb(double m){              // inicializar a class com o valor do M e o numero a codificar
            M = (int)m;
        };

        /**
         * @brief c
         * 
         * @param N numero ser codificado
         * @return o numero codificado no formato de string 
         */
        string encoding(signed int N){                         // codifica o numero pelo algoritmo de Golomb
            int q = (int)(floor(N/M));
            int r = N % M;

            // quocient code
            string golomb;
            for (int i = 0; i < q; i++){
                golomb = golomb + '0';
            }
            golomb = golomb + '1';

            // rem code
            string binary;
            int b = (int)(log2(M));
            binary = bitset<10>(r).to_string();

            if (r < pow(2,b+1)){
                binary = bitset<10>(r).to_string();
                for (int i = (int)(binary.length() - b); i <binary.length();i++ ){
                    golomb += binary[i];
                }
            }
            else{
                r = r + pow(2, b+1) - M;
                binary = bitset<10>(r).to_string();
                for (int i = (int)(binary.length() - b - 1); i <binary.length();i++ ){
                    golomb += binary[i];
                }
            }

            return golomb;
        }
};

#endif //PROJECT2_GOLOMB_H
