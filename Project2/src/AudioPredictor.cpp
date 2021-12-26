//
// Created by jfngsea on 13/12/21.
//

#include "AudioPredictor.h"
#include "boost/circular_buffer.hpp"
#include <memory>


AudioPredictor::AudioPredictor(int order) : buffer(order) {
    this->order= order;
    buffer = boost::circular_buffer<int>(order);//
    this->unique_buffer = make_unique<boost::circular_buffer<int>>(order);
}

AudioPredictor::AudioPredictor(const AudioPredictor &ap) : AudioPredictor(ap.order){}


int16_t AudioPredictor::predict_buffered(int16_t sample) {
    auto prediction = this->predict_buffered();
    this->updateBuffer(sample);
    return prediction;
}

int AudioPredictor::predict_buffered() {
    int o = this->order;
    int16_t prediction = 0;
    int multFactor = 1;

    if(o == 0)  return prediction;

    for(int i =1; i<o; i++){

        if(i==o) {
            prediction += multFactor*this->bufferGet(i-1);
        } else {
            prediction += multFactor*o*this->bufferGet(i-1);
        }

        multFactor*=-1;
    }

    return prediction;
}

int AudioPredictor::updateBuffer(int16_t sample) {
    this->buffer.push_front(sample);
    return 0;
}

int AudioPredictor::bufferGet(int pos) {
    return  this->buffer.at(pos);
}

int AudioPredictor::updateBuffer(vector<int16_t> samples) {
    for(int16_t sample: samples){
        this->updateBuffer(sample);
    }
    return 0;
}