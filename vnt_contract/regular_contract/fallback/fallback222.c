#include "vntlib.h"

KEY string s = "fallback";

constructor Fallback2(){}

MUTABLE
uint256 test1(){
    uint256 amount = 100;
    uint256 res = U256SafeAdd(amount, amount);
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   PrintStr("count:", s);
}

