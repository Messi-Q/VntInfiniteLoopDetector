#include "vntlib.h"

KEY uint128 amount = 100;

typedef struct fallback7 {
    uint128 balance;     // 存款
    string nickName;     // 昵称
} Account;

// 账号余额
KEY mapping(address, Account) accounts;

constructor Fallback7() {}

MUTABLE
void test1(){
    PrintStr("getRes", "getRes");
    getRes(GetSender(), amount);
}

uint128 getRes(address addr, uint128 amount) {
    accounts.key = addr;
    uint128 balance = accounts.value.balance;
    uint128 res = U256SafeAdd(balance, amount);

    return res;
}

// fallback函数，输入数据出错，自动执行
_(){
   while(true){
      test1();
   }
}