#include "vntlib.h"

constructor Fallback4() {}

MUTABLE
uint32 test1(uint256 amount){
    uint256 count = 0

    for(uint8 i = 0; i< amount; i++) {
        count += i;
    }

    return count;
}

// fallback函数，输入数据出错，自动执行
_(){
   test1(count);
}