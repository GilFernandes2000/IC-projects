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
        signed int N;
        int M;
        int q;
        int r;
    public:
        Golomb(double m, signed int n){              // inicializar a class com o valor do M e o numero a codificar
            M = (int)m;
            N = n;
            q = floor(N/M);
            r = N % M;
        };
        string enconding(){                         // codifica o numero pelo algoritmo de Golomb
            // quocient code
            string golomb;
            for (int i = 0; i < q; i++){
                golomb = golomb + '0';
            }
            golomb = golomb + '1';

            // rem code
            string binary;
            int b = log2(M);
            binary = bitset<10>(r).to_string();

            int n_bits = log2(10) +1; // number of bits needed to represent remainder

            for (int i =binary.length() - n_bits; i <binary.length();i++ ){
                golomb += binary[i];
            }

            return golomb;
        }
};

#endif //PROJECT2_GOLOMB_H
