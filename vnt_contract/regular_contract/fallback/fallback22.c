#include "vntlib.h"

KEY string s = "Fallback";

constructor Fallback2(){}

MUTABLE
uint64 test1(){
    PrintStr("Fallback", "Fallback")
    uint32 amount = 100;
    uint32 res = U256SafeAdd(amount, amount);
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   PrintStr("count:", s);
}

