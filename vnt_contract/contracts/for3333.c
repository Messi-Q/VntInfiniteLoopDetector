#include "vntlib.h"

 
KEY uint64 count;

constructor For3(){
}

MUTABLE
uint64 test1(){
    for(int32 i = 10; i < 100; i++) {
        count++;
        PrintUint256T("count:", count);
    }

    return count;
}
