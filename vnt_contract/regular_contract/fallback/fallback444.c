#include "vntlib.h"

KEY uint256 count = 0

constructor Fallback4() {}

MUTABLE
uint256 test1(uint256 amount){
    PrintStr("count", "count");

    for(uint32 i = 0; i< amount; i++) {
        count += i;
    }

    return count;
}

// fallback函数，输入数据出错，自动执行
_(){
   uint256 res = test1(count);
   PrintUint256T("res", res);
}