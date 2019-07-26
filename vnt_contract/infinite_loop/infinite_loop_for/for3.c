#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For3(){
}

MUTABLE
uint32 test1(){

    for(int32 i = 10; i < 100; i--) {
        count++;
        PrintUint256T("count:", count);
    }

    return count;
}
