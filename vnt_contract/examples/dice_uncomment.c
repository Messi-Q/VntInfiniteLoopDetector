#include "vntlib.h"

typedef struct dice
{
    uint256 balance;      
    string nickName;      
    bool freeAddress;     
    uint64 winCount;      
    uint64 loseCount;     
    uint64 chickenCount;  
    uint256 winReward;    
    uint256 loseAmount;   
} Account;

KEY mapping(address, Account) accounts;

KEY uint64 totalGameCount;

KEY uint256 deposit;
 
KEY uint256 fee = U256(10);

KEY address owner;

KEY uint256 freeAmount = U256(100000000000000000000);
 
EVENT EVENT_BET(indexed address from, string nickname, uint256 amount,
                int32 bigger, uint64 lottery, uint256 reward);   
EVENT EVENT_WITHDRAW(indexed address from, string nickname, uint256 amount);   
EVENT EVENT_DEPOSIT(indexed address from, string nickname, uint256 amount);   
EVENT EVENT_NICKNAME(indexed address from, string nickName);   
EVENT EVENT_GETFREEVNT(indexed address from, bool got);   

constructor $Dice(){        
    owner = GetSender();    
    totalGameCount = 0;     
}

 
uint256 getReward(uint256 amount){
    PrintUint256T("get amount in getreward:", amount);
    PrintUint256T("get fee1:", fee);
    uint256 res = U256SafeDiv(amount, fee);
    PrintUint256T("get fee2:", res);
    uint256 reward = U256SafeSub(amount, res);
    PrintUint256T("get reward:", reward);
    return reward;
}

 
void checkAmount(uint256 amount)
{
    Require(U256_Cmp(amount, U256(0) == 1), "amount must > 0");
    address from = GetSender();
    accounts.key = from;
    uint256 balance = accounts.value.balance;
    PrintAddress("get sender:", from);
    PrintUint256T("get balance:", balance);
    Require(U256_Cmp(U256SafeSub(balance, amount), 0) != -1,
            "No enough money to bet");   
}

 
void checkPool(uint256 amount)
{
    uint256 contractBalance = GetBalanceFromAddress(GetContractAddress());
    PrintAddress("get contract address:", GetContractAddress());
    PrintUint256T("get contract balance:", contractBalance);
    PrintUint256T("get deposit balance:", deposit);
    uint256 reward = getReward(amount);   
    Require(
        U256_Cmp(U256SafeSub(contractBalance, U256SafeAdd(deposit, U256SafeMul(reward, U256(10)))),0) != -1,
        "No enough money in prize pool");
}

 
void checkOwner()
{
    address sender = GetSender();
    Require(Equal(sender, owner) == true, "Only the owner can operate");
}

uint64 random()
{
    uint64 time = GetTimestamp();
    PrintUint64T("get time", time);
    string time_sha3 = SHA3(SHA3(SHA3(FromU64(time))));
    PrintStr("get time sha3", time_sha3);
    uint64 index = time % 63 + 2;
    PrintUint64T("get index", index);
    uint64 gas = GetGas() % 64 + 2;
    PrintUint64T("get gas", gas);
    uint64 random_a = (uint64)time_sha3[index];
    PrintUint64T("get random_a", random_a);
    uint64 random_b = (uint64)time_sha3[index + 1];
    PrintUint64T("get random_b", random_b);
    uint64 random_c = random_a * random_b * gas % 101;
    PrintUint64T("get result", random_c);
    return random_c;
}

