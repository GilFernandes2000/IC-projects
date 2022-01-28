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

    FCModel(const std::string file_path):FCModel_BaseClass<float>() {
        load_from_file(file_path);
        this->context.order=this->order;
    }

    /**
     * @param value
     * @return float representation of value
     */
    float parse_value(std::string value) override {
        return std::stof(value);
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

    static int use_model(std::string model_file_path, std::string file_path) {
        printf("Loading Model: %s\n", model_file_path.c_str());
        FCModel m(model_file_path);
        //m.load_from_file(model_file_path);

        std::ifstream ifs(file_path);
        if (!ifs.good()) {
            printf("File Not Found!\n");
            return -1;
        }

        int total_bits = 0;

        char c;
        while (ifs.get(c))
        {
            if(useChar(c)){
                c = transform_char(c);
                std::string cs(1, c);

                float prob = m.get_value_update(cs);
                // default value in case there is no probability associated with the pair (context,char)
                int num_bits = m.smoothing;
                // if theres a value replace it
                if(prob!=-1.0){
                    num_bits = floor(0.0- log2(prob))+1;
                }
                total_bits+=num_bits;
            }
        }

        ifs.close();

        return total_bits;
    }

};


#endif //PROJECT3_FCMODEL_H
