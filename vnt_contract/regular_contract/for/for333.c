#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For3(){
}

MUTABLE
uint256 test1(){
    PrintStr("uint256", "For");

    for(int32 i = 10; i < 100; i++) {
        count++;
        PrintUint256T("count:", count);
    }

    return count;
}
