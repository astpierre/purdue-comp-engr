// compile this and the other .cpp files and run them, and it will generate
// the answers in answers.txt

#include "Base.h"
#include "D1.h"
#include "D1a.h"
#include "D2.h"
#include <iostream>

void q(int qn) {
   std::cout << std::endl << "Q" << qn << ": ";
}

void q(std::string qs) {
   std::cout << std::endl << qs;
}

int main(int argc, char **argv) {

   Base *bP = new Base( );
   D1 *d1P = new D1( );
   D1a *d1aP = new D1a( );
   D2 *d2P = new D2( );
   Base bV;
   D1 d1V;
   D1a d1aV;
   D2 d2V;

//   bP->f1( );
//   bP->f2( );
//   bP->f3( );
//   bP->f4( );
//   bP->f5( );
//   st
q(1); bV.f1( ); // Q1
// bV.f2( );
q(2); bV.f3( ); // Q2
q(3); bV.f4( ); // Q3
q(4); bV.f5( ); // Q4
q(5); std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl; // Q5

q(6); d1P->f1( ); // Q6
// d1P->f2( );
q(7); d1P->f3( ); // Q7
q(8); d1P->f4( ); // Q8
q(9); d1P->f5( ); // Q9
q(10); std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl; // Q10

q(11); d1V.f1( ); // Q11
// d1V.f2( ); 
q(12); d1V.f3( ); // Q12
q(13); d1V.f4( ); // Q13
q(14); d1V.f5( ); // Q14
q(15); std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl; // Q15

q(16); d1aP->f1( ); // Q16
q("Q17: ERR"); // ERROR d1aP->f2( ); // Q17
q(18); d1aP->f3( ); // Q18
q(19); d1aP->f4( ); // Q19
q("Q20: ERR"); // ERROR d1aP->f5( ); // Q20
q("Q21: ERR"); // ERROR std::cout << d1aP->i << ", " << d1aP->j << ", " << d1aP->k << std::endl; // Q21

q(22); d1aV.f1( ); // Q22
q("Q23: ERR"); // ERROR d1aV.f2( ); // Q23
q(24); d1aV.f3( ); // Q24
q(25); d1aV.f4( ); // Q25
q("Q26: ERR"); // ERROR d1aV.f5( ); // Q26
q("Q27: ERR"); // ERROR std::cout << d1aV.i << ", " << d1aV.j << ", " << d1aV.k << std::endl; // Q27

q(28); d2P->f1( ); // Q28
// d2P->f2( ); 
q(29); d2P->f3( ); // Q29
q(30); d2P->f4( ); // Q30
q(31); d2P->f5( ); // Q31
q(32); std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl; // Q32

q(33); d2V.f1( ); // Q33
// d2V.f2( );
q(34); d2V.f3( ); // Q34
q(35); d2V.f4( ); // Q35
q(36); d2V.f5( ); // Q36
q(37); std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q37

bP = d2P; 
d1P = d2P; 
bV = d2V; 

q(38); bP->f1( ); // Q38
q(39); bP->f2( ); // Q39
q(40); bP->f3( ); // Q40
q(41); bP->f4( ); // Q41
q(42); bP->f5( ); // Q42

q(43); bV.f1( ); // Q43
q(44); bV.f2( ); // Q44
q(45); bV.f3( ); // Q45
q(46); bV.f4( ); // Q46
q(47); bV.f5( ); // Q47
q(40); std::cout << bV.i << ", " << bV.j << ", " << bV.k << std::endl; // Q48

q(49); d1P->f1( ); // Q49
q(50); d1P->f2( ); // Q50
q(51); d1P->f3( ); // Q51
q(52); d1P->f4( ); // Q52
q(53); d1P->f5( ); // Q53
q(54); std::cout << d1P->i << ", " << d1P->j << ", " << d1P->k << std::endl; // Q54

q(55); d1V.f1( ); // Q55
q(56); d1V.f2( ); // Q56
q(57); d1V.f3( ); // Q57
q(58); d1V.f4( ); // Q58
q(59); d1V.f5( ); // Q59
q(60); std::cout << d1V.i << ", " << d1V.j << ", " << d1V.k << std::endl; // Q60

q(61); d2P->f1( ); // Q61
q(62); d2P->f2( ); // Q62
q(63); d2P->f3( ); // Q63
q(64); d2P->f4( ); // Q64
q(65); d2P->f5( ); // Q65
q(66); std::cout << d2P->i << ", " << d2P->j << ", " << d2P->k << std::endl; // Q66

q(67); d2V.f1( ); // Q67
q(68); d2V.f2( ); // Q68
q(69); d2V.f3( ); // Q69
q(70); d2V.f4( ); // Q70
q(71); d2V.f5( ); // Q71
q(72); std::cout << d2V.i << ", " << d2V.j << ", " << d2V.k << std::endl; // Q72

q("Q73: ERR"); // ERROR bP = d1aP; // Q73
q("Q74: ERR"); // ERROR bV = d1aV; // Q74
q("Q75: ERR"); // ERROR d1P = d1aP; // Q75
q("Q76: ERR"); // ERROR d1V = d1aV; // Q76

std::cout << std::endl;
}

