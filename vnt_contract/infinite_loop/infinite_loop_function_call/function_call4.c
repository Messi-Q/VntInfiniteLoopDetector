#include "vntlib.h"

constructor Test1(){}

// test1.c 调用test2.c
CALL uint32 test2(CallParams params);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas


MUTABLE
void test1(){
    uint32 res = test2(params);
}

#include "vntlib.h"

// contract test1, 用于被调用
constructor Test2(){}

MUTABLE
void test2() {
    uint256 a = 20;
    PrintUint256T("a:", a);
    uint256 i = U256SafeMul(a, a)
    while(i > a) {
        i++;
    }
}
