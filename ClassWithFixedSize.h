#ifndef CLASS_WITH_FIXED_SIZE_H
#define CLASS_WITH_FIXED_SIZE_H

#include "Class.h"
/**
 * 仅用于重载 get_class_size() 来避免无限递归,
 * 此类仅用于构建测试用例中的成员变量, 不会被其他类继承
 * 此类与需要实现的部分无关
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
