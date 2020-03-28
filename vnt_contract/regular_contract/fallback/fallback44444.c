#include "vntlib.h"

KEY uint16 count = 0

constructor Fallback4() {}

MUTABLE
uint16 test1(uint256 amount){

    for(uint32 i = 0; i< amount; i++) {
        count += i;
    }

}

// fallback函数，输入数据出错，自动执行
_(){
   uint16 res = test1(count);
   PrintInt16T("res", res);
}