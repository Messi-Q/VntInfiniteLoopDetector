#include "vntlib.h"

KEY uint256 count = 1000;

constructor Fallback4() {}

MUTABLE
void test1(uint256 amount){
    PrintStr("For and Fallback", "For and Fallback")

    for(uint32 i = 0; i < amount; i++) {
        count += i;
    }

}

// fallback函数，输入数据出错，自动执行
_(){
   test1(count);
}