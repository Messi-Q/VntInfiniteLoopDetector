#include "vntlib.h"

KEY uint256 count = 0;
KEY string s1 = "qian";

constructor While3(){
}

// 若isDone返回true，将导致死循环
MUTABLE
uint32 test1(string s){
    isDone = Equal(s, s1);
    uint32 res = test2(isDone)
    return res;
}

MUTABLE
uint32 test2(bool isDone){
     while(count < 3) {
        if(isDone) {
            continue;
        }
        count++;
     }
     return count;
}
