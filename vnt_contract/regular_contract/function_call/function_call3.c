#include "vntlib.h"

KEY uint256 v;

KEY mapping(address, uint) account;

constructor Test1(){}

MUTABLE
uint32 test1(uint256 amount){
    v = amount;
    address to = GetSender();
    account.key = to;
    account.value = U256SafeAdd(account.value, amount);
    return account.value;
}



