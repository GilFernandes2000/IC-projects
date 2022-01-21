//
// Created by jfngsea on 16/01/22.
//
#include "FCModelFactory.h"


int FCModelFactory::parse_value(std::string value) {
    return std::stoi(value);

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

    MODEL<int> counters;

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
    this->model[context][c] += 1;
    this->model[context]["total"] += 1;
    this->total_chars++;

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
    std::string s(1, c);
    return this->updateContext(s);
}
int FCModelFactory::updateContext(std::string s) {
    this->context.updateContext(s);
    return 0;
}

FCModel FCModelFactory::createModel() {
    FCModel model(this->lang, this->order, this->smoothing);
    int model_total_chars = 0;

    for (auto const& row_ptr : this->model){
        auto row_map= row_ptr.second;

        // get total
        auto total = row_map["total"];
        model_total_chars += total;

        for (auto const& cell_ptr : row_map){
            std::string c = cell_ptr.first;
            // column name isn't a character but extra information like the row total
            // and therefore needs a different approach
            if (c.size() != 1) {
                continue;
            }
            int count = cell_ptr.second;

            float prob = utils::probability(count, total, NR_SYMBOLS, smoothing);

            model.set_field(row_ptr.first, c, prob);
        }

        // set submodel probability
        // model.set_field(row_ptr.first,"total", total/this->total_chars);
    }

    for (auto const& row_ptr : this->model){
        // calculate row probability
        auto row_map = row_ptr.second;
        float prob = (row_map["total"] + 0.0)/(model_total_chars);
        // set submodel/row probability
        model.set_field(row_ptr.first, "total", prob);

    }


    return model;
}

int FCModelFactory::saveModel(std::string file_out_path) {
    FCModel m = this->createModel();
    return m.save_to_file(file_out_path);
}