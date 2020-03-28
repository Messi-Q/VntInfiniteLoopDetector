import os
import re
import time
import numpy as np

# map user-defined variables to symbolic names(var)

# Boolean condition expression (VAR: )
var_op_bool = ['!', '~', '**', '*', '!=', '<', '>', '<=', '>=', '==', '<<', '>>', '||', '&&']

# Assignment expressions
var_op_assign = ['|=', '=', '^=', '&=', '<<=', '>>=', '+=', '-=', '*=', '/=', '%=', '++', '--']

# vntchain built-in functions (VAR: INNFUN)
built_in_functions = ["GetSender", "GetOrigin", "GetValue", "GetBalanceFromAddress", "GetContractAddress",
                      "GetBlockHash", "GetBlockNumber", "GetTimestamp", "GetBlockProduser", "SHA3", "Ecrecover",
                      "GetGas", "GetGasLimit", "SendFromContract", "TransferFromContract", "FromI64", "FromU64",
                      "ToI64", "ToU64", "Concat", "Equal", "PrintAddress", "PrintStr", "PrintUint64T", "PrintUint32T",
                      "PrintInt64T", "PrintInt32T", "PrintUint256T", "AddressFrom", "AddressToString", "U256From",
                      "U256ToString", "AddKeyInfo", "WriteWithPointer", "ReadWithPointer", "InitializeVariables",
                      "Pow", "U256FromU64", "U256FromI64", "U256_Add", "U256_Sub", "U256_Mul", "U256_Div", "U256_Mod",
                      "U256_Pow", "U256_Shl", "U256_Shr", "U256_And", "U256_Or", "U256_Xor", "U256_Cmp", "AddGas",
                      "U256SafeMul", "U256SafeDiv", "U256SafeSub", "U256SafeAdd", "EVENT", "PrintUint16T",
                      "PrintUint128T"]

# keywords of vnt; immutable set
keywords = frozenset({'int8', 'int16', 'int32', 'int64', 'int128', 'int256', 'uint8', 'uint16', 'uint32', 'uint64',
                      'uint128', 'uint256', 'void', 'bool', 'string', 'address', 'constructor', 'KEY', 'EVENT', 'break',
                      'case', 'catch', 'char', 'char16_t', 'char32_t', 'class', 'compl', 'const', 'const_cast',
                      'constexpr', 'continue', 'decltype', 'default', 'delete', 'do', 'double', 'dynamic_cast', 'else',
                      'enum', 'explicit', 'export', 'extern', 'false', 'final', 'float', 'for', 'friend', 'goto', 'if',
                      'inline', 'int', 'long', 'mutable', 'namespace', 'new', 'noexcept', 'not', 'not_eq', 'nullptr',
                      'operator', 'or', 'or_eq', 'override', 'private', 'protected', 'public', 'register', 'revert',
                      'reinterpret_cast', 'return', 'short', 'signed', 'sizeof', 'static', 'static_assert', 'assert',
                      'static_cast', 'struct', 'switch', 'template', 'this', 'thread_local', 'throw', 'true', 'try',
                      'typedef', 'typeid', 'typename', 'union', 'unsigned', 'using', 'virtual', 'volatile',
                      'wchar_t', 'while', 'xor', 'xor_eq', 'NULL', 'and'})

# function return type
function_return_list = ['int8', 'int16', 'int32', 'int64', 'int128', 'int256', 'uint8', 'uint16', 'uint32', 'uint64',
                        'uint128', 'uint256', 'void', 'bool', 'string', 'address', "$_()", "_()", "FALLBACK"]

# define edges operations
edge_operations = ['return', 'assert', 'require', 'revert']

# define edges operation expression
dict_edgeOpName = {"NULL": 0, "FW": 1, "IF": 2, "GB": 3, "GN": 4, "WHILE": 5, "FOR": 6, "RE": 7, "AH": 8, "RG": 9,
                   "RH": 10, "IT": 11}

# define infinite loop flag (aims to "for" and "while")
dict_InfiniteLoopFlag = {"NULL": 0, "AFOR": 1, "AWHILE": 2, "LOOPFOR": 3, "LOOPWHILE": 4, "SELFCALL": 5, "FALLCALL": 6}

# define the methods of function call
dict_NodeOpName = {"NULL": 0, "CALL": 1, "INNCALL": 2, "SELFCALL": 3, "FALLCALL": 4}

"""
Time sequence: start function: 1; first edges: 2; all var nodes: 2; second edges: 3; end function: 3 
Function call methods: CALL, INNCALL, MULCALL, SELFCALL, FALLBACK
Define var nodes: If there is a built-in function, it is named var nodes 
VAR Node Feature: VAR0 FUN0 2 INNFUN ASSIGN
"""

"""
int8 - [-128 : 127]
int16 - [-32768 : 32767]
int32 - [-2147483648 : 2147483647]
int64 - [-9223372036854775808 : 9223372036854775807]

uint8 - [0 : 255]
uint16 - [0 : 65535]
uint32 - [0 : 4294967295]
uint64 - [0 : 18446744073709551615]
"""


