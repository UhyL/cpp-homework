#include "Calculator.h"
#include <stack>
#include <sstream>

using namespace std;

Calculator::Calculator() {
    // TODO: 初始化Calculator
    precedenceTable['+'] = 6;
    precedenceTable['-'] = 6;
    precedenceTable['*'] = 5;
    precedenceTable['/'] = 5;
    precedenceTable['('] = 9;
    precedenceTable[')'] = 9;

    functionTable['+'] = [](double x, double y) -> double { return x + y; };
    functionTable['-'] = [](double x, double y) -> double { return x - y; };
    functionTable['*'] = [](double x, double y) -> double { return x * y; };
    functionTable['/'] = [](double x, double y) -> double { return x / y; };
}

void Calculator::registerOperator(const string &expr, int precedence) {
    // TODO: 注册运算符
    stringstream s(expr);
    string lhs, op, rhs, eq, exp;
    s >> lhs >> op >> rhs >> eq;
    getline(s, exp);
    precedenceTable[op[0]] = precedence;

    vector<string> nums;
    stack<string> ops;
    stringstream ss(exp);
    string token;

    while (ss >> token) {
        if (token == "(")
            ops.push(token);
        else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                nums.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else if (isdigit(token[0]) || token.length() > 1 || (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))
            nums.push_back(token);
        else {
            while (!ops.empty() && precedenceTable[ops.top()[0]] <= precedenceTable[token[0]]) {
                nums.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty()) {
        nums.push_back(ops.top());
        ops.pop();
    }

    TreeNode *tempTree = buildTree(nums);

    functionTable[op[0]] = [tempTree, lhs, rhs, this](double x, double y) -> double {
        double temp_lhs = 0, temp_rhs = 0;
        if (constantTable.find(lhs) != constantTable.end())
            temp_lhs = constantTable[lhs];

        if (constantTable.find(rhs) != constantTable.end())
            temp_rhs = constantTable[rhs];
        constantTable[lhs] = x;
        constantTable[rhs] = y;
        double res = getVal(tempTree);
        constantTable[lhs] = temp_lhs;
        constantTable[rhs] = temp_rhs;
        return res;
    };
}

void Calculator::registerConstant(const string &symbol, double val) {
    // TODO：注册常数
    constantTable[symbol] = val;
}

double Calculator::calculate(const string &expr) {
    // TODO: 解析并计算表达式

    // 中缀转换为后缀
    vector<string> nums;
    stack<string> ops;
    stringstream ss(expr);
    string token;

    while (ss >> token) {
        if (token == "(")
            ops.push(token);
        else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                nums.push_back(ops.top());
                ops.pop();
            }
            ops.pop();
        } else if (isdigit(token[0]) || token.length() > 1 || (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))
            nums.push_back(token);
        else {
            while (!ops.empty() && precedenceTable[ops.top()[0]] <= precedenceTable[token[0]]) {
                nums.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty()) {
        nums.push_back(ops.top());
        ops.pop();
    }
    TreeNode *root = buildTree(nums);

    return getVal(root);
}

TreeNode *Calculator::buildTree(vector<string> &tokens) {
    // TODO: 解析表达式并构造表达式解析树
    // 后缀构造树
    stack<TreeNode *> tree_stack;

    for (string token : tokens) {
        if (isdigit(token[0]) || token.length() > 1 || (token[0] >= 'a' && token[0] <= 'z') || (token[0] >= 'A' && token[0] <= 'Z'))
            tree_stack.push(new TreeNode(token));
        else {
            TreeNode *right = tree_stack.top();
            tree_stack.pop();
            TreeNode *left = tree_stack.top();
            tree_stack.pop();
            tree_stack.push(new TreeNode((functionTable[token[0]]), token, left, right));
        }
    }

    return tree_stack.top();
}

double Calculator::getVal(TreeNode *node) {
    // TODO: 获取树上某一节点的值

    if (!node->left && !node->right) {
        if (constantTable.count(node->element))
            return constantTable[node->element];
        return stod(node->element);
    }
    return node->operate(getVal(node->left), getVal(node->right));
}