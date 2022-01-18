//
// Created by jfngsea on 16/01/22.
//

#ifndef PROJECT3_FCMODELFACTORY_H
#define PROJECT3_FCMODELFACTORY_H

#include "FCModel_BaseClass.h"
#include "FCModel.h"
#include "FCModelContext.h"

#include "vector"
#include "algorithm"
#include <numeric>
#include "cctype"
#include <fstream>
#include <sstream>
#include <string>

#include "utils/math_utils.h"

class FCModelFactory: public FCModel_BaseClass<int>{
    FCModelContext context;
    int total_chars = 0;
public:

    /**
     * Constructors
     */

    FCModelFactory(std::string lang, int order, int smoothing): FCModel_BaseClass<int>(lang, order, smoothing), context(order) {}
    FCModelFactory(MODEL<int> model, std::string lang, int order, int smoothing): FCModel_BaseClass<int>(model, lang, order, smoothing), context(order) {}
    FCModelFactory(std::string path): FCModel_BaseClass<int>(), context(this->order) {
        this->load_from_file(path);
    }

    /**Virtual method implementation
    * @param value
    * @return float representation of value
    */
    int parse_value(std::string value);

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
     * Updates internal context buffer.
     * @param c char to be inserted in the buffer
     * @return 0 if success
     */
    int updateContext(char c);
    int updateContext(std::string c);

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
