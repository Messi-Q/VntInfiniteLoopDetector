#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For6(){
}

MUTABLE
uint256 test1(){
    for (; ;) {
        count++;
    }

    return count;
}