# split all functions of contracts
def split_function(filepath):
    function_list = []
    f = open(filepath, 'r', encoding="utf-8")
    lines = f.readlines()
    f.close()
    flag = -1

    for line in lines:
        count = 0
        text = line.rstrip()
        if len(text) > 0 and text != "\n":
            if "uint" in text.split()[0] and text.startswith("uint"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("uint" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "void" in text and text.startswith("void"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("void" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "bool" in text and text.startswith("bool"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("bool" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "string" in text and text.startswith("string"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("string" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "address" in text and text.startswith("address"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("address" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "$_()" in text and text.startswith("$_()"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("$_()" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue
            if "_()" in text and text.startswith("_()"):
                function_list.append([text])
                flag += 1
                continue
            elif len(function_list) > 0 and ("_()" in function_list[flag][0]):
                for types in function_return_list:
                    if text.startswith(types):
                        count += 1
                if count == 0:
                    function_list[flag].append(text)
                    continue

    return function_list


# Position the call.value to generate the graph
# inputFile: the specific path of smart solidity_contract
def generate_graph(inputFile):
    allFunctionList = split_function(inputFile)
    functionNameList = []  # Store all functions' name
    fallbackList = []
    funflag = 0  # number of function
    varCount = 0  # number of var
    node_list = []  # Store all the points
    edge_list = []  # Store all the edges and edges features
    var_node_list = []  # store var nodes
    node_feature_list = []  # Store nodes feature
    var_feature_list = []  # Store var feature

    # Store all functions' name
    for i in range(len(allFunctionList)):
        tmp = re.compile(".*?(?=\\()")
        funTypeAndName = tmp.match(allFunctionList[i][0]).group()
        if funTypeAndName != "$_" and funTypeAndName != "_":
            result = funTypeAndName.split(" ")
            functionNameList.append(result[1])
        else:
            functionNameList.append(funTypeAndName)

    # label node_list
    for i in range(len(functionNameList)):
        if functionNameList[i] == "_" or functionNameList[i] == "$_":
            node_list.append("FALLBACK")
            fallbackList.append(["FALLBACK", allFunctionList[i]])

    if len(fallbackList) != 0:
        for i in range(1, len(fallbackList[0][1])):
            for j in range(len(functionNameList)):
                if functionNameList[j] in fallbackList[0][1][i]:
                    funflag += 1
                    node_list.append("FUN" + str(funflag))
                    node_feature_list.append(['FALLBACK', ["FUN" + str(funflag)], 1, 3, 'FALLCALL'])
                    node_feature_list.append(["FUN" + str(funflag), ['FALLBACK'], 1, 3, 'FALLCALL'])
                    edge_list.append(['FALLBACK', "FUN" + str(funflag), 'FALLBACK', 2, 'FW', 'FALLCALL'])
                    edge_list.append(["FUN" + str(funflag), 'FALLBACK', 'FALLBACK', 3, 'FW', 'FALLCALL'])

    # ======================================================================
    # ----------------------  Handle nodes and edges  ------------------------
    # ======================================================================
    for i in range(len(allFunctionList)):
        # regular expression to find variable name candidates
        currentProcessedFunctionName = functionNameList[i]  # current function name

        for j in range(1, len(allFunctionList[i])):
            text = allFunctionList[i][j]
            text_value = re.findall('[a-zA-Z0-9]+', text)
            # ======================================================================
            # ----------------------      Handle self call    ----------------------
            # ======================================================================
            if currentProcessedFunctionName + "(" in text or currentProcessedFunctionName + " (" in text:
                funflag += 1
                node_list.append("FUN" + str(funflag))
                node_feature_list.append(["FUN" + str(funflag), ["FUN" + str(funflag)], 1, 1, 'SELFCALL'])
                edge_list.append(
                    ["FUN" + str(funflag), "FUN" + str(funflag), "FUN" + str(funflag), 1, 'FW', 'SELFCALL'])
                break

            # ======================================================================
            # ----------------------   Handle for and while   ----------------------
            # ======================================================================
            elif "for(" in text_value or "for (" in text_value:
                infiniteloopflag = 0
                funflag += 1
                node_list.append("FUN" + str(funflag))
                node_feature_list.append(["FUN" + str(funflag), ["FUN" + str(funflag)], 1, 4, 'NULL'])
                result = re.findall('[(](.*?)[)]', text)[0].split(";")
                result_value = re.sub("\D", "", result[1])

                if "<" in result[1] and ("--" or "-=" in result[2]):
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                elif ">" in result[1] and ("++" or "+=" in result[2]):
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                # uint8: the max value is 255, uint16: the max value is 65535; the max value is 4294967295
                elif "uint8" in result[0] and int(result_value) > 255:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                elif "uint16" in result[0] and int(result_value) > 65535:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                elif "uint32" in result[0] and int(result_value) > 4294967295:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                elif (result[0] == "" or " ") and (result[1] == "" or " ") and (result[2] == "" or " "):
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'LOOPFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPFOR'])
                    infiniteloopflag += 1
                    varCount += 1
                else:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'AFOR'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'AFOR'])
                    varCount += 1

                var_bool_node = 0
                var_node = 0

                for b in range(len(var_op_bool)):
                    if var_op_bool[b] in text:
                        var_feature_list.append(
                            ["VAR" + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'BOOL'])
                        var_bool_node += 1
                        var_node += 1
                        break

                if var_bool_node == 0:
                    for a in range(len(var_op_assign)):
                        if var_op_assign[a] in text:
                            var_feature_list.append(
                                ["VAR" + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'ASSIGN'])
                            var_node += 1
                            break

                if var_node == 0:
                    var_feature_list.append(["VAR" + str(varCount), "FUN" + str(funflag), 2, 'FOR', 'NULL'])

                var_node_list.append('VAR' + str(varCount))
                break

            elif "while(" in text_value or "while (" in text_value:
                infiniteloopflag = 0
                funflag += 1
                node_list.append("FUN" + str(funflag))
                node_feature_list.append(["FUN" + str(funflag), ["FUN" + str(funflag)], 1, 4, 'CALL'])
                result = re.findall('[(](.*?)[)]', text)[0]

                if "True" == result:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'WHILE', 'LOOPWHILE'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'LOOPWHILE'])
                    infiniteloopflag += 1
                    varCount += 1
                else:
                    edge_list.append(
                        ["FUN" + str(funflag), 'VAR' + str(varCount), "FUN" + str(funflag), 2, 'WHILE', 'AWHILE'])
                    edge_list.append(
                        ['VAR' + str(varCount), "FUN" + str(funflag), "FUN" + str(funflag), 3, 'FW', 'AWHILE'])
                    infiniteloopflag += 1
                    varCount += 1

                var_node = 0
                var_bool_node = 0

                for b in range(len(var_op_bool)):
                    if var_op_bool[b] in text:
                        var_feature_list.append(
                            ["VAR" + str(varCount), "FUN" + str(funflag), 2, 'WHILE', 'BOOL'])
                        var_bool_node += 1
                        var_node += 1
                        break

                if var_bool_node == 0:
                    for a in range(len(var_op_assign)):
                        if var_op_assign[a] in text:
                            var_feature_list.append(
                                ["VAR" + str(varCount), "FUN" + str(funflag), 2, 'WHILE', 'ASSIGN'])
                            var_node += 1
                            break

                if var_node == 0:
                    var_feature_list.append(
                        ["VAR" + str(varCount), "FUN" + str(funflag), 2, 'WHILE', 'NULL'])

                var_node_list.append('VAR' + str(varCount))
                break

    for i in range(len(var_feature_list)):
        node_feature_list.append(var_feature_list[i])

    # Handling some duplicate elements, the filter leaves a unique
    edge_list = list(set([tuple(t) for t in edge_list]))
    edge_list = [list(v) for v in edge_list]

    return node_feature_list, var_feature_list, edge_list


def printResult(file, node_feature, edge_feature):
    main_point = ['FUN1', 'FUN2', 'FUN3', 'FUN4', 'FUN5', 'FUN6', 'FUN7', 'FUN8', 'FALLBACK', 'Contract']

    for i in range(len(node_feature)):
        if node_feature[i][0] in main_point:
            for j in range(0, len(node_feature[i][1]), 2):
                if j + 1 < len(node_feature[i][1]):
                    tmp = node_feature[i][1][j] + "," + node_feature[i][1][j + 1]
                elif len(node_feature[i][1]) == 1:
                    tmp = node_feature[i][1][j]

        node_feature[i][1] = tmp

    nodeOutPath = "../graph_data/nodes/" + file
    edgeOutPath = "../graph_data/edges/" + file

    f_node = open(nodeOutPath, 'a')
    for i in range(len(node_feature)):
        result = " ".join(np.array(node_feature[i]))
        f_node.write(result + '\n')
    f_node.close()

    f_edge = open(edgeOutPath, 'a')
    for i in range(len(edge_feature)):
        result = " ".join(np.array(edge_feature[i]))
        f_edge.write(result + '\n')
    f_edge.close()


if __name__ == "__main__":
    inputFile = "../vnt_contract/contracts/loopfallback4444.c"
    node_feature_list, var_feature_list, edge_list = generate_graph(inputFile)
    print(node_feature_list)
    print(var_feature_list)
    print(edge_list)

    inputFileDir = "../vnt_contract/contracts/"
    dirs = os.listdir(inputFileDir)
    for file in dirs:
        inputFilePath = inputFileDir + file
        print(inputFilePath)
        node_feature, var_feature, edge_feature = generate_graph(inputFilePath)
        node_feature = sorted(node_feature, key=lambda x: (x[0]))
        printResult(file, node_feature, edge_feature)
