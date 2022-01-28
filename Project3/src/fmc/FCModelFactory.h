//
// Created by jfngsea on 16/01/22.
//

#ifndef PROJECT3_FCMODELFACTORY_H
#define PROJECT3_FCMODELFACTORY_H

#include "FCModel_BaseClass.h"
#include "FCModel.h"
#include "FCModelContext.h"
#include "utils/math_utils.h"

#include "vector"
#include "algorithm"
#include <numeric>
#include "cctype"
#include <fstream>
#include <sstream>
#include <string>

#include "utils/math_utils.h"

class FCModelFactory: public FCModel_BaseClass<int>{
    int total_chars = 0;

public:

    /**
     * Constructors
     */

    FCModelFactory(std::string lang, int order, int smoothing): FCModel_BaseClass<int>(lang, order, smoothing) {}
    FCModelFactory(MODEL<int> model, std::string lang, int order, int smoothing): FCModel_BaseClass<int>(model, lang, order, smoothing){}
    FCModelFactory(const std::string file_path):FCModel_BaseClass<int>() {
        load_from_file(file_path);
    }

    /**Virtual method implementation
    * @param value
    * @return float representation of value
    */
    int parse_value(std::string value) override;


    int load_from_file(std::string path) {
        auto return_value = FCModel_BaseClass::load_from_file(path);
        context = FCModelContext(this->order);
        return return_value;
    }


    /**
     * Adds char to model
     * @param c
     * @return
     */
    int addChar(char c);
    int addChar(std::string s);

    /**
     *  Reads a file and updates internal counters accordingly
     * @param file_path file path
     * @return
     */
    int readFile(std::string file_path);

    /**
     * TODO: create probabilities using the rigth formulas
     * Creates a probability matrix from the counters
     * @return
     */
    FCModel createModel();

    /**
     * Saves Model (probabilities) to binary file
     * @param file_out_path path to save the file to
     * @return
     */
    int saveModel(std::string file_out_path);
};

#endif //PROJECT3_FCMODELFACTORY_H
