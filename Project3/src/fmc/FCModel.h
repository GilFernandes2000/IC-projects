//
// Created by jfngsea on 12/01/22.
//

#ifndef PROJECT3_FCMODEL_H
#define PROJECT3_FCMODEL_H

#include <string>
#include <map>

#include "fstream"

int const NR_SYMBOLS = 26+1; // 26 letters + space

using MODEL = std::map<std::string, std::map<char, float>>;

/**
 * Class representative of a fcm model
 */
class FCModel {
    std::string lang;
    int order;
    int smoothing;
    MODEL model;

public:
    FCModel(std::string lang, int order=1, int smoothing=1) {
        this->lang=lang;
        this->order=order;
        this->smoothing=smoothing;
    };

    /**
     * Set the probility of of the model for a given (context/row, current/collum)
     * @param row the context
     * @param collumn current item
     * @param probility the probability
     */
    void setProbability(std::string row, char collumn, float probility){
        this->model[row][collumn] =probility;
    };
};


#endif //PROJECT3_FCMODEL_H
