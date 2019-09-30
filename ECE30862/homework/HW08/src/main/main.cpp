#include "src/lib/Set.h"
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    /* Create and test sets */
    Set a = Set(63);
    a=a+4;
    a=a+8;
    a.printSet(); // Need to overload << op
    //cout << "a w/4, 8: " << a << endl;

    //a = a + 4;
    //a = a + 8;
    //cout << "a w/4, 8: " << a << endl; // a w/4, 8: 4, 8

    Set b = Set(63);
    b=b+8;
    b=b+16;
    b.printSet();

    Set c = a&b;
    c.printSet();

    //Set d = a/b;
    //d.printSet();

    //cout << "b w/8, 16: " << b << endl; // b w/8, 16: 8, 16

    a = a / b;
    a.printSet();
    //cout << "a / b: " << a << endl; // a / b: 4

    a = a + 12;
    a = a + 16;
    a = a - 12;
    a = a - 7;
    a.printSet();
    //cout << "a w/4, 16: " << a << endl; // a w/4, 16: 4, 16

    a = ~a;
    a.printSet();

    //cout << "~a: " << ~a << endl; // ~a: 0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
    //cout << "a copy count: " << a.getCopyCount( ) << endl; // a copy count: 12
    //cout << "b copy count: " << b.getCopyCount( ) << endl; // b copy count: 12

    return 0;
}
