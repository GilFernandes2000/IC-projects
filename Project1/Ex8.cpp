

#include "AudioFile.h"

int main(int argc, char const *argv[])
{
    assert(argc == 3, "Wrong number of parameters");

    AudioFile<float> audioIn;
    bool loaded = audioIn.load(argv[1]); //carregar audioFile
    assert(loaded, "Audio file not loaded"); //verificar se esta carregado

    // sample will be divided by 2^quatization_factor
    int quatization_factor = std::stoi(argv[2]);
    int division_factor = pow(2, quatization_factor);
    
    // get og audioIn metadata
    int channels = audioIn.getNumChannels();
    int numSamples = audioIn.getNumSamplesPerChannel();

    //create out file with input file metadata
    AudioFile<float> audioOut = AudioFile<float>();
    audioOut.setNumChannels(channels);
    audioOut.setNumChannels(numSamples);
    audioOut.setAudioBufferSize(channels, numSamples);

    //
    for(int i = 0; i < channels; i++){
        for (int j = 0; j < numSamples; j++){
            double currentSample = audioIn.samples[i][j];
            audioOut.samples[i][j] = currentSample / division_factor;
        }
    }

    // save quantized file
    //! out file and extension still hardcoded
    audioOut.save("../audio_out_"+ std::to_string(quatization_factor) +".wav");

    return 0;
}
