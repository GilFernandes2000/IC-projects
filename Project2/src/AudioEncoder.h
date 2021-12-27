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
     * Given a wave files, encodes it using a golomb encoder
     * @param finPath input file (wav file)
     * @param foutPath out file (encoded)
     * @return
     */
    int encode(std::string finPath, std::string foutPath);
    /**
     * Given a encode wave file (using this namespace method) decodes it back into a wav file
     * @param finPath input file (encoded)
     * @param foutPath out file (wave file)
     * @return
     */
    int decode(std::string finPath, std::string foutPath);
};


#endif //PROJECT2_AUDIOENCODER_H


