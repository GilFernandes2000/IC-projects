//
// Created by jfngsea on 12/01/22.
//

#ifndef PROJECT3_FCMODEL_H
#define PROJECT3_FCMODEL_H

#include <algorithm>
#include "FCModel_BaseClass.h"
#include "utils/math_utils.h"

/**
 *
 */
struct use_model_return {
    std::string lang;
    int num_bits;

    bool operator<(const use_model_return& a) const
    {
        return num_bits < a.num_bits;
    }
};

class FCModel :public FCModel_BaseClass<float>{

public:
    /**
     * Inherited constructors
     */
    using FCModel_BaseClass::FCModel_BaseClass;

    /**
     * Allow the construction of model from a file.
     * @param file_path path to the file containing the model.
     */
    FCModel(const std::string file_path):FCModel_BaseClass<float>() {
        load_from_file(file_path);
        this->context.order=this->order;
    }

    /**
     * Base class virtual method override.
     * Parses a string representation of a probability, read from a file, into a float representation.
     * @param value string probability.
     * @return float representation of value
     */
    float parse_value(std::string value) override {
        return std::stof(value);
    };

    /**
     * Calculates the entropy of the model.
     * @return model's entropy.
     */
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

    /**
     * Allows the usage of a model on a file. Calculates the number of bits needed to represent a text file using a model.
     * @param model_file_path path to the model file.
     * @param file_path path to the file to be analysed.
     * @return <struct use_model_return> containg the language of the model used and the number of bits.
     */
    static use_model_return use_model(std::string model_file_path, std::string file_path) {
        printf("Loading Model: %s\n", model_file_path.c_str());
        FCModel m(model_file_path);
        //m.load_from_file(model_file_path);

        std::ifstream ifs(file_path);
        if (!ifs.good()) {
            printf("File Not Found!\n");
            return {"", -1};
        }

        int total_bits = 0;
        auto def_num_bits = floor(m.getEntropy())+1;

        char c;
        while (ifs.get(c))
        {
            if(useChar(c)){
                c = transform_char(c);
                std::string cs(1, c);

                float prob = m.get_value_update(cs);
                int num_bits = def_num_bits;
                // if there's no probability associated with the current event
                // calculate the probability using laplace formula with n=0 and using the constant u
                if(prob==-1.0){
                    printf("Wrong Prob!\n");
                }
                num_bits = floor(0.0-log2(prob))+1;
                total_bits+=num_bits;
        }

        ifs.close();

        struct use_model_return ret {m.lang, total_bits};

        return ret;
    }

};



#endif //PROJECT3_FCMODEL_H
