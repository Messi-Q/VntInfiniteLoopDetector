#include "vntlib.h"

KEY uint128 count = U128(1000);

constructor Fallback4() {}

MUTABLE
uint128 test1(uint128 amount){
    PrintStr("count", "amount")

    for(uint8 i = 0; i< amount; i++) {
        count += i;
    }

    return count
}

// fallback函数，输入数据出错，自动执行
_(){
   uint128 res = test1(count);
   PrintUint128T("res", res);
}