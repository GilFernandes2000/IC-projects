//
// Created by jfngsea on 16/01/22.
//

#ifndef PROJECT3_FCMODELFACTORY_H
#define PROJECT3_FCMODELFACTORY_H

#include "FCModel.h"
#include "FCModelContext.h"

#include "vector"
#include "algorithm"
#include <numeric>
#include "cctype"
#include <fstream>
#include <sstream>
#include <string>

using COUNTERS = std::map<std::string, std::map<std::string , int>>;

class FCModelFactory {
    COUNTERS counters;
    FCModelContext context;

    std::string lang;
    int order;
    int smoothing;
public:
    /**
     * Loads a model factory (counters+ metadata) from a file
     * @param file_path file with model factory
     * @return
     */
    static FCModelFactory load_from_file(std::string file_path);


    FCModelFactory(std::string lang, int order=1, int smoothing=1): context(order){
        this->lang=lang;
        this->order=order;
        this->smoothing=smoothing;
    };

    FCModelFactory(COUNTERS counters, std::string lang, int order=1, int smoothing=1): FCModelFactory(lang, order, smoothing){
        this->counters=counters;
    };

    /**
     * Saves counters state to file
     * @param file_out_path file to save the counter's state to
     * @return
     */
    int save_to_file(std::string file_out_path);

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
     * Saves Model (probabilities to binary file
     * @param file_out_path path to save the file to
     * @return
     */
    int saveModel(std::string file_out_path);
};

#endif //PROJECT3_FCMODELFACTORY_H
