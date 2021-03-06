import argparse


def parameter_parser():
    # Experiment parameters
    parser = argparse.ArgumentParser(description='Smart contract vulnerability detection based on graph neural network')
    parser.add_argument('-D', '--dataset', type=str, default='SMART_CONTRACT_VNT',
                        choices=['SMART_CONTRACT_VNT'])
    parser.add_argument('-M', '--model', type=str, default='gcn_modify',
                        choices=['gcn_modify', 'mgcn', 'gat', 'gcn_origin'])
    parser.add_argument('--lr', type=float, default=0.001, help='learning rate')
    parser.add_argument('--lr_decay_steps', type=str, default='10,20', help='learning rate')
    parser.add_argument('--wd', type=float, default=1e-4, help='weight decay')
    parser.add_argument('-d', '--dropout', type=float, default=0.1, help='dropout rate')
    parser.add_argument('-f', '--filters', type=str, default='64,64,64', help='number of filters in each layer')
    parser.add_argument('--n_hidden', type=int, default=0,
                        help='number of hidden units in a fully connected layer after the last conv layer')
    parser.add_argument('--epochs', type=int, default=50, help='number of epochs')
    parser.add_argument('-b', '--batch_size', type=int, default=32, help='batch size')
    parser.add_argument('-t', '--threads', type=int, default=2, help='number of threads to load data')
    parser.add_argument('--log_interval', type=int, default=1,
                        help='interval (number of batches) of logging')
    parser.add_argument('--device', type=str, default='cpu', choices=['cuda', 'cpu'])
    parser.add_argument('--seed', type=int, default=2484, help='random seed')
    parser.add_argument('--shuffle_nodes', action='store_true', default=False, help='shuffle nodes for debugging')
    parser.add_argument('-F', '--folds', default=5, choices=[5, 8, 10], help='n-fold cross validation')
    parser.add_argument('-a', '--adj_sq', action='store_true', default=True,
                        help='use A^2 instead of A as an adjacency matrix')
    parser.add_argument('-s', '--scale_identity', action='store_true', default=True,
                        help='use 2I instead of I for self connections')
    parser.add_argument('-c', '--use_cont_node_attr', action='store_true', default=True,
                        help='use continuous nodes attributes in addition to discrete ones')
    parser.add_argument('--alpha', type=float, default=0.2, help='Alpha value for the leaky_relu')
    parser.add_argument('--multi_head', type=int, default=4, help='number of head attentions(Multi-Head)')

    return parser.parse_args()
