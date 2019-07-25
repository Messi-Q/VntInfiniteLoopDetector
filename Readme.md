# VntInfiniteLoophDee 

This repo is a python implementation of smart contract vulnerability detection based on graph neural network (GCN). In this research work, we focus on the infinite loop of smart contracts.
All of the infinite loop types we concerned are implemented by C/C++ of [VNT](https://github.com/vntchain/go-vnt). By the way, [VNT](https://github.com/vntchain/go-vnt), similar to Ethereum, is the next generation of commercial-grade intelligent value delivery infrastructure, 
which is dedicated to solving the problem of high energy consumption and low efficiency in the current public chain.

We implemented a dozen infinite loop cases using the vnt smart contract language. Then, we use the automation tool to extract the graph from smart contracts.
The results of model training and model evaluation are given below.


### Running project
* To run program, use this command: python InfiniteLoopDetector.py.
* In addition, you can use specific hyperparameters to train the model. All the hyperparameters can be found in `parser.py`.

Examples:
```shell
python InfiniteLoopDetector.py --dataset data/SMART_CONTRACT_VNT
python InfiniteLoopDetector.py --dataset data/SMART_CONTRACT_VNT --model gcn_modify --n_hidden 192 --lr 0.001 -f 64,64,64 --dropout 0.1 --vector_dim 100 --epochs 50 --lr_decay_steps 10,20 
```

Using script：
Repeating 10 times for different seeds with `train.sh`.
```shell
for i in $(seq 1 10);
do seed=$(( ( RANDOM % 10000 )  + 1 ));
python InfiniteLoopDetector.py --model gcn --seed $seed | tee logs/smartcheck_"$i".log;
done
```
Then, you can find the training results in the `logs`.

