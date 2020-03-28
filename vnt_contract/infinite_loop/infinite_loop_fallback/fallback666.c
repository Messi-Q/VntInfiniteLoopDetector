#include "vntlib.h"

KEY uint64 amount = 100;

typedef struct fallback4 {
    uint256 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback6() {}

MUTABLE
void test1(){
    getRes(GetSender(), amount);
}

uint64 getRes(address addr, uint32 amount) {
    accounts.key = addr;

    uint256 balance = accounts.value.balance;
    uint64 res = U256SafeAdd(balance, amount);

    return res;
}

uint64 test2(){
    Require(accounts.value.balance > 0, "balance > 0");
    uint64 res = accounts.value.balance;
    while (res > 0) {
        test1();
    }

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   uint64 res = test2();
   PrintUint64T("res", res);
}