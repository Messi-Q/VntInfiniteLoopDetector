#include "vntlib.h"

// 账号余额
KEY mapping(address, uint) account;

KEY address owner;

EVENT Deposit(address indexed from, int32 id, uint256 value, uint256 balance);

constructor Fallback3(){
    owner = GetSender();   // owner即交易发起者的地址
}

//存款
MUTABLE
uint128 $deposit(int128 id) {
    uint128 amount = GetValue();
    address from = GetSender();
    account.key = from;
    account.value = U256SafeAdd(accounts.value, amount);
    deposit = U256SafeAdd(deposit, amount);
    Deposit(GetSender(), id, GetValue(), account.value);
    return account.value;
}

string perform() {
    string UUID = "1234-5678-9101";
    $deposit(UUID);
    return UUID;
}

// fallback函数，输入数据出错时，自动执行存款操作
// 若数据一直出错，将一直执行存款操作
$_() {
    string s = perform();
    PrintStr("s",  s)
}


