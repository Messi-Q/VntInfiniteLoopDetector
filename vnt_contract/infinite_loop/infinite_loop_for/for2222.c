#include "vntlib.h"

// 计数
KEY uint128 count = 0;

constructor For2(){
}

MUTABLE
uint128 test1(){
    uint128 x = 0;
    for (uint32 i = 0; i < 2000; i++) {
        for(uint8 j = 0; j < 1000; j++){
            count += 2;
            if(count > 50) {
                x = count;
            }
        }
    }
    return x;
}

// 获取金额
UNMUTABLE
uint128 GetCount() {
    PrintStr("test1()", "test1()")
    return test1();
}