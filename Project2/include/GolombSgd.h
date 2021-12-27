//
// Created by jfngsea on 20/12/21.
//

#ifndef PROJECT2_GOLOMBSGD_H
#define PROJECT2_GOLOMBSGD_H

#include <iostream>
#include <string>
#include <memory>
#include "math.h"

#include "BitStream.h"
#include "boost/dynamic_bitset.hpp"

/**
 * Classe que implementa um codificador/descodificador golomb com suporte a numeros negativos (usa sinal).
 * Não usa truncated remainder bits.
 * Lida diretamente com uma bitstream, para ler/escrever ficheiros bit a bit,
 * sendo apenas necessario passar os parametros de inicialização de uma bitstream para o construtor da classe.
 */
class GolombSgd {

public:
    /**
     * @param fpath path do ficheiro a usar pela bitstream.
     * @param fmode modo de abertura do ficheiro.
     * @param m divisor para encoding/decoding.
     */
    GolombSgd(string fpath, char fmode, int m=1) {
        this->m=m;
        this->stream = std::make_unique<BitStream>(fpath, fmode);
    }

    /**
     * Closes Stream before being destroyed assegurando que os buffers são flushed.
     */
    ~GolombSgd() {
        this->closeStream();
    }

    /**
     * Atualiza o divisor M.
     * @param m novo divisor M.
     */
    void updateM(int m){ this->m=m; }

    /**
     * Codifica um numero (suporta numeros negativos) em golomb encoding.
     * @param N Numero a codificar.
     * @return String com a representação em binario do numero N.
     *
     */
    string encodeNumber(int N) {
        int M = this->m;
        string golomb="";

        // handle signal
        if (N<0){
            golomb += "0"; // signal -
            N *= -1;
        } else {
            golomb += "1"; //signal +
        }
        //https://wikimedia.org/api/rest_v1/media/math/render/svg/93cd04de90786d78b2aa7f7b08352cc891bcb967


        //do math
        int q = floor(N/M);
        int r = N % M;

        //encode q
        for (int i = 0; i < q; i++){
            golomb = golomb + "1";
        }
        golomb = golomb + "0";

        //encode r (truncated bits)
        int b = floor(log2(M)) +1;
        string remainder;


        boost::dynamic_bitset<> bitset(b, r);
        boost::to_string(bitset, remainder);

        golomb+=remainder;

        this->stream->writeBits(golomb);

        //printf("g: %s;", golomb.c_str());
        return golomb;
    }

    /**
     * Le e descodifica o proximo numero no ficheiro.
     * @return Numero descodificado.
     */
    int readNumber() {
        if(this->stream->getEof()) { return 0;}

        // https://vicente-gonzalez-ruiz.github.io/Golomb-Rice_coding/
        //this->stream->readBit();//read fisrt separator bit
        char schar = this->stream->readBit();

        int signal = (schar == '1')? 1:-1;
        //if(signal == -1) {this->stream->readBit();}

        if(this->stream->getEof()) { return 0;}
        int count = 0;
        char c = this->stream->readBit();
        if(c == '2') {
            this->eof= true;
            return 0;
        }
        while(c == '1'){
            count++;
            c =this->stream->readBit();
        }

        //handle remainder
        int r=0;
        string remainder = "0";
        int b = floor(log2(this->m)) +1;
        int t = pow(2, b) - this->m;

        for(int i=0; i<b;i++){
            char c = this->stream->readBit();
            if(this->stream->getEof()) {
                this->eof= true;
                return 0;
            }
            remainder+= c;
        }

        r=std::stoi(remainder, nullptr, 2);

        return signal *(count*this->m+r);
    }

    /**
     * Closes BistStream assegurando o flush dos buffers.
     */
    void closeStream() {
        this->stream->close();
    }

    bool getEof() {
        return this->stream->getEof();
    }
private:
    int m;
    std::unique_ptr<BitStream> stream;
    bool eof;
};

#endif //PROJECT2_GOLOMBSGD_H
