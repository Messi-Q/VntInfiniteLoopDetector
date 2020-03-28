#include "vntlib.h"

KEY string s = "fallback";

constructor Fallback2(){}

MUTABLE
uint16 test1(){
    uint16 amount = 100;
    uint16 res = U256SafeAdd(amount, amount);
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   PrintStr("count:", s);
}

