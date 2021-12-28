
#ifndef PROJECT2_IMAGEENCODER_H
#define PROJECT2_IMAGEENCODER_H

#include "ImagePredictor.h"

using namespace std;

namespace ImageEncoder {

    /**
     * @brief 
     * 
     * @param img image to encode
     * @param fileOut file where the encoded image is going to be written
     * @param encodFormat choose between loless and lossy
     * @param predictor choose between linear and nonLinear
     * @param mode to use only if you chose a linear predictor
     * @param shifts quantetization value
     * @return 
     */
    int encode(string img, string fileOut, string encodFormat, string predictor, int mode, int shifts);
};

#endif //PROJECT2_IMAGEENCODER_H