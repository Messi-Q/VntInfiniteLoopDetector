#include "vntlib.h"

KEY address newOwner;
KEY address owner;
KEY uint256 MinDeposit
KEY mapping (address, uint) holders;

constructor $Fallback3(){       // Payable 函数可以接收来自交易中的原生代币，使用符号$表示
    owner = GetSender();   // owner 即交易发起者的地址
}

void initTokenBank() {
    owner = GetSender();
    MinDeposit = 1;
}

//存款
MUTABLE
void $Deposit() {
    if (GetValue() > MinDeposit) {
        holders.key = GetSender();
        holders.value += GetValue();
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