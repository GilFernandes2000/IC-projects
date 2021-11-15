#include "AudioFile.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(int argc, char* argv[]){
    assert(argc == 2);
    AudioFile<float> audio;
    bool loaded = audio.load(argv[1]);
    assert(loaded);

    int channels = audio.getNumChannels(); // numero de canais no fhciero
    int numSamples = audio.getNumSamplesPerChannel(); // numero de samples por canal
    map<double, int> hist;

    // criaçao do histograma do ficheiro 
    for(int i = 0; i < channels; i++){
        for (int j = 0; j < numSamples; j++){
            double currentSample = audio.samples[i][j];
            map<double, int>::  iterator it = hist.find(currentSample); //
            if(it != hist.end()){
                it -> second++;
            }
            else{
                hist.insert(make_pair(currentSample, 1));
            }
        }
    }
    ofstream ofs("audioHST.txt");
    
    // copia o histograma para um ficheiro 
    for(auto it = hist.cbegin(); it != hist.cend(); ++it){ // precorre o iterador do mapa
        ofs << it->first << " - " << it->second << endl; // imprime first - second
    }
    ofs.close();
    return 0;
}