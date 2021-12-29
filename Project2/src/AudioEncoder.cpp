//
// Created by jfngsea on 13/12/21.
//
#include "AudioEncoder.h"

#include <iostream>
#include <vector>
#include <memory>

#include "AudioFile.h"
#include "Golomb.h"
#include "BitStream.h"
#include "GolombSgd.h"
#include "AudioPredictor.h"

int16_t to_int16(float f)
{
    //clipping
    if (f > 1.0) f = 1.0;
    if (f < -1.0) f = -1.0;

    return static_cast<int16_t> (f * static_cast<float> (32767.));
}

float to_float(int i)
{
    float f = static_cast<float> (i / static_cast<float> (32767.));

    //clipping
    if (f > 1.0) f = 1.0;
    if (f < -1.0) f = -1.0;

    return f;
}

int golomb_diviser(int mean) {
    return floor((-1.0/(log2((mean)/(mean+1.0)))))+1;
}

int AudioCodec::encode(std::string finPath, std::string foutPath) {
    AudioCodec::ENC_OPT  opts;
    return AudioCodec::encode(finPath, foutPath, opts);
}

/**
 *
 * @param finPath
 * @param foutPath
 * @return
 */
int AudioCodec::encode(
        std::string finPath, std::string foutPath, ENC_OPT opts) {

    //ofstream ofile("../encoder_ms");
    int division_f = pow(2, opts.quantization_factor);

    AudioFile<float> audioFile;
    if(!audioFile.load(finPath)){
        printf("Exiting...\n");
        return 1;
    }

    map<int,int> hist;

    //AudioPredictor predictor(predictor_order, audioFile.samples);

    // read audio file metadata
    int sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();
    int numSamples = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();

    int numBlocks = (numSamples-opts.predictor_order)/opts.samples_per_block + 1; //gives wrong number  if numSamples==samples_per_block(tbf special case and not really wanted)

    //encode metadata
    //start with default M
    GolombSgd gencoder(foutPath, 'w', opts.starter_golomb_m);

    gencoder.encodeNumber(numChannels);
    gencoder.encodeNumber(opts.samples_per_block);
    gencoder.encodeNumber(opts.predictor_order);
    gencoder.encodeNumber(opts.quantization_factor);

    //encode bigger metadata?

    //encode n fisrts samples and start general predicrtor buffer
    std:vector<AudioPredictor> predictors(numChannels, AudioPredictor(opts.predictor_order));

    //encode predictors base samples
    {
        AudioPredictor basesamplesPredictors[numChannels];

        {
            std::vector<int> firstSamples;
            int16_t fSamplesAvg = 0;

            int residuals[numChannels];
            for (int cIdx = 0; cIdx < numChannels; cIdx++) {
                float sample_f = audioFile.samples[cIdx][0];
                int16_t sample_i16 = to_int16(sample_f);
                if(opts.quantization_factor !=0 ){
                    sample_i16 /= division_f;
                }

                predictors[cIdx].updateBuffer(sample_i16);
                basesamplesPredictors[cIdx].updateBuffer(sample_i16);
                firstSamples.push_back(sample_i16);
                fSamplesAvg += abs(sample_i16);
            }

            fSamplesAvg /= numChannels;
            int fSamplesM = golomb_diviser(fSamplesAvg);
            gencoder.encodeNumber(fSamplesM);
            gencoder.updateM(fSamplesM);

            for (int s: firstSamples) {
                gencoder.encodeNumber(s);
            }
        }

        //encode the rest of the needed samples to make general predictor work
        {
            std::vector<int> residuals;
            int residualsAvg = 0;
            for (int sIdx = 1; sIdx < opts.predictor_order; sIdx++) {


                for (int cIdx = 0; cIdx < numChannels; cIdx++) {
                    int16_t sample_i16 = to_int16(audioFile.samples[cIdx][sIdx]);
                    int prediction = basesamplesPredictors[cIdx].predict_buffered(sample_i16);
                    int residual = sample_i16 - prediction;

                    if(opts.quantization_factor != 0) {
                        residual /= division_f;
                        sample_i16 = residual+prediction;
                    }

                    if(opts.histogram){
                        hist[residual] += 1;
                    }

                    residuals.push_back(residual);
                    residualsAvg += abs(residual);

                    predictors[cIdx].updateBuffer(sample_i16);
                }
            }
            //encode base samples residuals
            if(opts.predictor_order > 1){
                int residualsM = golomb_diviser(residualsAvg);
                gencoder.encodeNumber(residualsM);
                gencoder.updateM(residualsM);

                for (int s: residuals) {
                    gencoder.encodeNumber(s);
                }
            }
        }
    }

    int offset = opts.predictor_order;

    for(int block = 0; block<numBlocks; block++){
        //int block_average[numChannels];
        int block_average = 0;
        int sample_idx_offset = opts.predictor_order -1;
        std::vector<int16_t> residuals;

        for(int blocksample = 0; blocksample<opts.samples_per_block; blocksample++){
            for(int channelIdx=0; channelIdx<numChannels;channelIdx++){
                int sampleIdx = block*opts.samples_per_block+blocksample+offset;
                int16_t  sample_i16 = to_int16(audioFile.samples[channelIdx][sampleIdx]);
                int prediction = predictors[channelIdx].predict_buffered();
                int residual = sample_i16 - prediction;

                if(opts.quantization_factor != 0) {
                    residual /= division_f;
                    sample_i16 = residual+prediction;
                }

                if(opts.histogram){
                    hist[residual] += 1;
                }

                residuals.push_back(residual);
                //block_average[channelIdx] += sampleIdx;
                block_average += abs(residual);
                predictors[channelIdx].updateBuffer(sample_i16);
            }
        }

        block_average /= (opts.samples_per_block*numChannels);

        // calculate block's samples best golomb encoder M
        int block_gm = golomb_diviser(block_average);

        //encode new golomb M with previous block M
        gencoder.encodeNumber(block_gm);

        //redefine golomb encodewr with new M
        gencoder.updateM(block_gm);



        //encode block's residuals
        for (auto r:residuals) {
            gencoder.encodeNumber(r);
        }
    }
    return  0;
}

