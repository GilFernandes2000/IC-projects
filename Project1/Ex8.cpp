#include "AudioFile.h"
#include <math.h>

using namespace std;


int main(int argc, char *argv[]) {

    AudioFile<float> aud;
    bool loaded = aud.load(argv[1]);


    //new buffer
    AudioFile<float>::AudioBuffer buffer;

    //get original nsamples, nchannels
    int numSamples = aud.getNumSamplesPerChannel();
    int nch = aud.getNumChannels();
    
    //resize new buffer
    buffer.resize(nch);
    for (int i=0; i<nch; i++) {
        buffer[i].resize(numSamples);
    }

    assert(loaded);

    for (int c = 0; c<nch; c++) {
        for (int i = 0; i<numSamples; i++) {
            buffer[c][i] = aud.samples[c][i] / pow(2, atoi(argv[3]));
            //cout << buffer[c][i] << " " << aud.samples[c][i] << endl;
        }
    }

    AudioFile<float> outf;
    outf.setAudioBufferSize(nch, numSamples);
    outf.setBitDepth(16);
    outf.setSampleRate(44100);

    bool ok = outf.setAudioBuffer(buffer);

    outf.save(argv[2]);
}