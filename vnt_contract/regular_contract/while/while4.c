#include "vntlib.h"

KEY uint256 count = 0;

EVENT EVENT_GETFINALCOUNT(uint256 count);

constructor While4(){
}

MUTABLE
uint32 test1(uint256 res) {
    while(count < res) {
        count += 2;
    }
    EVENT_GETFINALCOUNT(count);
    return count
}

UNMUTABLE
uint32 getFinalCount() {
    uint256 x = 1000;
    uint256 res = U256SafeAdd(x, x);
    return test1(res);
}