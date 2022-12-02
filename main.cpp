#include <iostream>
#include "Class.h"
#include "ClassWithFixedSize.h"
#include <functional>

const ClassWithFixedSize *Char = new ClassWithFixedSize(1);
const ClassWithFixedSize *Int = new ClassWithFixedSize(4);

#define EXPECTED(exp, val) if(exp!=val) return false;

bool test1() {
    Class *c1 = new Class();
    EXPECTED(c1->get_class_size(), 1)
    return true;
}

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

bool test3() {
    Class *c1 = new Class();
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Char);
    EXPECTED(c1->get_class_size(), 4 + 4 + 1)
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

bool test5() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 1; });
    c1->add_member_function("f2", [] { return 2; });
    EXPECTED(c1->get_class_size(), 1)
    return true;
}

bool test6() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 1; });
    c1->add_member_function("f2", [] { return 2; });
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_function("f2", [] { return 3; });
    EXPECTED(c2->get_class_size(), 1)
    return true;
}

bool test7() {
    Class *c1 = new Class();
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_function("f1", [] { return 1; });
    c1->add_member_function("f2", [] { return 2; });
    EXPECTED(c1->get_class_size(), 4 * 3)
    return true;
}

bool test8() {
    Class *c1 = new Class();
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_function("f1", [] { return 1; });
    c1->add_member_function("f2", [] { return 2; });
    EXPECTED(c1->get_class_size(), 4 * 3)
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_object(Char);
    EXPECTED(c2->get_class_size(), 4 * 3 + 1)
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

bool test10() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 2948; });
    c1->add_member_function("f2", [] { return 859; });
    EXPECTED(c1->call_member_function("f1"), 2948)
    EXPECTED(c1->call_member_function("f2"), 859)
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_function("f1", [] { return 34; });
    c2->add_member_function("f3", [] { return 847; });
    //EXPECTED(c2->call_member_function("f1"), 34)
    EXPECTED(c2->call_member_function("f2"), 859)
    EXPECTED(c2->call_member_function("f3"), 847)
    return true;
}

bool test11() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 8473; });
    c1->add_member_function("f2", [] { return 123; });
    EXPECTED(c1->call_member_function("f1"), 8473)
    EXPECTED(c1->call_member_function("f2"), 123)
    EXPECTED(c1->get_class_size(), 1)
    return true;
}

bool test12() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 23; });
    c1->add_member_function("f2", [] { return 1313; });
    EXPECTED(c1->call_member_function("f1"), 23)
    EXPECTED(c1->call_member_function("f2"), 1313)
    EXPECTED(c1->get_class_size(), 1)
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_function("f1", [] { return 14; });
    c2->add_member_function("f3", [] { return 827; });
    //EXPECTED(c2->call_member_function("f1"), 14)
    EXPECTED(c2->call_member_function("f2"), 1313)
    EXPECTED(c2->call_member_function("f3"), 827)
    EXPECTED(c2->get_class_size(), 1)
    return true;
}

bool test13() {
    Class *c1 = new Class();
    c1->add_member_object(new ClassWithFixedSize(1));
    c1->add_member_object(new ClassWithFixedSize(2));
    c1->add_member_object(new ClassWithFixedSize(3));
    c1->add_member_object(new ClassWithFixedSize(4));
    c1->add_member_object(new ClassWithFixedSize(5));
    c1->add_member_object(new ClassWithFixedSize(6));
    c1->add_member_object(new ClassWithFixedSize(7));
    c1->add_member_object(new ClassWithFixedSize(8));
    c1->add_member_object(new ClassWithFixedSize(9));
    c1->add_member_object(new ClassWithFixedSize(10));
    c1->add_member_object(new ClassWithFixedSize(1));
    c1->add_member_object(new ClassWithFixedSize(2));
    c1->add_member_object(new ClassWithFixedSize(3));
    c1->add_member_object(new ClassWithFixedSize(4));
    c1->add_member_object(new ClassWithFixedSize(5));
    c1->add_member_object(new ClassWithFixedSize(6));
    c1->add_member_object(new ClassWithFixedSize(7));
    c1->add_member_object(new ClassWithFixedSize(8));
    c1->add_member_object(new ClassWithFixedSize(9));
    c1->add_member_object(new ClassWithFixedSize(10));
    c1->add_member_function("f1", [] { return 8473; });
    c1->add_member_function("f2", [] { return 123; });
    EXPECTED(c1->call_member_function("f1"), 8473)
    EXPECTED(c1->call_member_function("f2"), 123)
    EXPECTED(c1->get_class_size(), 110)
    return true;
}

