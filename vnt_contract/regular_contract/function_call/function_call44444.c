#include "vntlib.h"

constructor Test1(){}

// test1.c 调用test2.c
CALL uint16 test2(CallParams params);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas


MUTABLE
uint16 test1(){
    uint16 res = test2(params);
    PrintUint16T("res:", res);
    return res;
}

#include "vntlib.h"

// contract test1, 用于被调用
constructor Test2(){}

MUTABLE
void test2() {
    uint16 a = 20;
    uint16 i = U256SafeMul(a, a)
    while(i > a) {
        a++;
    }
}
