#include "vntlib.h"

KEY uint16 count = 0;
KEY string ss = "qian";

constructor While3(){
}

// 若isDone返回true，将导致死循环
MUTABLE
uint16 test1(string s){
    isDone = Equal(s, ss);
    uint16 res = test2(isDone)
    return res;
}

MUTABLE
uint16 test2(bool isDone){
     while(count < 3) {
        if(isDone) {
            count++;
            continue;
        }
        count++;
     }
     return count;
}
