#include "vntlib.h"

 
KEY uint32 count = 0;

constructor For5(){
}

MUTABLE
uint32 test1(){

    for (uint32 k = -1; k == 1; k++) {
        count++;
    }

    return count;
}

void test2() {
    test1();
}
