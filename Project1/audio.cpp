#include "AudioFile.h"
#include <iostream>
#include <cmath>

using namespace std;



void CreateAudio(string file){
    AudioFile<float> audio;
    audio.setNumChannels(2);
    audio.setNumSamplesPerChannel(44100);

    const float sampleRate = 44100.f;
    const float frenquency = 440.f;
    for (int i = 0; i < audio.getNumSamplesPerChannel(); i++){
        for(int c = 0; c < audio.getNumChannels(); c++){
            audio.samples[c][i] = sin ((static_cast<float> (i) / sampleRate) * frenquency * 5.f * M_PI);
        }
    }

    audio.save(file, AudioFileFormat::Wave);
}

void ChangeAndSaveAudio(string inFile, float gainz, string outFile){
    AudioFile<float> audio;
    bool loaded = audio.load(inFile);

    assert(loaded);

    for (int i = 0; i < audio.getNumSamplesPerChannel(); i++){
        for(int c = 0; c < audio.getNumChannels(); c++){
            audio.samples[c][i] = audio.samples[c][i] * gainz;
        }
    }

    audio.save(outFile, AudioFileFormat::Wave);
}

void AudioAnalise(string file){
    AudioFile<float> audio;
    bool loaded = audio.load(file);
    assert(loaded);
    cout << "File Name: " << file << endl;
    cout << "Bit Depth: " << audio.getBitDepth() << endl;
    cout << "Sample Rate: " << audio.getSampleRate() << endl;
    cout << "Num Channels: " << audio.getNumChannels() << endl;
    cout << "Length in Seconds: " << audio.getLengthInSeconds() << endl;
}

int main(){
    string file = "sample02.wav";
    AudioAnalise(file);
    return 0;
}

// compilar com -lsndfile
// g++ audio.cpp -o audio -lsndfile