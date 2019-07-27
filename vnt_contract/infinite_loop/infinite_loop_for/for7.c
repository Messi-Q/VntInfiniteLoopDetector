#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For7(){
}

MUTABLE
uint32 test1(){
    for (uint32 i = 1000; i > 0; i++) {
        count++;
    }

    return count;
}
