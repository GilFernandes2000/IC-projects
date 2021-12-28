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
namespace AudioEncoder {
     /**
      *
      * @param finPath input file (wav file)
      * @param foutPath out file (encoded)
      * @param predictor_order
      * @param samples_per_block
      * @param starter_golomb_m
      * @return 0 on success
      */
    int encode(std::string finPath, std::string foutPath, int predictor_order=1, int samples_per_block = 10, int starter_golomb_m = 4);
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


