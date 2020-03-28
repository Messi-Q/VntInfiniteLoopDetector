#include "vntlib.h"

KEY uint8 count = 10;

constructor Fallback1() {}

// test1跨合约调用函数，数据输入错误，调用fallback, fallback函数调用test2，test2调用test1，即
// test1->fallback->test2->test1->fallback->....
CALL uint16 test(CallParams params, uint8 amount);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas

MUTABLE
uint64 test2(uint256 amount){
    test1(amount)
    uint32 res = amount + 1;
    return res;
}

MUTABLE
uint64 test1(uint256 amount){
    PrintStr("fallback", "fallback")
    uint256 res = test(param, amount)
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   test2(count);
}