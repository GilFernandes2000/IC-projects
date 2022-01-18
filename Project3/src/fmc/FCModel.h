//
// Created by jfngsea on 12/01/22.
//

#ifndef PROJECT3_FCMODEL_H
#define PROJECT3_FCMODEL_H

#include "FCModel_BaseClass.h"

class FCModel :public FCModel_BaseClass<float>{

public:
    /**
     * Inherited constructors
     */
    using FCModel_BaseClass::FCModel_BaseClass;

    /**
     * Allows the loading of a model from a file
     * @param path
     */
    FCModel(std::string path) {
        this->load_from_file(path);
    }

    float get_entropy();

    /**
     * @param value
     * @return float representation of value
     */
    float parse_value(std::string value);
};


#endif //PROJECT3_FCMODEL_H
