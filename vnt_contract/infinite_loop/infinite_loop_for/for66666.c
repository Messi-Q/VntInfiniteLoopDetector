#include "vntlib.h"

// 计数
KEY uint16 count = 0;

constructor For6(){
}

MUTABLE
uint16 test1(){
    for (; ;) {
        count++;
    }

    return count;
}
