//
// Created by jfngsea on 16/01/22.
//
#include "FCModelFactory.h"

int FCModelFactory::parse_value(std::string value) {
    return std::stoi(value);
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
    this->context.updateContext(c);
    return 0;
}
int FCModelFactory::updateContext(std::string s) {
    this->context.updateContext(s);
    return 0;
}

FCModel FCModelFactory::createModel() {
    FCModel model(this->lang, this->order, this->smoothing);

    for (auto const& row_ptr : this->model){
        auto row_map= row_ptr.second;

        // get total
        auto total = row_map["total"];

        for (auto const& cell_ptr : row_map){
            std::string c = cell_ptr.first;
            int count = cell_ptr.second;

            float prob = utils::probability(count, total, NR_SYMBOLS, smoothing);

            model.set_field(row_ptr.first, c, prob);
        }

        //set submodel probability
        model.set_field(row_ptr.first,"total", total/this->total_chars);
    }

    return model;
}

int FCModelFactory::saveModel(std::string file_out_path) {
    FCModel m = this->createModel();
    return 0;//m.save_to_file(file_out_path);
}
