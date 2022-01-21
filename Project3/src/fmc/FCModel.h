//
// Created by jfngsea on 12/01/22.
//

#ifndef PROJECT3_FCMODEL_H
#define PROJECT3_FCMODEL_H

#include <algorithm>
#include "FCModel_BaseClass.h"
#include "utils/math_utils.h"

class FCModel :public FCModel_BaseClass<float>{

public:
    /**
     * Inherited constructors
     */
    using FCModel_BaseClass::FCModel_BaseClass;

    /**
     * @param value
     * @return float representation of value
     */
    float parse_value(std::string value) override {
        return std::stof(value);
    };

    float get_entropy() {
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
