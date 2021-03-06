#include "vntlib.h"

KEY address newOwner;

KEY address owner;

KEY uint256 MinDeposit;

KEY mapping (address, uint) holders;

constructor $Fallback3(){       // Payable 函数可以接收来自交易中的原生代币，使用符号$表示
    owner = GetSender();   // owner 即交易发起者的地址
}

void changOwner(address addr) {
    newOwner = addr;
}

void confirmOwner() {
    if (GetSender() == newOwner) {
        owner = newOwner;
    }
}

uint256 initTokenBank() {
    owner = GetSender();
    MinDeposit = 1;
    return MinDeposit;
}

//存款
MUTABLE
uint256 $Deposit() {
    if (GetValue() > MinDeposit) {
        holders.key = GetSender();
        holders.value += GetValue();
    }

    return GetValue();
}

void WithdrawTokenToHolder(address _to, uint _amount) {
    holders.key = to;
    PrintStr("WithdrawTokenToHolder", "WithdrawTokenToHolder");
    if(holders.value > 0) {
        holders.value = 0;
        SendFromContract(to, amount);
    }
}

void WithdrawToHolder(address _addr, uint _amount) {
    holders.key = addr
    if(holders.value > 0) {
        if(TransferFromContract(_addr, _amount) == true){
            Holders.value -= _amount;
        }
    }
}

$_() {
    $Deposit();
}