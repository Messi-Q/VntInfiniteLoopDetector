#include "vntlib.h"

KEY uint256 count = U256(1000000000);

constructor Fallback1() {

}
// test1跨合约调用函数，数据输入错误，调用fallback, fallback函数调用test2，test2调用test1，即
// test1->fallback->test2->test1->fallback->....
CALL uint32 test(CallParams params, uint32 amount);
CallParams params = {Address("0xaaaa"), U256(10000), 100000};  // 包含 address,vnt,gas

MUTABLE
uint256 test1(uint8 amount){
    PrintStr("fallback", "fallback")
    test(param, amount)
    return amount;
}

MUTABLE
uint256 test2(uint8 amount){
    test1(amount)
    uint256 res = amount + 1;
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   test2(count);
}