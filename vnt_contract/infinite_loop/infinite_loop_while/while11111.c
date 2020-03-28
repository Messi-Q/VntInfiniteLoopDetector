#include "vntlib.h"

KEY uint16 count = 0;

constructor While1(){

}

MUTABLE
uint16 test1(uint16 x){
    // (1)
    while(1 == 1) {
        count = x;
    }

    // (2)
    while(true) {
        count = x;
    }

    return count;
}
