/* wyy-answers */
#include "Class.h"

void Class::add_inherit_class(const Class *c)
{
    fathers.emplace_back(c);
}

void Class::add_virtual_inherit_class(const Class *c)
{
    v_fathers.emplace_back(c);
    have_vbptr = true;
}

void Class::add_member_object(const Class *c)
{
    members.emplace_back(c);
}

int Class::get_class_size() const
{
    int res = 0;
    res += get_class_size_except_v_ancestors();
    std::set<const Class *> v_ancestors;
    get_v_ancestors(v_ancestors);
    for (const Class *v_ancestor : v_ancestors)
    {
        res += v_ancestor->get_class_size_except_v_ancestors();
    }
    return res == 0 ? 1 : res;
}

void Class::add_member_function(const std::string &func_name, int (*func_ptr)())
{
    funcs[func_name] = func_ptr;
}

void Class::add_virtual_member_function(const std::string &func_name, int (*func_ptr)())
{
    funcs[func_name] = func_ptr;
    have_vfptr = true;
}

int Class::call_member_function(const std::string &func_name)
{
    int ret;
    get_func_ret(func_name, ret);
    return ret;
}
