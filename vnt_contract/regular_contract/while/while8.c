#include "vntlib.h"

typedef struct voter
{
    uint64 weight;     // 投票者拥有的投票权重
    bool voted;    // 投票者是否已经投票，若为true则已经投票
    uint64 vote;     // 投票者所投的提案
    address delegate;  // 投票者指定的代理
} Voter;

KEY Voter sender;

typedef struct proposal
{
    string name;// 提案简称
    uint64 voteCount;// 提案的投票数统计
} Proposal;

//
KEY address chairperson;

// 这里声明了一个mapping，存储了每一个Voter的address
KEY mapping(address, Voter) voters;

// 一个用来存储提案的数组(提案数量最大为100)
KEY array(Proposal) proposals;

// 构造函数，初始化投票系统，初始化提案
constructor vote(array(string) proposalNames){
    chairperson = GetSender();
    voters.key = chairperson;
    voters.value.weight = 1;
    proposalNames.length = 32;

    // 为每一个提案名称创建一个提案对象，并存储到数组里
    for(uint64 i = 0; i < proposalNames.length; i++) {
        // 每一个提案对象包含提案名称和被投票数（初始化每个提案的被投票数都为0）
        proposalNames.index = i;
        proposalNames.value = "proposalName" + FromU64(i);

        proposals.length = 100;
        proposals.index = i;
        proposals.value.name = proposalNames.value;
        proposals.value.voteCount = 0;
    }

}

// 给系统里的voter分配投票权，只有chairperson才可以这么做
void giveRightToVote(address voter) {
    // 如果require函数的第一个参数返回false，那么所有的状态改变和Ether账户都将被回滚。
    // 经常可以使用require函数来检查函数是否被正确调用，第二个参数用来提示发生了什么错误。
   require(GetSender() == chairperson, "Only chairperson can give right to vote.");
   require(!voters[voter].value.voted, "The voter already voted.");
   require(voters[voter].value.weight == 0);
   voters[voter].value.weight = 1;
}

// 将投票权代理给其他人
void delegate(address to) {
    //指定引用
    sender = voters[msg.sender];
    require(!sender.value.voted, "you already voted");
    require(to != GetSender(), "Self-delegation is disallowed.");

    while(voters[to].delegate != sender){
        to = GetSender();
    }

    // 设定代理方的voted为true即已投票
    sender.value.voted = true;
    sender.value.delegate = to;
    delegate_ = voters[to];

    if(delegate_.value.voted){
        // 如果被代理方已经投票，则直接将代理方的投票权重添加到被代理方所投的提案
        proposals[delegate_.value.vote].value.voteCount += sender.value.weight;
    }else{
        // 如果代理方未投票，则增加被代理方的投票权重为代理方的投票权重
        delegate_.value.weight += sender.value.weight;
     }
}
