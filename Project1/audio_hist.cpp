#include "AudioFile.h"
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main(){
    AudioFile<float> audio;
    bool loaded = audio.load("sample02.wav");
    assert(loaded);

    int channels = audio.getNumChannels();
    int numSamples = audio.getNumSamplesPerChannel();
    map<double, int> hist;

    for(int i = 0; i < channels; i++){
        for (int j = 0; j < numSamples; j++){
            double currentSample = audio.samples[i][j];
            map<double, int>::  iterator it = hist.find(currentSample);
            if(it != hist.end()){
                it -> second++;
            }
            else{
                hist.insert(make_pair(currentSample, 1));
            }
        }
    }
    ofstream ofs("audioHST.txt");
    for(auto it = hist.cbegin(); it != hist.cend(); ++it){ // precorre o iterador do mapa
        ofs << it->first << " - " << it->second << endl; // imprime first - second
    }
    ofs.close();
    return 0;
}