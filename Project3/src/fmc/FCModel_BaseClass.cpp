//
// Created by jfngsea on 18/01/22.
//

#include "FCModel_BaseClass.h"

template<typename T>
void FCModel_BaseClass<T>::set_field(std::string row, std::string collumn, T value) {
    this->model[row][collumn] =value;
}

template<typename T>
int FCModel_BaseClass<T>::load_from_file(std::string file_path) {
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

    return 1;
}

template<typename T>
int FCModel_BaseClass<T>::save_to_file(std::string file_out_path) {
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