#include "vntlib.h"

KEY uint256 res = 100;

typedef struct fallback4 {
    uint256 balance;      
    string nickName;      
} Account;

 
KEY mapping(address, Account) accounts;

constructor Fallback5() {}

uint256 getRes(address addr) {
    accounts.key = addr;

    uint256 balance = accounts.value.balance;
    while(balance >= 0) {
        res = U256_Add(balance, res);
    }

    return res;
}

MUTABLE
uint256 test1(){
    uint256 res = getRes(GetSender());
    return res;
}



 
_(){
   uint256 res = test1();
   PrintUint256T("uint256", res);
}