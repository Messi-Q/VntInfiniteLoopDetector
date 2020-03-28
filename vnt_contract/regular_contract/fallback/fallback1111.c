#include "vntlib.h"

KEY uint8 count = 10;

constructor Fallback1(){

}

// test1跨合约调用函数，数据输入错误，调用fallback, fallback函数调用test2，test2调用test1，即
// test1->fallback->test2->test1->fallback->....
CALL uint128 test(CallParams params, uint32 amount);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas


MUTABLE
uint128 test1(uint8 amount){
    test(param, amount)
    return amount;
}

MUTABLE
uint128 test2(uint8 amount){
    test1(amount)
    uint128 res = amount + 1;
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   string s = "Input data error";
   PrintStr("ERROR:", s);
}