#include "vntlib.h"

// 计数
KEY uint16 count = 0;

constructor For1(){
}

// i 的类型是 uint8，而这个类型变量的最大值比 2000 小。
// uint8 最大值为255
// 此时默认为uint8，所以当i循环到最大值时会出错。
// 如果改成 uint16 i 则 i <= 255 没问题
MUTABLE
uint16 test1(){
    for (uint8 i = 0; i < 2000; i++) {
        count++;
        if(count >= 2100){
            break;
        }
    }

    return count;
}
