#include <iostream>
#include "Class.h"
#include "ClassWithFixedSize.h"

const ClassWithFixedSize*Char=new ClassWithFixedSize(1);
const ClassWithFixedSize*Int=new ClassWithFixedSize(4);

#define EXPECTED(exp, val) if(exp!=val) return false;

bool test1(){
    auto c1=new Class;
    EXPECTED(c1->get_class_size(), 1)
    return true;
}

bool test2(){
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
    auto c1=new Class;
    auto c2=new Class;
    c2->add_inherit_class(c1);
    EXPECTED(c2->get_class_size(), 1)
    return true;
}

bool test3(){
    auto c1=new Class;
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Char);
    EXPECTED(c1->get_class_size(), 4+4+1)
    return true;
}

bool test4(){
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

int main(){
   std::cout << sizeof(C2);
}
*/
    auto c1=new Class;
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Char);
    EXPECTED(c1->get_class_size(), 9)
    auto c2=new Class;
    c2->add_member_object(Int);
    c2->add_inherit_class(c1);
    EXPECTED(c2->get_class_size(), 13)
    auto c3=new Class;
    c3->add_inherit_class(c2);
    c3->add_member_object(Int);
    c3->add_member_object(Char);
    EXPECTED(c3->get_class_size(), 18)
    return true;
}

bool test5(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 1; });
    c1->add_member_function("f2", []{ return 2; });
    EXPECTED(c1->get_class_size(), 1)
    return true;
}

bool test6(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 1; });
    c1->add_member_function("f2", []{ return 2; });
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_function("f2", []{ return 3; });
    EXPECTED(c2->get_class_size(), 1)
    return true;
}

bool test7(){
    auto c1=new Class;
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_function("f1", []{ return 1; });
    c1->add_member_function("f2", []{ return 2; });
    EXPECTED(c1->get_class_size(), 4*3)
    return true;
}

bool test8(){
    auto c1=new Class;
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    c1->add_member_function("f1", []{ return 1; });
    c1->add_member_function("f2", []{ return 2; });
    EXPECTED(c1->get_class_size(), 4*3)
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_object(Char);
    EXPECTED(c2->get_class_size(), 4*3+1)
    return true;
}

bool test9(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 9012; });
    c1->add_member_function("f2", []{ return 9015; });
    EXPECTED(c1->call_member_function("f1"),9012)
    EXPECTED(c1->call_member_function("f2"),9015)
    return true;
}

bool test10(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 2948; });
    c1->add_member_function("f2", []{ return 859; });
    EXPECTED(c1->call_member_function("f1"),2948)
    EXPECTED(c1->call_member_function("f2"),859)
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_function("f1", []{ return 34; });
    c2->add_member_function("f3", []{ return 847; });
    EXPECTED(c2->call_member_function("f1"),34)
    EXPECTED(c2->call_member_function("f2"),859)
    EXPECTED(c2->call_member_function("f3"),847)
    return true;
}

bool test11(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 8473; });
    c1->add_member_function("f2", []{ return 123; });
    EXPECTED(c1->call_member_function("f1"),8473)
    EXPECTED(c1->call_member_function("f2"),123)
    EXPECTED(c1->get_class_size(),1)
    return true;
}

bool test12(){
    auto c1=new Class;
    c1->add_member_function("f1", []{ return 23; });
    c1->add_member_function("f2", []{ return 1313; });
    EXPECTED(c1->call_member_function("f1"),23)
    EXPECTED(c1->call_member_function("f2"),1313)
    EXPECTED(c1->get_class_size(),1)
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_function("f1", []{ return 14; });
    c2->add_member_function("f3", []{ return 827; });
    EXPECTED(c2->call_member_function("f1"),14)
    EXPECTED(c2->call_member_function("f2"),1313)
    EXPECTED(c2->call_member_function("f3"),827)
    EXPECTED(c2->get_class_size(),1)
    return true;
}

bool test13(){
    auto c1=new Class;
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
    c1->add_member_function("f1", []{ return 8473; });
    c1->add_member_function("f2", []{ return 123; });
    EXPECTED(c1->call_member_function("f1"),8473)
    EXPECTED(c1->call_member_function("f2"),123)
    EXPECTED(c1->get_class_size(),110)
    return true;
}

bool test14(){
    auto c1=new Class;
    c1->add_member_function("f2", []{ return 123; });
    c1->add_member_object(new ClassWithFixedSize(100));
    c1->add_member_object(new ClassWithFixedSize(10));
    c1->add_member_function("f1", []{ return 8473; });
    EXPECTED(c1->call_member_function("f1"),8473)
    EXPECTED(c1->call_member_function("f2"),123)
    EXPECTED(c1->get_class_size(),110)
    auto c2=new Class;
    c2->add_member_object(new ClassWithFixedSize(1000));
    c2->add_member_object(new ClassWithFixedSize(10));
    c2->add_member_function("f3", []{ return 653; });
    c2->add_member_function("f2", []{ return 1234; });
    c2->add_inherit_class(c1);
    EXPECTED(c2->call_member_function("f1"),8473)
    EXPECTED(c2->call_member_function("f2"),1234)
    EXPECTED(c2->call_member_function("f3"),653)
    EXPECTED(c2->get_class_size(),1120)
    return true;
}

