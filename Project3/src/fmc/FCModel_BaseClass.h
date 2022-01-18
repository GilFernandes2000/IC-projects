//
// Created by jfngsea on 18/01/22.
//

#ifndef PROJECT3_FCMODEL_BASECLASS_H
#define PROJECT3_FCMODEL_BASECLASS_H

#include "map"
#include "vector"
#include "string"
#include "sstream"
#include "fstream"

//------ MODEL CHARACTERISTCS ----//
int const NR_SYMBOLS = 26; // 26 letters
/**
 * Transforms a char into an appropriate alternative supported by the counters and the model
 * @param c
 * @return return the lowercase of char
 */
 inline char transform_char(char c) {
    return tolower(c);
}
/**
 * @param c
 * @return if char can be used in model
 */
inline bool useChar(char c) {
    return isalpha(c);
}

template<typename T>
using MODEL = std::map<std::string, std::map<std::string , T>>;

template<typename T>
class FCModel_BaseClass {
protected:
    MODEL<T> model;

    std::string lang;
    int order;
    int smoothing;

    T parse_value(std::string value){return 0;};

    /**
     *
     * @param file_path
     * @return
     */
    int load_from_file(std::string file_path);

public:
    /**
     * Default Constructor
     */
    FCModel_BaseClass(){
        this->order=1;
        this->smoothing=0;
        this->lang="";
    };

    /**
     * Creates a empty model.
     * @param lang
     * @param order
     * @param smoothing
     */
    FCModel_BaseClass(std::string lang, int order, int smoothing=0){
            this->lang=lang;
            this->order=order;
            this->smoothing=smoothing;
    };

    /**
     * Creates a filled model
     * @param model
     * @param lang
     * @param order
     * @param smoothing
     */
    FCModel_BaseClass(MODEL<T> model, std::string lang, int order=1, int smoothing=0): FCModel_BaseClass(lang, order, smoothing){
        this->model=model;
    };

    /**
     * Saves counters state to file
     * @param file_out_path file to save the counter's state to
     * @return
     */
    int save_to_file(std::string file_out_path);

    /**
     * Set the probility of of the model for a given (context/row, current/collum)
     * @param row the context
     * @param collumn current item
     * @param probility the probability
     */
    void set_field(std::string row, std::string collumn, T value);

};


#endif //PROJECT3_FCMODEL_BASECLASS_H
