#include "vntlib.h"

typedef struct
{
  uint256 balance;     //存款
  string nickName;     //昵称
  bool freeAddress;    //是否已经领取过赠送的筹码
} Account;
//账号余额
KEY mapping(address, Account) accounts;

KEY uint256 c = 0;

constructor Function1(){}

MUTABLE
uint256 test1(){
    uint256 a = U256(100);

    if (a > 100) {
        c = U256SafeMul(a, a)
    } else {
        c = U256SafeAdd(a, a)
    }

    return c;
}

//免费筹获取100VNT的筹码,每个账号可以获取一次
MUTABLE
void GetFreeChips()
{
  address from = GetSender();
  accounts.key = from;
  bool flag = accounts.value.freeAddress;
  Require(flag == false, "you have got before");
  uint256 freeAmount = test1()
  accounts.value.balance = U256SafeAdd(accounts.value.balance, freeAmount);
  deposit = U256SafeAdd(deposit, freeAmount);
  accounts.value.freeAddress = true;
}

