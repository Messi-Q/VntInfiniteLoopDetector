#include "vntlib.h"

// 计数
KEY uint256 count = 0;

constructor For1(){}

MUTABLE
uint256 test1(){
    PrintStr("uint256", "uint256")

    for (uint8 i = 0; i < 2000; i++) {
        count++;
        if(count >= 2100){
            break;
        }
    }

    return count;
}
