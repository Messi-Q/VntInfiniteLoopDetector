#include "vntlib.h"

KEY uint64 res = 100;

typedef struct fallback4 {
    uint64 balance;      
    string nickName;      
} Account;

 
KEY mapping(address, Account) accounts;

constructor Fallback5 () {}

uint64 getRes(address addr) {
    accounts.key = addr;

    uint64 balance = accounts.value.balance;
    Require(balance > 0, "balance > 0");

    while(balance > 0) {
        res =  U256_Add(res, balance);
    }

    return res;
}

MUTABLE
void test1(){
    uint256 res = getRes(GetSender());
    PrintUint256T("uint256", res);
}


 
_(){
   PrintStr("fallback", "fallback");
   test1();
}