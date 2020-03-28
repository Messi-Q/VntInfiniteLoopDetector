#include "vntlib.h"

KEY uint16 res = 100;

typedef struct fallback4 {
    uint16 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback5() {}

MUTABLE
void test1(){
    uint16 res = getRes(GetSender());
    PrintUint16T("uint256", res);
}

uint16 getRes(address addr) {
    accounts.key = addr;

    uint16 balance = accounts.value.balance;
    while(balance >= 0) {
        res += balance;
    }

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   test1();
}