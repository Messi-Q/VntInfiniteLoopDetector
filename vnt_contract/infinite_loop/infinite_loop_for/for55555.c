#include "vntlib.h"

// 计数
KEY uint16 count = 0;

constructor For5(){
}

MUTABLE
uint16 test1(){

    for (int32 k = -1; k = 1; k++) {
        count++;
    }

    return count;
}

void test2() {
    test1();
}
