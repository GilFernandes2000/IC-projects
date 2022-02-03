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
#include "FCModelContext.h"

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
//------ MODEL CHARACTERISTCS ----//

template<typename T>
using MODEL = std::map<std::string, std::map<std::string , T>>;

template<typename T>
class FCModel_BaseClass {
protected:
    MODEL<T> model;
    FCModelContext context;

    std::string lang;
    unsigned int order;
    unsigned int smoothing;

    virtual T parse_value(std::string value){return 0;};

public:
    float u=-1.0; // equal to smoothing / total_chars, used when calculating the probability of a event thats never occurred

    /**
     * Default C�onstructor
     */
    FCModel_BaseClass():FCModel_BaseClass("", 1, 0){};



    /**
     * Creates a empty model.
     * @param lang
     * @param order
     * @param smoothing
     */
    FCModel_BaseClass(std::string lang, int order, int smoothing): context(order){
            this->lang=lang;
            this->order=order;
            this->smoothing=smoothing;

            //initiate model


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
     * Load a model from a file
     * @param file_path path to the file
     */
    virtual int load_from_file(std::string file_path){
        std::ifstream ifs(file_path);
        std::string tmp;
        //load metadata

        getline(ifs, this->lang);

        getline(ifs, tmp);
        this->order = stoi(tmp);
        getline(ifs, tmp);
        this->smoothing = stoi(tmp);
        getline(ifs, tmp);
        this->u = std::stof(tmp);

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
            T count = parse_value(line_c[2]);

            model[ctx][letter] = count;

            line_c.clear();
        }

        this->model = model;
        return 0;
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
        ofs << this->u << '\n';

        for (auto const& row_ptr : this->model){
            for (auto const& cell_ptr : row_ptr.second){
                ofs << row_ptr.first << ':' << cell_ptr.first << ':' << cell_ptr.second << '\n';
            }
        }
        ofs.close();

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

    /**
     * Updates internal context buffer.
     * @param c char to be inserted in the buffer
     * @return 0 if success
     */
    int update_context(std::string c){
        this->context.update_context(c);
        return 0;
    };


    /**
     *
     * @return the current context
     */
    std::string get_context() {
        return this->context.get_context();
    }

    /**
     * TODO
     * return the probability associated with a given pair (context, char)
     * @return the probability associated with a given pair (context, char)
     */
    T get_value(std::string context, std::string c) {
        auto res = model[context][c];
        // no value associated with the pair (context, char)
        if (res==0.0){
            res = this->u / ( model[context]["total"] + (this->u*NR_SYMBOLS));
        }
        return res;
    };
    T get_value(std::string c) {
        return this->get_value(this->get_context(), c);
    };

    /**
     * return the probability associated with a given pair (context, char) and updates internal context
     * @param c
     * @return
     */
    T get_value_update(std::string c) {
        //check if context has been loaded, if not just updates contexts
        if(!this->context.filled()){
            this->context.update_context(c);
            return -1;
        }

        auto ctx = this->get_context();
        this->context.update_context(c);
        return this->get_value(ctx, c);
    };

};


#endif //PROJECT3_FCMODEL_BASECLASS_H
