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

    std::string context="";

public:
    int order;

    /**
     * Default contructor
     * @param order the number of character to store for context
     */
    FCModelContext(int order=1) {
        this->order=order;
    }

    /**
     * Adds a new character to the buffer.
     * Enssures that the size of the buffer is always <= that its order
     * @param c character to be introduced
     */
    void update_context(char c){
        context.push_back(c);

        if(context.size() > this->order) {
            context.erase(0);
        }
    }

    void update_context(std::string s){
        context.append(s);

        if(context.size() > this->order) {
            context = context.substr(context.size()-order,order);
        }
    }

    /**
     * @return the current context
     */
    std::string get_context(){
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
