#include <iostream>
#include <vector>

using std::pair;
using std::vector;

struct TreeNode {
    int val;
    vector<TreeNode *> children;
    TreeNode(int x) : val(x) {}
};

using StrategyFunc = bool (*)(TreeNode *, TreeNode *);

int n = 0, p = 0, q = 0, k = 0;

int dfs(TreeNode *node, TreeNode *parent, StrategyFunc strategy) {
    if (!node) return 0;
    int total_value = 0;

    if (strategy(node, parent)) {
        total_value += node->val;
        for (auto child : node->children) {
            total_value += dfs(child, node, strategy);
        }
    }

    return total_value;
}

bool w_strategy(TreeNode *node, TreeNode *parent) {
    return node->val > p;
}

bool h_strategy(TreeNode *node, TreeNode *parent) {
    if (!parent) return true;

    return node->val > q && (node->val + parent->val) > k;
}

bool x_strategy(TreeNode *node, TreeNode *parent) {
    if (!parent) return true;
    return node->val % 2 == 0;
}

TreeNode *buildTree(vector<int> &values, vector<pair<int, int>> &edges) {
    vector<TreeNode *> nodes(n, nullptr);

    for (int i = 0; i < n; ++i) {
        nodes[i] = new TreeNode(values[i]);
    }

    for (auto edge : edges) {
        int parent = edge.first, child = edge.second;
        nodes[parent - 1]->children.push_back(nodes[child - 1]);
    }

    return nodes[0];
}

int main() {
    std::cin >> n >> p >> q >> k;

    vector<pair<int, int>> edges;
    vector<int> values(n + 1);

    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        edges.emplace_back(pair(x, y));
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
    }

    TreeNode *root = buildTree(values, edges);
    int value_w = dfs(root, nullptr, w_strategy);
    int value_h = dfs(root, nullptr, h_strategy);
    int value_x = dfs(root, nullptr, x_strategy);

    std::cout << value_w << " " << value_h << " " << value_x << std::endl;
}