#include "vntlib.h"

KEY uint128 res = 100;

typedef struct fallback4 {
    uint128 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback5() {}

uint128 getRes(address addr) {
    accounts.key = addr;

    uint128 balance = accounts.value.balance;
    while(balance >= 0) {
        res += balance;
    }

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   getRes(GetSender());
}