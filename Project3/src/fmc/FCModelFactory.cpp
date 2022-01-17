//
// Created by jfngsea on 16/01/22.
//
/**
 * Transforms a char into an appropriate alternative supported by the counters and the model
 * @param c
 * @return return the lowercase of char
 */
char transform_char(char c);
/**
 * @param c
 * @return if char can be used in model
 */
bool useChar(char c);

#include "FCModelFactory.h"

FCModelFactory FCModelFactory::load_from_file(std::string file_path) {
    std::ifstream ifs(file_path);
    std::string tmp;
    //load metadata

    std::string lang;
    getline(ifs, lang);

    getline(ifs, tmp);
    int order = stoi(tmp);
    getline(ifs, tmp);
    int smoothing = stoi(tmp);

    COUNTERS counters;

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
        int count = stoi(line_c[2]);

        counters[ctx][letter] = count;

        line_c.clear();
    }

    return FCModelFactory(counters, lang, order, smoothing);
}


int FCModelFactory::save_to_file(std::string file_out_path) {
    std::ofstream ofs(file_out_path);

    //save metadata
    ofs << this->lang << '\n';
    ofs << this->order << '\n';
    ofs << this->smoothing << '\n';


    for (auto const& row_ptr : this->counters){
        for (auto const& cell_ptr : row_ptr.second){
            ofs << row_ptr.first << ':' << cell_ptr.first << ':' << cell_ptr.second << '\n';
        }
    }

    return 0;
}

int FCModelFactory::addChar(char c) {
    std::string s(1, c);
    return this->addChar(s);
}

int FCModelFactory::addChar(std::string c) {
    // checks if buffer already has enough chars
    if ( !this->context.filled() ) {
        return this->updateContext(c[0]);
    }

    std::string context = this->context.getContext();

    // update counters
    this->counters[context][c] += 1;
    this->counters[context]["total"] += 1;

    //update context
    return this->updateContext(c);
}

int FCModelFactory::readFile(std::string file_path) {
    std::ifstream ifs(file_path);

    if(!ifs.good()) {
        printf("Error loading file: %s\n", file_path.c_str());
    }

    char c;
    while (ifs.get(c))
    {
        if(useChar(c)){
            c = transform_char(c);
            this->addChar(c);
        }
    }

    ifs.close();
    return 0;
}

int FCModelFactory::updateContext(char c) {
    this->context.updateContext(c);
    return 0;
}
int FCModelFactory::updateContext(std::string s) {
    this->context.updateContext(s);
    return 0;
}

// TODO: use coorect math functions
FCModel FCModelFactory::createModel() {
    FCModel model(this->lang, this->order, this->smoothing);

    for (auto const& row_ptr : this->counters){
        auto row_map= row_ptr.second;

        // transform row map into vector containing just the counter's values;
        std::vector<int> row_values;
        std::transform(row_map.begin(), row_map.end(), std::back_inserter(row_values), [](auto &kv){ return kv.second;} );

        // total summ
        int total = std::accumulate(row_values.begin(), row_values.end(), 0);

        for (auto const& cell_ptr : row_map){
            std::string c = cell_ptr.first;
            int count = cell_ptr.second;

            float prob = count/total;

            model.setProbability(row_ptr.first, c[0], prob);
        }
    }

    return model;
}

int FCModelFactory::saveModel(std::string file_out_path) {

    return 0;
}

//----- PRIVATE -----//
char transform_char(char c) {
    return tolower(c);
}

bool useChar(char c) {
    return isalpha(c);
}
