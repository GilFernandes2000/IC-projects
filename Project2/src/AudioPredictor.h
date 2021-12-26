//
// Created by jfngsea on 13/12/21.
//

#ifndef PROJECT2_AUDIOPREDICTOR_H
#define PROJECT2_AUDIOPREDICTOR_H

#include <vector>
#include <cstdint>

#include "boost/circular_buffer.hpp"

using namespace std;

/**
 * @brief 
 * 
 */
class AudioPredictor {
public:

    /**
     *
     * @param order number of previous samples to consider
     */
    AudioPredictor(int order=1);
    AudioPredictor(const AudioPredictor &ap);

    boost::circular_buffer<int> buffer;
    std::unique_ptr<boost::circular_buffer<int>> unique_buffer;

    /**
     * @brief given current predictor state, calculates a prediction
     * 
     * @return int prediction
     */
    int predict_buffered();
    /**
     * @brief updates internal sample buffer
     * 
     * @param samples samples to update buffer with.
     * @return int 0 if all went okay
     */
    int updateBuffer(vector<int16_t> samples);
    /**
     * @brief Updates internal buffer samples
     * 
     * @param sample samples to update buffer 
     * @return int 
     */
    int updateBuffer(int16_t sample);
    /**
     * @brief wrapper method, calculates prediction using buffer state and then updates it with given sample
     * 
     * @param sample sample to be introduced in  buffer
     * @return int16_t prediction
     */
    int16_t predict_buffered(int16_t sample);

    /**
     * @brief Returns the sample in a given position
     * 
     * @param pos position of sample
     * @return int sample in position pos
     */
    int bufferGet(int pos);


private:
    int order;
    //boost::circular_buffer<int16_t> buffer;
};


#endif //PROJECT2_AUDIOPREDICTOR_H
