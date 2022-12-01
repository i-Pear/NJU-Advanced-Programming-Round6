#include <iostream>
#include "Class.h"
#include "ClassWithFixedSize.h"

const ClassWithFixedSize *Char = new ClassWithFixedSize(1);
const ClassWithFixedSize *Int = new ClassWithFixedSize(4);

#define EXPECTED(exp, val) if(exp!=val) return false;

bool test2() {
/**

#include <iostream>
#pragma pack(1)

class C1{

};

class C2:C1{

};

int main(){
   std::cout << sizeof(C2);
}

*/
    Class *c1 = new Class();
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    EXPECTED(c2->get_class_size(), 1)
    return true;
}

bool test4() {
/**

#include <iostream>
#pragma pack(1)

class C1{
   int member1;
   int member2;
   char member3;
};

class C2:C1{
   int member4;
};

class C3:C2{
   int member5;
   char member6;
};

int main(){
   std::cout << sizeof(C1);
   std::cout << sizeof(C2);
   std::cout << sizeof(C3);
}
*/
    Class *c1 = new Class();
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Char);
    EXPECTED(c1->get_class_size(), 9)
    Class *c2 = new Class();
    c2->add_member_object(Int);
    c2->add_inherit_class(c1);
    EXPECTED(c2->get_class_size(), 13)
    Class *c3 = new Class();
    c3->add_inherit_class(c2);
    c3->add_member_object(Int);
    c3->add_member_object(Char);
    EXPECTED(c3->get_class_size(), 18)
    return true;
}

bool test9() {
/**

#include <iostream>
#pragma pack(1)
using namespace std;

class c1{
public:
    int f1(){
        return 9012;
    }
    int f2(){
        return 9015;
    }
};

int main(){
    c1 c1;
    cout<<c1.f1()<<endl;
    cout<<c1.f2()<<endl;
}

*/
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 9012; });
    c1->add_member_function("f2", [] { return 9015; });
    EXPECTED(c1->call_member_function("f1"), 9012)
    EXPECTED(c1->call_member_function("f2"), 9015)
    return true;
}

bool test18() {
/**

#include <iostream>
#pragma pack(1)
using namespace std;

class c1{
    int a;
    int b;
};

class c2: public c1{
public:
    char c;
    int f2(){
        return 22;
    }
};

class c3: public c1{
public:
    int d;
    int f3(){
        return 3;
    }
};

class c4: public c2,public c3{
public:
    int e;
    int f4(){
        return 4;
    }
};

class c5{
public:
    int f5(){
        return 5;
    }
};

class c6:public c4,public c5{
public:
    c4 f;
    c5 g;
};

int main(){
    cout<<sizeof(c1)<<endl;
    cout<<sizeof(c2)<<endl;
    cout<<sizeof(c3)<<endl;
    cout<<sizeof(c4)<<endl;
    cout<<sizeof(c5)<<endl;
    cout<<sizeof(c6)<<endl;
    c6 c6;
    cout<<c6.f2()<<endl;
    cout<<c6.f3()<<endl;
    cout<<c6.f4()<<endl;
    cout<<c6.f5()<<endl;
}
 */
    Class *c1 = new Class();
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_object(Char);
    c2->add_member_function("f2", [] { return 22; });
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_member_object(Int);
    c3->add_member_function("f3", [] { return 3; });
    Class *c4 = new Class();
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    c4->add_member_function("f4", [] { return 4; });
    Class *c5 = new Class();
    c5->add_member_function("f5", [] { return 5; });
    Class *c6 = new Class();
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_member_object(c4);
    c6->add_member_object(c5);
    EXPECTED(c1->get_class_size(), 8)
    EXPECTED(c2->get_class_size(), 9)
    EXPECTED(c3->get_class_size(), 12)
    EXPECTED(c4->get_class_size(), 25)
    EXPECTED(c5->get_class_size(), 1)
    EXPECTED(c6->get_class_size(), 51)
    EXPECTED(c6->call_member_function("f2"), 22)
    EXPECTED(c6->call_member_function("f3"), 3)
    EXPECTED(c6->call_member_function("f4"), 4)
    EXPECTED(c6->call_member_function("f5"), 5)
    return true;
}

int main() {
    int test_id;
    std::cin >> test_id;
    bool passed;

    if (test_id == 2) {
        passed = test2();
    } else if (test_id == 4) {
        passed = test4();
    } else if (test_id == 9) {
        passed = test9();
    } else if (test_id == 18) {
        passed = test18();
    } else{
        std::cout<<"Testcase "<<test_id<<" is hidden!";
        return 0;
    }
    if (passed) {
        std::cout << "Test " << test_id << " passed";
    } else {
        std::cout << "Test " << test_id << " failed";
    }
}
