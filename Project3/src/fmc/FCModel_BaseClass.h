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

    virtual T parse_value(std::string value){return 0;};

public:
    /**
     * Default Constructor
     */
    FCModel_BaseClass():FCModel_BaseClass("", 1, 0){};

    /**
     *
     * @param file_path
     */
    FCModel_BaseClass(std::string file_path){
        std::ifstream ifs(file_path);
        std::string tmp;
        //load metadata

        getline(ifs, this->lang);

        getline(ifs, tmp);
        this->order = stoi(tmp);
        getline(ifs, tmp);
        this->smoothing = stoi(tmp);

        MODEL<T> model;

        std::string line;
        std::vector<std::string> line_c;
        while(getline(ifs, line)){
            std::stringstream ss(line);
            while(getline(ss, tmp, ':')){
                line_c.push_back(tmp);
                if(line_c.size()==3) {
                    break;
                }
            }

            std::string ctx = line_c[0];
            std::string letter = line_c[1];
            int count = parse_value(line_c[2]);

            model[ctx][letter] = count;

            line_c.clear();
        }

        this->model = model;
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
    int save_to_file(std::string file_out_path){
        std::ofstream ofs(file_out_path);

        //save metadata
        ofs << this->lang << '\n';
        ofs << this->order << '\n';
        ofs << this->smoothing << '\n';


        for (auto const& row_ptr : this->model){
            for (auto const& cell_ptr : row_ptr.second){
                ofs << row_ptr.first << ':' << cell_ptr.first << ':' << cell_ptr.second << '\n';
            }
        }

        return 0;
    }

    /**
     * Set the probility of of the model for a given (context/row, current/collum)
     * @param row the context
     * @param collumn current item
     * @param probility the probability
     */
    void set_field(std::string row, std::string collumn, T value){
        this->model[row][collumn] =value;
    };

};


#endif //PROJECT3_FCMODEL_BASECLASS_H
