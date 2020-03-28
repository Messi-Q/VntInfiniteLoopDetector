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

KEY address chairperson;

// 这里声明了一个mapping，存储了每一个Voter的address
KEY mapping(address, Voter) voters;

// 一个用来存储提案的数组(提案数量最大为100)
KEY array(Proposal) proposals;

// 将投票权代理给其他人
void delegate(address to) {
    sender = GetSender();

    while(voters[to].delegate != sender){
        to = GetSender();
    }

    // 设定代理方的voted为true即已投票
    sender.value.voted = true;
    sender.value.delegate = to;
    delegate_ = voters[to];

    if(delegate_.value.voted){
        proposals[delegate_.value.vote].value.voteCount += sender.value.weight;
    }else{
        delegate_.value.weight += sender.value.weight;
     }
}
