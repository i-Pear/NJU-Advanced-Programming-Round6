#ifndef CLASS_H
#define CLASS_H

#include <functional>
#include <vector>
#include <map>
#include <string>
#include <set>

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
    std::vector<const Class*> v_inherits;

    bool _call_member_function(const std::string& func_name,int& res)const;
    int _get_class_size(std::set<const Class*>& vis) const;
    int _get_virtual_func_table_size() const;
    bool has_virtual_func=false;
    bool has_virtual_inherit=false;
};

#endif //CLASS_H
