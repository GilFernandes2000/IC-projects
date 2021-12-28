
#ifndef PROJECT2_IMAGEENCODER_H
#define PROJECT2_IMAGEENCODER_H

#include "ImagePredictor.h"

using namespace std;

namespace ImageEncoder {

    /**
     * @brief 
     * 
     * @param img image to encode
     * @param encodFormat choose between loless and lossy
     * @param predictor choose between linear and nonLinear
     * @param mode to use only if you chose a linear predictor
     * @param shifts quantetization value
     * @return 
     */
    int encode(string img, string encodFormat, string predictor, int mode=1);
};

#endif //PROJECT2_IMAGEENCODER_H