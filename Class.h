#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include <map>
#include <string>
#include <optional>

class Class{
public:
    // -------------- Fixed --------------
    void add_inherit_class(const Class*);
    void add_virtual_inherit_class(const Class*);
    void add_member_object(const Class*);
    virtual int get_class_size() const;

    void add_member_function(const std::string& func_name, int (*func_ptr)());
    void add_virtual_member_function(const std::string& func_name, int (*func_ptr)());
    int call_member_function(const std::string& func_name);
    // ------------ Fixed End ------------

    std::vector<const Class*> member_objects;
    std::map<std::string,int (*)()> member_functions;
    std::vector<const Class*> inherits;

    std::optional<int> _call_member_function(const std::string& func_name)const;
    int _get_class_size() const;
};

#endif //CLASS_H
