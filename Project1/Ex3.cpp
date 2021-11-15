#include "AudioFile.h"
#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;


int main(int argc, char *argv[]){//dar como argumento o ficheiro para ler e o ficheiro para copia
    
    AudioFile<float> audio;
    bool loaded = audio.load(argv[1]); //carregar audioFile

    assert(loaded); //verificar se esta carregada

    audio.save(argv[2], AudioFileFormat::Wave); // guardar o ficheiro em formato .wav
    
    return 0;
}

// compilar com -lsndfile
// g++ audio.cpp -o audio -lsndfile