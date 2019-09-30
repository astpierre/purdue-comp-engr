// This is the main class for HW3
#include "src/lib/Base.h"
#include "src/lib/D1.h"
#include "src/lib/D1a.h"
#include "src/lib/D2.h"
#include <iostream>

int main(int argc, char **argv) {
    Base *bP = new Base( );
    D1 *d1P = new D1( );
    D1a *d1aP = new D1a( );
    D2 *d2P = new D2( );
    Base bV;
    D1 d1V;
    D1a d1aV;
    D2 d2V;


    std::cout << "Q1 --> Q5" << std::endl;
    bV.f1( ); // Q1
    bV.f3( ); // Q2
    bV.f4( ); // Q3
    bV.f5( ); // Q4
    std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl; // Q5

    std::cout << "Q6 --> Q10" << std::endl;
    d1P->f1( ); // Q6
    d1P->f3( ); // Q7
    d1P->f4( ); // Q8
    d1P->f5( ); // Q9
    std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl; // Q10

    std::cout << "Q11 --> Q15" << std::endl;
    d1V.f1( ); // Q11
    d1V.f3( ); // Q12
    d1V.f4( ); // Q13
    d1V.f5( ); // Q14
    std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl; // Q15

    std::cout << "Q16 --> Q21" << std::endl;
    d1aP->f1( ); // Q16
    std::cout << "Q17: E\n";//d1aP->f2( ); // Q17
    d1aP->f3( ); // Q18
    d1aP->f4( ); // Q19
    std::cout << "Q20: E\n";//d1aP->f5( ); // Q20
    std::cout << "Q21: E\n";//std::cout << d1aP->i << ", " << d1aP->j << ", " << d1aP->k << std::endl; // Q21

    std::cout << "Q22 --> Q27" << std::endl;
    d1aV.f1( ); // Q22
    std::cout << "Q23: E\n";//d1aV.f2( ); // Q23
    d1aV.f3( ); // Q24
    d1aV.f4( ); // Q25
    std::cout << "Q26: E\n";//d1aV.f5( ); // Q26
    std::cout << "Q27: E\n";//std::cout << d1aV.i << ", " << d1aV.j << ", " << d1aV.k << std::endl; // Q27

    std::cout << "Q28 --> Q32" << std::endl;
    d2P->f1( ); // Q28
    d2P->f3( ); // Q29
    d2P->f4( ); // Q30
    d2P->f5( ); // Q31
    std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl; // Q32

    std::cout << "Q33 --> Q37" << std::endl;
    d2V.f1( ); // Q33
    d2V.f3( ); // Q34
    d2V.f4( ); // Q35
    d2V.f5( ); // Q36
    std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q37

    bP = d2P;
    d1P = d2P;
    bV = d2V;

    std::cout << "Q38 --> Q42" << std::endl;
    bP->f1( ); // Q38
    bP->f2( ); // Q39
    bP->f3( ); // Q40
    bP->f4( ); // Q41
    bP->f5( ); // Q42

    std::cout << "Q43 --> Q48" << std::endl;
    bV.f1( ); // Q43
    bV.f2( ); // Q44
    bV.f3( ); // Q45
    bV.f4( ); // Q46
    bV.f5( ); // Q47
    std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl; // Q48

    std::cout << "Q49 --> Q54" << std::endl;
    d1P->f1( ); // Q49
    d1P->f2( ); // Q50
    d1P->f3( ); // Q51
    d1P->f4( ); // Q52
    d1P->f5( ); // Q53
    std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl; // Q54

    std::cout << "Q55 --> Q60" << std::endl;
    d1V.f1( ); // Q55
    d1V.f2( ); // Q56
    d1V.f3( ); // Q57
    d1V.f4( ); // Q58
    d1V.f5( ); // Q59
    std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl; // Q60

    std::cout << "Q61 --> Q66" << std::endl;
    d2P->f1( ); // Q61
    d2P->f2( ); // Q62
    d2P->f3( ); // Q63
    d2P->f4( ); // Q64
    d2P->f5( ); // Q65
    std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl; // Q66

    std::cout << "Q67 --> Q72" << std::endl;
    d2V.f1( ); // Q67
    d2V.f2( ); // Q68
    d2V.f3( ); // Q69
    d2V.f4( ); // Q70
    d2V.f5( ); // Q71
    std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q72

    std::cout << "Q73 --> Q76" << std::endl;
    std::cout << "Q73: E\n";//bP = d1aP; // Q73
    std::cout << "Q74: E\n";//bV = d1aV; // Q74
    std::cout << "Q75: E\n";//d1P = d1aP; // Q75
    std::cout << "Q76: E\n";//d1V = d1aV; // Q76
}
