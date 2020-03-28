#include "vntlib.h"

KEY uint16 count = 10;

constructor Fallback1(){}

// test1跨合约调用函数，数据输入错误，调用fallback, fallback函数调用test2，test2调用test1，即
// test1->fallback->test2->test1->fallback->....
CALL uint16 test(CallParams params, uint32 amount);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas


MUTABLE
uint16 test1(uint16 amount){
    test(param, amount)
    return amount;
}

MUTABLE
uint16 test2(uint8 amount){
    test1(amount)
    uint16 res = amount + 1;
    return res;
}

MUTABLE
void test3(){
    string s = "Input data error";
    PrintStr("ERROR:", s);
}

// fallback函数，输入数据出错，自动执行
_(){
   test3();
}