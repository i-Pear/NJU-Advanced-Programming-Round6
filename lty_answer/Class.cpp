#include "Class.h"

void Class::add_inherit_class(const Class*c){
    inherits.push_back(c);
}

void Class::add_virtual_inherit_class(const Class*c){
    v_inherits.push_back(c);
    has_virtual_inherit=true;
}

void Class::add_member_object(const Class*m){
    member_objects.push_back(m);
}

void Class::add_member_function(const std::string&name, int (*f)()){
    member_functions[name]=f;
}

void Class::add_virtual_member_function(const std::string&name, int (*f)()){
    member_functions[name]=f;
    has_virtual_func=true;
}

int Class::call_member_function(const std::string&func_name){
    int res;
    _call_member_function(func_name, res);
    return res;
}

bool Class::_call_member_function(const std::string&func_name, int&res) const{
    if(member_functions.find(func_name)!=member_functions.end()){
        auto iter=member_functions.find(func_name);
        res=(iter->second)();
        return true;
    }
    for(auto c: inherits){
        if(c->_call_member_function(func_name, res)){
            return true;
        }
    }
    return false;
}

int Class::_get_virtual_func_table_size() const{
    int vft_floor=0;
    for(auto c: inherits){
        vft_floor+=c->_get_virtual_func_table_size();
    }
    if(has_virtual_func){
        vft_floor=std::max(vft_floor, 1);
    }
    return vft_floor;
}

int Class::_get_class_size(std::set<const Class*>& vis) const{
    int res=0;
    for(auto c: member_objects){
        res+=c->get_class_size();
    }
    if(has_virtual_inherit){
        res+=8;
    }
    for(auto c: inherits){
        res+=c->_get_class_size(vis);
    }
    for(auto c: v_inherits){
        if(vis.find(c)!=vis.end())continue;
        vis.insert(c);
        res+=c->_get_class_size(vis);
    }
    return res;
}

int Class::get_class_size() const{
    std::set<const Class*> vis;
    int res=_get_class_size(vis);
    res+=_get_virtual_func_table_size()*8;
    return std::max(res, 1);
}
