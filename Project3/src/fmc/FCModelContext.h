//
// Created by jfngsea on 16/01/22.
//

#ifndef PROJECT3_FCMODELCONTEXT_H
#define PROJECT3_FCMODELCONTEXT_H

#include <string>

/**
 * Class to handle context for a fcm.
 * It uses a string as a container instead of a more general circular_buffer given the specificity of its application
 */
class FCModelContext {
    int order;
    std::string context="";

public:

    /**
     * Default contructor
     * @param order the number of character to store for context
     */
    FCModelContext(int order) {
        this->order=order;
    }

    /**
     * Adds a new character to the buffer.
     * Enssures that the size of the buffer is always <= that its order
     * @param c character to be introduced
     */
    void updateContext(char c){
        context.push_back(c);

        if(context.size() > this->order) {
            context.erase(0);
        }
    }

    /**
     * @return the current context
     */
    std::string getContext(){
        return context;
    }

    /**
     * @return the current buffer size
     */
    int size() {
        return context.size();
    }

    /**
     * @return if buffer has reached its maximum size
     */
    bool filled() {
        return this->size()== this->order;
    }
};

#endif //PROJECT3_FCMODELCONTEXT_H
