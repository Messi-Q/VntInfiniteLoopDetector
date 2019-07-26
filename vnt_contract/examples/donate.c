#include "vntlib.h"

// 账户地址
KEY mapping(address, uint) account;

constructor $Donate(){}

// 任何人可以向指定地址捐献以太币，受捐赠人可以提走自己受捐赠的币。
MUTABLE    // MUTABLE会修改状态变量
void $donate(){
    uint256 amount = GetValue();
    address to = GetSender();
    account.key = to;
    account.value = U256SafeAdd(account.value, amount);
}

// 根据合约地址获取金额
UNMUTABLE
uint256 GetAmountFromAddress(address addr){
  account.key = addr;
  return account.value;
}

UNMUTABLE  // UNMUTABLE不会修改状态变量, 根据合约地址获取金额
uint256 queryAmount(address to) {
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
