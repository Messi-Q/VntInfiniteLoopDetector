#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For5(){
}

MUTABLE
uint32 test1(){

    for (k = -1; k == 1; k++) {
        count++;
    }

    return count;
}

void test2() {
    test1();
}
