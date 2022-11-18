#ifndef CLASS_H
#define CLASS_H

#include <string>

class Class{
public:

    void add_inherit_class(const Class*);
    void add_virtual_inherit_class(const Class*);
    void add_member_object(const Class*);

    virtual int get_class_size() const;

    void add_member_function(const std::string& func_name, int (*func_ptr)());
    void add_virtual_member_function(const std::string& func_name, int (*func_ptr)());

    int call_member_function(const std::string& func_name);
};

#endif //CLASS_H