bool test14() {
    Class *c1 = new Class();
    c1->add_member_function("f2", [] { return 123; });
    c1->add_member_object(new ClassWithFixedSize(100));
    c1->add_member_object(new ClassWithFixedSize(10));
    c1->add_member_function("f1", [] { return 8473; });
    EXPECTED(c1->call_member_function("f1"), 8473)
    EXPECTED(c1->call_member_function("f2"), 123)
    EXPECTED(c1->get_class_size(), 110)
    Class *c2 = new Class();
    c2->add_member_object(new ClassWithFixedSize(1000));
    c2->add_member_object(new ClassWithFixedSize(10));
    c2->add_member_function("f3", [] { return 653; });
    c2->add_member_function("f2", [] { return 1234; });
    c2->add_inherit_class(c1);
    EXPECTED(c2->call_member_function("f1"), 8473)
    //EXPECTED(c1->call_member_function("f2"), 1234)
    EXPECTED(c2->call_member_function("f3"), 653)
    EXPECTED(c2->get_class_size(), 1120)
    return true;
}

bool test15() {
    // multi -> one
    Class *c1 = new Class();
    c1->add_member_object(new ClassWithFixedSize(100));
    Class *c2 = new Class();
    c2->add_member_object(new ClassWithFixedSize(200));
    Class *c3 = new Class();
    c3->add_member_object(new ClassWithFixedSize(300));
    Class *c4 = new Class();
    c4->add_inherit_class(c1);
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    EXPECTED(c4->get_class_size(), 600)
    Class *c5 = new Class();
    c5->add_member_object(new ClassWithFixedSize(10));
    Class *c6 = new Class();
    c6->add_member_object(new ClassWithFixedSize(20));
    Class *c7 = new Class();
    c7->add_member_object(new ClassWithFixedSize(30));
    Class *c8 = new Class();
    c8->add_inherit_class(c5);
    c8->add_inherit_class(c6);
    c8->add_inherit_class(c7);
    EXPECTED(c8->get_class_size(), 60)
    Class *c9 = new Class();
    c9->add_inherit_class(c4);
    c9->add_inherit_class(c8);
    EXPECTED(c9->get_class_size(), 660)
    Class *c10 = new Class();
    c10->add_inherit_class(c9);
    EXPECTED(c10->get_class_size(), 660)
    return true;
}

bool test16() {
    Class *c1 = new Class();
    c1->add_member_function("f1", [] { return 1; });
    Class *c2 = new Class();
    c2->add_member_function("f2", [] { return 2; });
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_member_function("f3", [] { return 3; });
    Class *c4 = new Class();
    c4->add_member_function("f4", [] { return 4; });
    Class *c5 = new Class();
    c5->add_member_function("f5", [] { return 5; });
    Class *c6 = new Class();
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_member_function("f6", [] { return 6; });
    Class *c7 = new Class();
    c7->add_inherit_class(c3);
    c7->add_inherit_class(c6);
    c7->add_member_function("f7", [] { return 77; });

    EXPECTED(c7->call_member_function("f1"), 1)
    EXPECTED(c7->call_member_function("f2"), 2)
    EXPECTED(c7->call_member_function("f3"), 3)
    EXPECTED(c7->call_member_function("f4"), 4)
    EXPECTED(c7->call_member_function("f5"), 5)
    EXPECTED(c7->call_member_function("f6"), 6)
    EXPECTED(c7->call_member_function("f7"), 77)
    return true;
}

