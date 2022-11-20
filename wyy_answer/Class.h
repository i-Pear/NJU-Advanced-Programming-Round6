/* wyy-answers */
#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <map>
#include <set>
#include <vector>

class Class
{
public:
    bool have_vfptr = false;
    bool have_vbptr = false;
    std::map<std::string, int (*)()> funcs;
    std::vector<const Class *> members;
    std::vector<const Class *> fathers;
    std::vector<const Class *> v_fathers;

    void add_inherit_class(const Class *);
    void add_virtual_inherit_class(const Class *);
    void add_member_object(const Class *);

    virtual int get_class_size() const;

    void add_member_function(const std::string &func_name, int (*func_ptr)());
    void add_virtual_member_function(const std::string &func_name, int (*func_ptr)());

    int call_member_function(const std::string &func_name);

    bool get_func_ret(const std::string &func_name, int &ret) const
    {
        if (funcs.count(func_name) == 0)
        {
            for (const Class *f : fathers)
            {
                if (f->get_func_ret(func_name, ret))
                {
                    return true;
                }
            }
            return false;
        }

        auto it = funcs.find(func_name);
        ret = (it->second)();
        return true;
    };

    int get_class_size_except_v_ancestors() const
    {
        int res = 0;
        for (const Class *c : members)
        {
            res += c->get_class_size();
        }
        for (const Class *c : fathers)
        {
            res += c->get_class_size_except_v_ancestors();
        }
        if (have_vbptr | have_vfptr)
        {
            if (!can_reuse_father_vptr())
                res += 8;
        }
        return res;
    };

    void get_v_ancestors(std::set<const Class *> &target) const
    {
        for (const Class *c : v_fathers)
        {
            target.insert(c);
            c->get_v_ancestors(target);
        }
        for (const Class *c : fathers)
        {
            c->get_v_ancestors(target);
        }
    };

    bool can_reuse_father_vptr() const
    {
        for (const Class *c : fathers)
        {
            if (c->have_vbptr | c->have_vfptr)
                return true;
        }
        return false;
    };
};

#endif // CLASS_H
