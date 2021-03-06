#include "vntlib.h"

KEY uint256 count = 0;
KEY string ss = "qian";

constructor While3(){}

// 若isDone返回true，将导致死循环
MUTABLE
uint256 test1(string s){
    isDone = Equal(s, ss);
    uint32 res = test2(isDone)
    return res;
}

MUTABLE
uint256 test2(bool isDone){
    PrintStr("test", "test");

    while(count < 3) {
        if(isDone) {
            count++;
            continue;
        }
        count++;
    }
    return count;
}
