#include "vntlib.h"

// 计数
KEY uint256 count;

constructor For1(){
}

MUTABLE
uint32 test1(){
    for (uint32 i = 0; i < 2000; i++) {
        count++;
        if(count >= 2100){
            break;
        }
    }

    return count;
}