UNMUTABLE   
uint64 testRandom() {
    return random();
}

 
MUTABLE
void Bet(uint256 amount, int32 bigger)
{
    PrintUint256T("get amount:", amount);
    checkAmount(amount);
    checkPool(amount);
    address sender = GetSender();
    uint64 res = random();
    totalGameCount += 1;
    if (res > 50 && bigger == 1)
    {
        accounts.key = sender;
        uint256 reward = getReward(amount);
        accounts.value.balance = U256SafeAdd(accounts.value.balance, reward);
        accounts.value.winReward = U256SafeAdd(accounts.value.winReward, reward);   
        deposit = U256SafeAdd(deposit, reward);
        accounts.value.winCount += 1;
        EVENT_BET(sender, accounts.value.nickName, amount, bigger, res, reward);   
    }
    else if (res < 50 && bigger == -1)
    {
        accounts.key = sender;
        uint256 reward = getReward(amount);
        accounts.value.balance = U256SafeAdd(accounts.value.balance, reward);
        accounts.value.winReward = U256SafeAdd(accounts.value.winReward, reward);
        deposit = U256SafeAdd(deposit, reward);
        accounts.value.winCount += 1;
        EVENT_BET(sender, accounts.value.nickName, amount, bigger, res, reward);
    }
    else if (res == 50 && bigger == 0)
    {
        accounts.key = sender;
        uint256 reward = getReward(amount);
        reward = U256SafeMul(reward, U256(100));
        accounts.value.balance = U256SafeAdd(accounts.value.balance, reward);
        accounts.value.winReward = U256SafeAdd(accounts.value.winReward, reward);
        deposit = U256SafeAdd(deposit, reward);
        accounts.value.chickenCount += 1;
        EVENT_BET(sender, accounts.value.nickName, amount, bigger, res, reward);
    }
    else
    {
        accounts.key = sender;
        accounts.value.balance = U256SafeSub(accounts.value.balance, amount);
        accounts.value.loseAmount = U256SafeAdd(accounts.value.loseAmount, amount);
        deposit = U256SafeSub(deposit, amount);
        accounts.value.loseCount += 1;
        EVENT_BET(sender, accounts.value.nickName, amount, bigger, res, U256(0));   
    }
}

 
MUTABLE
void Withdraw(uint256 amount)
{
    checkAmount(amount);
    address from = GetSender();
    if (TransferFromContract(from, amount) == true)   
    {
        accounts.key = from;
        accounts.value.balance = U256SafeSub(accounts.value.balance, amount);
        deposit = U256SafeSub(deposit, amount);
        EVENT_WITHDRAW(from, accounts.value.nickName, amount);
    }
}

 
MUTABLE
void WithdrawAll()
{
    accounts.key = GetSender();
    uint256 amount = accounts.value.balance;
    Withdraw(amount);
}

 
MUTABLE
void WithdrawPool(uint256 amount)
{
    checkOwner();   
    checkPool(amount);   
    TransferFromContract(GetSender(), amount);
}

 
MUTABLE
void WithdrawPoolAll()
{
    uint256 amount = GetBalanceFromAddress(GetContractAddress());
    WithdrawPool(amount);
}

 
MUTABLE
void $DepositPool() {}

 
MUTABLE
void $Deposit()
{
    uint256 amount = GetValue();
    address from = GetSender();
    accounts.key = from;
    accounts.value.balance = U256SafeAdd(accounts.value.balance, amount);
    deposit = U256SafeAdd(deposit, amount);
    EVENT_DEPOSIT(from, accounts.value.balance, amount);
}

 
MUTABLE
void GetFreeChips()
{
    address from = GetSender();
    accounts.key = from;
    bool flag = accounts.value.freeAddress;
    Require(flag == false, "you have got before");
    accounts.value.balance = U256SafeAdd(accounts.value.balance, freeAmount);
    deposit = U256SafeAdd(deposit, freeAmount);
    accounts.value.freeAddress = true;
    EVENT_GETFREEVNT(from, true);
}

 
MUTABLE
void SetNickName(string name)
{
    address from = GetSender();
    accounts.key = from;
    accounts.value.nickName = name;
    EVENT_NICKNAME(from, name);
}

 
UNMUTABLE
string GetNickNameFromAddress(address addr)
{
    accounts.key = addr;
    return accounts.value.nickName;
}

 
UNMUTABLE
string GetNickName() {
    return GetNickNameFromAddress(GetSender());
}

 
UNMUTABLE
address GetOwner() {
    return owner;
}

 
UNMUTABLE
uint256 GetAmountFromAddress(address addr)
{
  accounts.key = addr;
  return accounts.value.balance;
}

 
UNMUTABLE
uint256 GetAmount() {
    return GetAmountFromAddress(GetSender());
}

 
UNMUTABLE
string GetWinAndLose()
{
    accounts.key = GetSender();
    uint64 win = accounts.value.winCount;
    uint64 lose = accounts.value.loseCount;
    uint64 chicken = accounts.value.chickenCount;
    return Concat(
        Concat(Concat(Concat(FromU64(win), "-"), FromU64(chicken)), "-"),
        FromU64(lose));
}

 
UNMUTABLE
uint256 GetPool()
{
    uint256 amount = GetBalanceFromAddress(GetContractAddress());
    return U256SafeSub(amount, deposit);
}

 
UNMUTABLE
uint64 GetTotalGameCount() {
    return totalGameCount;
}

 
$_() {
    $Deposit();
}
