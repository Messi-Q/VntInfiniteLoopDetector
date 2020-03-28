#include "vntlib.h"

KEY uint128 count = 0;

constructor Fallback4() {}

MUTABLE
void test1(uint128 amount){

    for(uint32 i = 1; i< amount; i++) {
        count += i;
    }

}

// fallback函数，输入数据出错，自动执行
_(){
    PrintStr("fallback", "fallback");
    test1(count);
}