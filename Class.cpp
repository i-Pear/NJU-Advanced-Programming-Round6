#include "Class.h"

void Class::add_inherit_class(const Class*c){
    inherits.push_back(c);
}

void Class::add_virtual_inherit_class(const Class*c){

}

void Class::add_member_object(const Class*m){
    member_objects.push_back(m);
}

void Class::add_member_function(const std::string&name, int (*f)()){
    member_functions[name]=f;
}

void Class::add_virtual_member_function(const std::string&name, int (*f)()){

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

int Class::get_class_size() const{
    int res=_get_class_size();
    return std::max(res, 1);
}

int Class::_get_class_size() const{
    int res=0;
    for(auto c: member_objects){
        res+=c->get_class_size();
    }
    for(auto c: inherits){
        res+=c->_get_class_size();
    }
    return res;
}
