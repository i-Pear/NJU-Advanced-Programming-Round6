#ifndef CLASS_WITH_FIXED_SIZE_H
#define CLASS_WITH_FIXED_SIZE_H

#include "Class.h"
/**
 * Just for overriding the get_class_size() method,
 * in order to terminate the endless recursive calls
 */
class ClassWithFixedSize : public Class{
private:
    int fixed_size;

public:
    ClassWithFixedSize(int size) : fixed_size(size){

    }

    int get_class_size() const{
        return fixed_size;
    }
};

#endif //CLASS_WITH_FIXED_SIZE_H
