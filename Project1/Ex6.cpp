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
    ofstream ofs("audioHST_stereo.txt");
    for(auto it = hist.cbegin(); it != hist.cend(); ++it){ // precorre o iterador do mapa
        ofs << it->first << " - " << it->second << endl; // imprime first - second
    }
    ofs.close();

    float entropySum = 0;
    for (auto const& item : hist){
        float prob = static_cast<float>(item.second)/numSamples;
        entropySum += prob*log2(prob);
    }
    entropySum = -entropySum;
    printf("Entropy stereo: %f\n", (entropySum));

    //Mono Channel Histogram
    map<double, int> histMono;
    map<double, int>::  iterator it;

    for (it = hist.begin(); it != hist.end(); it++)
    {
        map<double, int>::  iterator it_mono = histMono.find(abs(it->first));
        if(it_mono != histMono.end()){
            it_mono -> second += it->second;
        }
        else{
            histMono.insert(make_pair(abs(it->first), it->second));
        }
    }

    entropySum = 0;
    for (auto const& item : histMono){
        float prob = static_cast<float>(item.second)/numSamples;
        entropySum += prob*log2(prob);
    }
    entropySum = -entropySum;
    printf("Entropy Mono: %f\n", (entropySum));

    ofstream ofs_mono("audioHST_mono.txt");
    for(auto it = histMono.cbegin(); it != histMono.cend(); ++it){ // precorre o iterador do mapa
        auto sampleValue = (it->second%2 == 0)? it->second / 2:it->second / 2 +1;
        ofs_mono << it->first << " - " << sampleValue << endl; // imprime first - second
    }
    ofs_mono.close();
    return 0;
}