#include "vntlib.h"

// 计数
KEY uint256 count = 0;

constructor For2(){
}

MUTABLE
uint32 test1(){
    uint32 x = 0;
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
uint32 GetCount() {
    return test1();
}