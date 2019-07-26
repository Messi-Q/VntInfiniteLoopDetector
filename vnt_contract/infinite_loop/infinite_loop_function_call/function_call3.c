#include "vntlib.h"

KEY uint256 v;

constructor Test1(){}

MUTABLE
uint32 test1(uint256 amount){
    v = amount;
    c = test1(v)
    return c;
}




