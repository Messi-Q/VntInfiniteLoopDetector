#include "vntlib.h"

// 计数
KEY uint128 count = 0;

constructor For8(){
}

MUTABLE
uint128 test(){
    PrintStr("double for","double for")

    for (uint128 i = 100; i > 0; i--) {
        for (uint128 j = i; j > 50; j++) {
            if (j > 100) {
                count = j;
                PrintUint128T("remark", j)
            }
        }
    }

    return count;
}
