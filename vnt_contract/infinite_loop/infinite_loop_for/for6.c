#include "vntlib.h"

// 计数
KEY uint256 count = 0;

constructor For6(){
}

MUTABLE
uint32 test1(){
    for (; ;) {
        count++;
    }

    return count;
}