bool test17() {
    // diamond
    Class *c1 = new Class();
    c1->add_member_object(new ClassWithFixedSize(100));
    Class *c2 = new Class();
    c2->add_inherit_class(c1);
    c2->add_member_function("f2", [] { return 2; });
    c2->add_member_object(new ClassWithFixedSize(201));
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_member_function("f3", [] { return 3; });
    c3->add_member_object(new ClassWithFixedSize(302));
    Class *c4 = new Class();
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    EXPECTED(c4->get_class_size(), 100 + 100 + 201 + 302 + 4)
    EXPECTED(c4->call_member_function("f2"), 2)
    EXPECTED(c4->call_member_function("f3"), 3)
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

bool test19() {
    Class *c1 = new Class();
    c1->add_virtual_member_function("f1", [] { return 4857; });
    c1->add_member_function("f2", [] { return 419; });
    EXPECTED(c1->get_class_size(), 8)
    return true;
}

bool test20() {
    /**
class c1{
    virtual void f(){}
};

class c2{
virtual void ff(){}
};

class c3: public c1,c2{
public:
    virtual void fff(){}
};

int main(){
    cout<<sizeof(c1)<<endl;
    cout<<sizeof(c2)<<endl;
    cout<<sizeof(c3)<<endl;
}
     */
    Class *c1 = new Class();
    c1->add_virtual_member_function("f1", [] { return 1; });
    Class *c2 = new Class();
    c2->add_virtual_member_function("f2", [] { return 2; });
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_virtual_member_function("f2", [] { return 3; });
    EXPECTED(c1->get_class_size(), 8)
    EXPECTED(c2->get_class_size(), 8)
    EXPECTED(c3->get_class_size(), 16)
    EXPECTED(c1->call_member_function("f1"), 1)
    EXPECTED(c2->call_member_function("f2"), 2)
    EXPECTED(c3->call_member_function("f1"), 1)
    //EXPECTED(c3->call_member_function("f2"), 3)
    return true;
}

bool test21() {
    /**
class c1{

};

class c2:virtual c1{
};

int main(){
    cout<<sizeof(c1)<<endl;
    cout<<sizeof(c2)<<endl;
}
     */
    Class *c1 = new Class();
    EXPECTED(c1->get_class_size(), 1)
    Class *c2 = new Class();
    c2->add_virtual_inherit_class(c1);
    EXPECTED(c2->get_class_size(), 8)
    return true;
}

bool test22() {
/**
class c1{
char a[100];
};

class c2:virtual c1{
    char a[10];
};

class c3:virtual c1{
    char a[5];
};

class c4:c2,c3{
    int a;
};

int main(){
    cout<<sizeof(c1)<<endl;
    cout<<sizeof(c2)<<endl;
    cout<<sizeof(c3)<<endl;
    cout<<sizeof(c4)<<endl;
}
 */
    // diamond virtual
    Class *c1 = new Class();
    c1->add_member_object(new ClassWithFixedSize(100));
    EXPECTED(c1->get_class_size(), 100)
    Class *c2 = new Class();
    c2->add_virtual_inherit_class(c1);
    c2->add_member_object(new ClassWithFixedSize(10));
    EXPECTED(c2->get_class_size(), 118)
    Class *c3 = new Class();
    c3->add_virtual_inherit_class(c1);
    c3->add_member_object(new ClassWithFixedSize(5));
    EXPECTED(c3->get_class_size(), 113)
    Class *c4 = new Class();
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    EXPECTED(c4->get_class_size(), 135)
    return true;
}

bool test23() {
    /**
#pragma pack(1)

class c1{
    virtual void f1(){}
};

class c2{
    void f2(){}
};

class c3:c1,c2{
    c1 c1;
    c2 c2;
    virtual void f3(){}
};


int main(){
    cout<<sizeof(c1)<<endl;
    cout<<sizeof(c2)<<endl;
    cout<<sizeof(c3)<<endl;
}
     */
    Class *c1 = new Class();
    c1->add_virtual_member_function("f1", [] { return 1; });
    EXPECTED(c1->get_class_size(), 8)
    EXPECTED(c1->call_member_function("f1"), 1)
    Class *c2 = new Class();
    c2->add_member_function("f2", [] { return 2; });
    EXPECTED(c2->get_class_size(), 1)
    EXPECTED(c2->call_member_function("f2"), 2)
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_member_object(c1);
    c3->add_member_object(c2);
    c3->add_virtual_member_function("f2", [] { return 3; });
    EXPECTED(c3->get_class_size(), 17)
    EXPECTED(c3->call_member_function("f1"), 1)
    //EXPECTED(c3->call_member_function("f2"), 3)
    return true;
}

bool test24() {
    /**
#pragma pack(1)

class c1{
    virtual void f1(){}
};

class c2{
    virtual void f2(){}
};

class c3:public c1,public c2{
    virtual void f3(){}
};

class c4{
    virtual void f4(){}
};

class c5{
    virtual void f5(){}
};

class c6:public c4,public c5{
    virtual void f6(){}
};

class c7:public c3,public c6{
    virtual void f7(){}
};

int main(){
    cout<<sizeof(c7);
}
     */
    if (!test23())return false;
    Class *c1 = new Class();
    c1->add_virtual_member_function("f1", [] { return 1; });
    Class *c2 = new Class();
    c2->add_virtual_member_function("f2", [] { return 1; });
    Class *c3 = new Class();
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_virtual_member_function("f3", [] { return 1; });
    Class *c4 = new Class();
    c4->add_virtual_member_function("f4", [] { return 1; });
    Class *c5 = new Class();
    c5->add_virtual_member_function("f5", [] { return 1; });
    Class *c6 = new Class();
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_virtual_member_function("f6", [] { return 1; });
    Class *c7 = new Class();
    c7->add_inherit_class(c3);
    c7->add_inherit_class(c6);
    c7->add_virtual_member_function("f7", [] { return 1; });
    EXPECTED(c7->get_class_size(), 32)
    return true;
}

bool test25() {
    /**
class c1{
    char a[100];
};

class c2:virtual c1{
    char q[200];
};

class c3:virtual c1{
    char w[300];
};

class c4:c2,c3{
    int r;
};

class c5{

};

class c6:c4{
    c5 cc5;
};

int main(){
    cout<<sizeof(c6)<<endl;
}
     */
    Class *c1 = new Class(); // 100
    Class *c2 = new Class(); // 100+200
    Class *c3 = new Class(); // 100+300
    Class *c4 = new Class(); // 300+
    Class *c5 = new Class();
    Class *c6 = new Class();
    c6->add_inherit_class(c4);
    EXPECTED(c6->get_class_size(), 1)
    c6->add_member_object(c5);
    c1->add_member_object(new ClassWithFixedSize(100));
    c2->add_virtual_inherit_class(c1);
    c4->add_inherit_class(c2);
    c2->add_member_function("f2", [] { return 2; });
    c2->add_member_object(new ClassWithFixedSize(200));
    c3->add_virtual_inherit_class(c1);
    c3->add_member_object(new ClassWithFixedSize(300));
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    c3->add_member_function("f3", [] { return 3; });
    c5->add_member_function("f5", [] { return 55; });
    EXPECTED(c6->get_class_size(), 621)
    EXPECTED(c6->call_member_function("f2"), 2)
    EXPECTED(c6->call_member_function("f3"), 3)
    return true;
}

int main() {
    std::function<bool()> tests[] = {
            test1,
            test2,
            test3,
            test4,
            test5,
            test6,
            test7,
            test8,
            test9,
            test10,
            test11,
            test12,
            test13,
            test14,
            test15,
            test16,
            test17,
            test18,
            test19,
            test20,
            test21,
            test22,
            test23,
            test24,
            test25,
    };
    int test_id;
    std::cin >> test_id;
    bool pass = tests[test_id - 1]();
    if (pass) {
        std::cout << "TesT " << test_id << " passEd\n";
    } else {
        std::cout << "TesT " << test_id << " failed\n";
    }
    std::cout << "Eof";
}