bool test15(){
    // multi -> one
    auto c1=new Class;
    c1->add_member_object(new ClassWithFixedSize(100));
    auto c2=new Class;
    c2->add_member_object(new ClassWithFixedSize(200));
    auto c3=new Class;
    c3->add_member_object(new ClassWithFixedSize(300));
    auto c4=new Class;
    c4->add_inherit_class(c1);
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    EXPECTED(c4->get_class_size(),600)
    auto c5=new Class;
    c5->add_member_object(new ClassWithFixedSize(10));
    auto c6=new Class;
    c6->add_member_object(new ClassWithFixedSize(20));
    auto c7=new Class;
    c7->add_member_object(new ClassWithFixedSize(30));
    auto c8=new Class;
    c8->add_inherit_class(c5);
    c8->add_inherit_class(c6);
    c8->add_inherit_class(c7);
    EXPECTED(c8->get_class_size(),60)
    auto c9=new Class;
    c9->add_inherit_class(c4);
    c9->add_inherit_class(c8);
    EXPECTED(c9->get_class_size(),660)
    auto c10=new Class;
    c10->add_inherit_class(c9);
    EXPECTED(c10->get_class_size(),660)
    return true;
}

bool test16(){
    auto c1=new Class;
    c1->add_member_function("f1", []{return 1;});
    auto c2=new Class;
    c2->add_member_function("f2", []{return 2;});
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_member_function("f3", []{return 3;});
    auto c4=new Class;
    c4->add_member_function("f4", []{return 4;});
    auto c5=new Class;
    c5->add_member_function("f5", []{return 5;});
    auto c6=new Class;
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_member_function("f6", []{return 6;});
    auto c7=new Class;
    c7->add_inherit_class(c3);
    c7->add_inherit_class(c6);
    c7->add_member_function("f7", []{return 77;});

    EXPECTED(c7->call_member_function("f1"),1)
    EXPECTED(c7->call_member_function("f2"),2)
    EXPECTED(c7->call_member_function("f3"),3)
    EXPECTED(c7->call_member_function("f4"),4)
    EXPECTED(c7->call_member_function("f5"),5)
    EXPECTED(c7->call_member_function("f6"),6)
    EXPECTED(c7->call_member_function("f7"),77)
    return true;
}

bool test17(){
    // diamond
    auto c1=new Class;
    c1->add_member_object(new ClassWithFixedSize(100));
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_function("f2", []{return 2;});
    c2->add_member_object(new ClassWithFixedSize(201));
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_member_function("f3", []{return 3;});
    c3->add_member_object(new ClassWithFixedSize(302));
    auto c4=new Class;
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    EXPECTED(c4->get_class_size(),100+100+201+302+4)
    EXPECTED(c4->call_member_function("f2"),2)
    EXPECTED(c4->call_member_function("f3"),3)
    return true;
}

