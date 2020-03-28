#include "vntlib.h"

KEY string s = "fallback";

constructor Fallback2(){}

MUTABLE
uint256 test1(uint32 amount){
    uint256 res = U256SafeAdd(amount, amount);
    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   uint256 res = test1(s);
   PrintUint256T("res", res)
}

