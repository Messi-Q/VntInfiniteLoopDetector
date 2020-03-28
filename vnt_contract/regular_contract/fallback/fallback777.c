#include "vntlib.h"

KEY uint64 amount = 100;

typedef struct fallback7 {
    uint64 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback7() {}

MUTABLE
void test1(){
    PrintStr("getRes()", "getRes()");
    getRes(GetSender(), amount);
}

uint64 getRes(address addr, uint32 amount) {
    accounts.key = addr;

    uint64 balance = accounts.value.balance;
    uint64 res = U256SafeAdd(balance, amount);

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
    PrintStr("fallback", "fallback");
    test1();
}