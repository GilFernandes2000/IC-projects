#include "AudioFile.h"

using namespace std;

int main(int argc, char const *argv[])
{
    assert(argc == 4, "Wrong number of Arguments (4)");
    string audioRefPath = argv[1];
    string audioQuantizedPath = argv[2];
    int quantization_factor = std::stoi(argv[3]);

    AudioFile<float> audioRef, audioQuantized;
    bool audioRefLoaded = audioRef.load(audioRefPath);
    bool audioQuantizedLoaded = audioQuantized.load(audioQuantizedPath);

    assert(audioRefLoaded, "Error loading reference audio file.");
    assert(audioQuantizedLoaded, "Error loading quantized  audio file.");

    //get audiofiles metadata
    int channels = audioRef.getNumChannels();
    int numSamples = audioRef.getNumSamplesPerChannel();

    assert(channels == audioQuantized.getNumChannels(), "Number of channels in the reference and quantized audio files do not match.");
    assert(numSamples == audioQuantized.getNumSamplesPerChannel(), "Number of samples per channel in the reference and quantized audio files do not match.");

    // calculate 'de-quantization' factor
    int multFactor = pow(2, quantization_factor);

    double error_sum = 0;
    double signal_sum = 0;

    // 'de-quantize' audio file
    for(int i=0; i<channels; i++){
        for (int j = 0; j < numSamples; j++)
        {
            double refSample = audioRef.samples[i][j];
            double quantizedSample = audioQuantized.samples[i][j] *= multFactor;

            double noise = refSample - quantizedSample;

            signal_sum += pow(refSample, 2);
            error_sum += pow(noise, 2);
        }
    }

    auto snr = signal_sum/error_sum;
    auto snr_sb = 10*log10(snr);

    printf("%s (QBits=%d) => SNR = %0.2f (%0.2f db)", audioRefPath.c_str(), quantization_factor, snr, snr_sb);

    return 0;
}