int AudioCodec::decode(std::string finPath, std::string foutPath, int starter_golomb_m) {
    //int predictor_order = 1;
    //int samples_per_block = 10;
    //int starter_golomb_m = 4;

    std::ofstream ofile("../decode_ms");

    AudioFile<float> audioFile;
    AudioFile<float>::AudioBuffer fout_buffer;
    //todo: assing following metadata:
    // audioFile.setSampleRate(0);
    // audioFile.setBitDepth(0);


    //Golomb* gencoder;
    std::unique_ptr<GolombSgd> gencoder(new GolombSgd(finPath, 'r', starter_golomb_m));

    //read and set file metadata
    int numChannels = gencoder->readNumber();
    int samples_per_block = gencoder->readNumber();
    int predictor_order = gencoder->readNumber();
    int quantization_factor = gencoder->readNumber();

    int mult_f = pow(2, quantization_factor);

    audioFile.setNumChannels(numChannels);
    fout_buffer.resize(numChannels);

    //generate general predictors
    std:vector<AudioPredictor> predictors(numChannels, AudioPredictor(predictor_order));

    //read base samples and setup base predictors
    {
        AudioPredictor basesamplesPredictors[numChannels];
        // read first sample of each channel
        {
            int first_data_m =  gencoder->readNumber();
            ofile << first_data_m << '\n';
            gencoder->updateM(first_data_m);

            std::vector<int> firstSamples;

            for(int cIdx=0; cIdx<numChannels;cIdx++){
                int sample_i = gencoder->readNumber();

                if(quantization_factor !=0 ){
                    sample_i *= mult_f;
                }

                float sample_f = to_float(sample_i);
                fout_buffer[cIdx].push_back(sample_f);

                //update predictors
                predictors[cIdx].updateBuffer(sample_i);
                basesamplesPredictors[cIdx].updateBuffer(sample_i);
            }
        }

        // read and decode following base samples
        {
            if(predictor_order>1){
                int baseSamples_m = gencoder->readNumber();
                ofile << baseSamples_m << '\n';
                gencoder->updateM(baseSamples_m);
            }

            for(int i=1; i<predictor_order;i++){
                for(int cIdx=0; cIdx<numChannels; cIdx++){
                    int residual_i = gencoder->readNumber();

                    if(quantization_factor !=0 ){
                        residual_i *= mult_f;
                    }

                    int sample_i = residual_i + basesamplesPredictors[cIdx].predict_buffered();

                    basesamplesPredictors[cIdx].updateBuffer(sample_i);
                    predictors[cIdx].updateBuffer(sample_i);

                    fout_buffer[cIdx].push_back(to_float(sample_i));
                }
            }
        }
    }

    int num_blocks = 0;

    bool notEOF = true;
    while(notEOF) {
        int block_m = gencoder->readNumber();
        ofile << block_m << '\n';

        gencoder->updateM(block_m);

        //read samples_per_block*numChannels residuals
        for(int sIdx=0; sIdx<samples_per_block; sIdx++){
            if (!notEOF) { break;}
            for(int cIdx=0; cIdx<numChannels; cIdx++){
                int residual = gencoder->readNumber();
                if (gencoder->getEof()){
                    notEOF = false;
                    break;
                }
                int prediction = predictors[cIdx].predict_buffered();
                if(quantization_factor !=0 ){
                    residual *= mult_f;
                }
                int sample_i = residual+prediction;
                predictors[cIdx].updateBuffer(sample_i);
                fout_buffer[cIdx].push_back(to_float(sample_i));
            }
        }
    }

    audioFile.setAudioBuffer(fout_buffer);
    audioFile.save(foutPath);
    return 0;

}