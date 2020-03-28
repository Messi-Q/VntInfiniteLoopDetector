#include "vntlib.h"

// 计数
KEY uint128 count;

constructor For5(){
}

MUTABLE
uint128 test1(){
    PrintStr("uint128", "uint128");

    for (int32 k = -1; k = 1; k++) {
        count++;
    }

    return count;
}

uint128 test2() {
    return test1();
}
