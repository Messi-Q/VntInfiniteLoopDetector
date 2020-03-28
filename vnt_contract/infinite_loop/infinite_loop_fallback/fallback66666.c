#include "vntlib.h"

KEY uint16 amount = 100;

typedef struct fallback4 {
    uint16 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback6() {}

MUTABLE
void test1(){
    getRes(GetSender(), amount);
}

uint16 getRes(address addr, uint16 amount) {
    accounts.key = addr;

    uint16 balance = accounts.value.balance;
    uint16 res = U256SafeAdd(balance, amount);

    return res;
}

uint16 test2(){
    Require(accounts.value.balance > 0, "balance > 0");
    uint16 res = accounts.value.balance;
    while (res > 0) {
        test1();
    }

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   test2();
}