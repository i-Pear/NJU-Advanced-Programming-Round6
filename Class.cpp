#include "Class.h"
#include <numbers>

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
    return _call_member_function(func_name).value();
}

std::optional<int> Class::_call_member_function(const std::string&func_name) const{
    if(member_functions.find(func_name)!=member_functions.end()){
        return member_functions.find(func_name)->second();
    }
    for(auto c: inherits){
        auto res=c->_call_member_function(func_name);
        if(res.has_value())return res;
    }
    return {};
}

int Class::get_class_size() const{
    return std::max(_get_class_size(), 1);
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
