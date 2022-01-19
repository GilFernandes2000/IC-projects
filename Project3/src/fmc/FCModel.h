//
// Created by jfngsea on 12/01/22.
//

#ifndef PROJECT3_FCMODEL_H
#define PROJECT3_FCMODEL_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "fstream"

#include "utils/math_utils.h"

// ------- MODEL CHARACTERISTICS ------- //
int const NR_SYMBOLS = 26; // 26 letters
inline char transform_char(char c) {
    return tolower(c);
}

inline bool useChar(char c) {
    return isalpha(c);
}

template <typename T>
using MODEL = std::map<std::string, std::map<std::string, T>>;



/**
 * Class representative of a fcm model
 */
class FCModel {
    std::string lang;
    int order;
    int smoothing;
    MODEL<float> model;

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
    void setValue(std::string row, std::string collumn, float probility){
        this->model[row][collumn] =probility;
    };

    float getEntropy() {
        float entropy = 0.0;

        for(auto const& row_ptr : this->model){
            auto row_map = row_ptr.second;
            std::vector<float> probs;
            std::transform(row_map.begin(), row_map.end(), std::back_inserter(probs), [](const auto& value){ return value.second; });
            // get submodel / row entropy
            auto row_entropy = utils::list_entropy(probs);
            // add it to overall model's entropy using weighted average
            // the "total" field is supposed to contain the sub-model probability
            entropy += row_entropy * row_map["total"];
        }

        return  entropy;
    };
};


#endif //PROJECT3_FCMODEL_H
