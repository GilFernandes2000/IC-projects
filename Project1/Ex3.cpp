#include "AudioFile.h"

using namespace std;


int main() {

    AudioFile<double> aud;
    bool loaded = aud.load("sample01.wav");


    //new buffer
    AudioFile<double>::AudioBuffer buffer;

    //get original nsamples, nchannels
    int numSamples = aud.getNumSamplesPerChannel();
    int nch = aud.getNumChannels();
    
    //resize new buffer
    buffer.resize(nch);
    for (int i=0; i<nch; i++) {
        buffer[i].resize(numSamples);
    }

    assert(loaded);

    // copy old buffer to new
    for (int c = 0; c<nch; c++) {
        for (int i = 0; i<numSamples; i++) {
            buffer[c][i] = aud.samples[c][i];
        }
    }

    AudioFile<double> outf;
    outf.setAudioBufferSize(nch, numSamples);
    outf.setBitDepth(24);
    outf.setSampleRate(44100);

    bool ok = outf.setAudioBuffer(buffer);

    outf.save("out.wav");
}