bool test18(){
/**

#include <iostream>
#pragma pack(1)

class c1{
    int a;
    int b;
};

class c2: public c1{
public:
    char c;
    int f2(){
        return 2;
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
    auto c1=new Class;
    c1->add_member_object(Int);
    c1->add_member_object(Int);
    auto c2=new Class;
    c2->add_inherit_class(c1);
    c2->add_member_object(Char);
    c2->add_member_function("f2", []{return 2;});
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_member_object(Int);
    c3->add_member_function("f3", []{return 3;});
    auto c4=new Class;
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    c4->add_member_function("f4", []{return 4;});
    auto c5=new Class;
    c5->add_member_function("f5", []{return 5;});
    auto c6=new Class;
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_member_object(c4);
    c6->add_member_object(c5);
    EXPECTED(c1->get_class_size(),8)
    EXPECTED(c2->get_class_size(),9)
    EXPECTED(c3->get_class_size(),12)
    EXPECTED(c4->get_class_size(),25)
    EXPECTED(c5->get_class_size(),1)
    EXPECTED(c6->get_class_size(),51)
    EXPECTED(c6->call_member_function("f2"),2)
    EXPECTED(c6->call_member_function("f3"),3)
    EXPECTED(c6->call_member_function("f4"),4)
    EXPECTED(c6->call_member_function("f5"),5)
    return true;
}

bool test19(){
    auto c1=new Class;
    c1->add_virtual_member_function("f1", []{return 4857;});
    c1->add_member_function("f2", []{return 419;});
    EXPECTED(c1->get_class_size(),8)
    EXPECTED(c1->call_member_function("f1"),4857)
    EXPECTED(c1->call_member_function("f2"),419)
    return true;
}

bool test20(){
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
    auto c1=new Class;
    c1->add_virtual_member_function("f1", []{return 1;});
    auto c2=new Class;
    c2->add_virtual_member_function("f2", []{return 2;});
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_virtual_member_function("f2", []{return 3;});
    EXPECTED(c1->get_class_size(),8)
    EXPECTED(c2->get_class_size(),8)
    EXPECTED(c3->get_class_size(),16)
    EXPECTED(c1->call_member_function("f1"),1)
    EXPECTED(c2->call_member_function("f2"),2)
    EXPECTED(c3->call_member_function("f1"),1)
    EXPECTED(c3->call_member_function("f2"),3)
    return true;
}

bool test21(){
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
    auto c1=new Class;
    EXPECTED(c1->get_class_size(),1)
    auto c2=new Class;
    c2->add_virtual_inherit_class(c1);
    EXPECTED(c2->get_class_size(),8)
    return true;
}

bool test22(){
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
    auto c1=new Class;
    c1->add_member_object(new ClassWithFixedSize(100));
    EXPECTED(c1->get_class_size(),100)
    auto c2=new Class;
    c2->add_virtual_inherit_class(c1);
    c2->add_member_object(new ClassWithFixedSize(10));
    EXPECTED(c2->get_class_size(),118)
    auto c3=new Class;
    c3->add_virtual_inherit_class(c1);
    c3->add_member_object(new ClassWithFixedSize(5));
    EXPECTED(c3->get_class_size(),113)
    auto c4=new Class;
    c4->add_inherit_class(c2);
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    EXPECTED(c4->get_class_size(),135)
    return true;
}

bool test23(){
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
    auto c1=new Class;
    c1->add_virtual_member_function("f1", []{return 1;});
    EXPECTED(c1->get_class_size(),8)
    EXPECTED(c1->call_member_function("f1"),1)
    auto c2=new Class;
    c2->add_member_function("f2", []{return 2;});
    EXPECTED(c2->get_class_size(),1)
    EXPECTED(c2->call_member_function("f2"),2)
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_member_object(c1);
    c3->add_member_object(c2);
    c3->add_virtual_member_function("f2", []{return 3;});
    EXPECTED(c3->get_class_size(),17)
    EXPECTED(c3->call_member_function("f1"),1)
    EXPECTED(c3->call_member_function("f2"),3)
    return true;
}

bool test24(){
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
    if(!test23())return false;
    auto c1=new Class;
    c1->add_virtual_member_function("f1", []{return 1;});
    auto c2=new Class;
    c2->add_virtual_member_function("f2", []{return 1;});
    auto c3=new Class;
    c3->add_inherit_class(c1);
    c3->add_inherit_class(c2);
    c3->add_virtual_member_function("f3", []{return 1;});
    auto c4=new Class;
    c4->add_virtual_member_function("f4", []{return 1;});
    auto c5=new Class;
    c5->add_virtual_member_function("f5", []{return 1;});
    auto c6=new Class;
    c6->add_inherit_class(c4);
    c6->add_inherit_class(c5);
    c6->add_virtual_member_function("f6", []{return 1;});
    auto c7=new Class;
    c7->add_inherit_class(c3);
    c7->add_inherit_class(c6);
    c7->add_virtual_member_function("f7", []{return 1;});
    EXPECTED(c7->get_class_size(),32)
    return true;
}

bool test25(){
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
    auto c1=new Class; // 100
    auto c2=new Class; // 100+200
    auto c3=new Class; // 100+300
    auto c4=new Class; // 300+
    auto c5=new Class;
    auto c6=new Class;
    c6->add_inherit_class(c4);
    EXPECTED(c6->get_class_size(),1)
    c6->add_member_object(c5);
    c1->add_member_object(new ClassWithFixedSize(100));
    c2->add_virtual_inherit_class(c1);
    c4->add_inherit_class(c2);
    c2->add_member_function("f2", []{return 2;});
    c2->add_member_object(new ClassWithFixedSize(200));
    c3->add_virtual_inherit_class(c1);
    c3->add_member_object(new ClassWithFixedSize(300));
    c4->add_inherit_class(c3);
    c4->add_member_object(Int);
    c3->add_member_function("f3", []{return 3;});
    c5->add_member_function("f5", []{return 55;});
    EXPECTED(c6->get_class_size(),621)
    EXPECTED(c6->call_member_function("f2"),2)
    EXPECTED(c6->call_member_function("f3"),3)
    return true;
}

int main(){
    std::function<bool()> tests[]={
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
    int score=0;
    for(int i=0; i<25; i++){
        bool if_passed=tests[i]();
        if(if_passed)score+=5;
        std::cout<<"Test"<<i+1<<" : "<<(if_passed ? "Passed" : "Failed")<<std::endl;
    }
    score=std::min(score, 100);
    std::cout<<"Final score: "<<score<<std::endl;
}
