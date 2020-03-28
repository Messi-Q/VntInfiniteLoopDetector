#include "vntlib.h"

KEY uint128 amount = 100;

typedef struct fallback4 {
    uint128 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback6() {}

MUTABLE
void test1(){
    getRes(GetSender(), amount);
}

uint128 getRes(address addr, uint32 amount) {
    accounts.key = addr;

    uint128 balance = accounts.value.balance;
    uint128 res = U256SafeAdd(balance, amount);

    return res;
}

uint128 test2(){
    Require(accounts.value.balance > 0, "balance > 0");
    uint32 res = accounts.value.balance;
    if (res > 0) {
        test1();
    }

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   test2();
}