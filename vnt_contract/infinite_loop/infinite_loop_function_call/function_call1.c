#include "vntlib.h"

constructor Function1(){}

MUTABLE
uint64 test1(uint256 amount){
    v = a;
    c = test2(a, v)
    return c;
}

MUTABLE
uint64 test2(uint256 b, uint256 c){
    uint256 e = U256SafeAdd(b, c);
    uint256 res = test3(e);
    return res;
}


MUTABLE
uint64 test3(uint256 a){
    uint256 res = test1(a);
    return res;
}

