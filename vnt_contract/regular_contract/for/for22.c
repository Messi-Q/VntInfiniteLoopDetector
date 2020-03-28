#include "vntlib.h"

// 计数
KEY uint256 count = 0;

constructor For2(){}

// i 的类型是 uint8，而这个类型变量的最大值比 2000 小。
// uint8 最大值为255
// 此时默认为uint8，所以当i循环到最大值时会出错。
// 如果改成 uint32 i 则 i <= 255 没问题
MUTABLE
uint64 test1(){
    for (uint32 i = 0; i < 2000; i++) {
        count++;
        if(count >= 2100){
            break;
        }
    }
    return count;
}

// 获取金额
UNMUTABLE
uint64 GetCount() {
    PrintStr("uint256:", "count < 1000");
    return test1();
}