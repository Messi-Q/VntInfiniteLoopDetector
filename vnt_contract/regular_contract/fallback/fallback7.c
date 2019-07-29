#include "vntlib.h"

KEY uint256 amount = 100;

typedef struct fallback7 {
    uint256 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback7() {}

MUTABLE
void test1(){
    getRes(GetSender(), amount);
}

uint256 getRes(address addr, uint32 amount) {
    accounts.key = addr;

    uint256 balance = accounts.value.balance;
    uint32 res = U256SafeAdd(balance, amount);

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
    test1();
}