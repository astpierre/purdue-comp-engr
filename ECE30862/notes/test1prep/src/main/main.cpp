#include <iostream>
#include <string>
using namespace std;
/*
class Base {
public:
    void fun(int i) { cout<<"Base"<<endl; }
};
class Derived : public Base {
public:
    using Base::fun;
    void fun(char c) {  cout<<"Derived"<<endl; }
};
int main(void) {
    Derived d;
    d.fun(1);       // Prints Base
    d.fun('a');     // Prints Derived
    return 0;
}*/

/*class Complex {
private:
    int real, imag;
public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}
    Complex operator + (Complex const &obj) {
        Complex res;
        res.real = real + obj.real;
        res.imag = imag + obj.imag;
        return res;
    }
    void show() { cout << real << " + i" << imag << endl; }
};
int main(void) {
    cout<<"=========================="<<endl;
    Complex c1(1,3), c2(2,5);
    Complex c3 = c1 + c2;
    c3.show();
    cout<<"=========================="<<endl;
    return 0;
}*/

class Base {
public:
    virtual void fun(int i) { cout<<"Base fun(int i)"<<endl; }
};
class Derived : public Base {
public:
    virtual void fun(int x) {  cout<<"Derived fun(int x)"<<endl; }
};
int main(void) {
    Derived * d = new Derived;
    Base * b = new Base;
    b->fun(1); // Base fun
    d->fun(1); // Derived fun
    b = d;
    b->fun(1); // Derived fun

    //Derived * dd = new Base;    // Error
    Base * bbb = new Base;
    Base * bb = new Derived;
    bb->fun(1); // Derived fun
    bb = bbb;
    bb->fun(1); // Base fun
    return 0;
}
