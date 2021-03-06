#include "vntlib.h"

KEY uint128 res = 100;

typedef struct fallback4 {
    uint128 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback5{}

uint128 getRes(address addr) {
    accounts.key = addr;

    uint128 balance = accounts.value.balance;
    Require(balance > 0, "balance > 0");

    while(balance > 0) {
        res += balance;
    }

    return res;
}

MUTABLE
void test1(){
    uint128 res = getRes(GetSender());
    PrintUint128T("uint256", res);
}


// fallback函数，输入数据出错，自动执行
_(){
   test1();
}