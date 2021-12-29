//
// Created by jfngsea on 13/12/21.
//

#ifndef PROJECT2_AUDIOENCODER_H
#define PROJECT2_AUDIOENCODER_H

#include "AudioFile.h"
#include "AudioPredictor.h"

/**
 * Namespace tih function to handle the encoding and decoding of wave files.
 * Currently only supports 16bit depth files - TODO
 */
namespace AudioCodec {

    typedef struct enc_options {
        bool histogram = false;
        std::string histogram_out_file = "";
        int quantization_factor = 0;
        int predictor_order =1;
        int samples_per_block=10;
        int starter_golomb_m = 4;
    } ENC_OPT;

     /**
      *
      * @param finPath input file (wav file)
      * @param foutPath out file (encoded)
      * @return 0 on success
      */
    int encode(std::string finPath, std::string foutPath, ENC_OPT opts);
    int encode(std::string finPath, std::string foutPath);

    /**
     * Given a encode wave file (using this namespace method) decodes it back into a wav file
     * @param finPath input file (encoded)
     * @param foutPath out file (wave file)
     * @param starter_golomb_m
     * @return
     */
    int decode(std::string finPath, std::string foutPath, int starter_golomb_m=4);



};


#endif //PROJECT2_AUDIOENCODER_H


