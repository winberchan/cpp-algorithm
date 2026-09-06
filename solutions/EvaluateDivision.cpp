#include "../templates/common.h"

/*
 * 題號：399
 * 標題：Evaluate Division
 * 難度：Medium
 *
 * 思路：帶權並查集（Weighted Union-Find）
 * 每個變數是一個節點，edge 的權重代表「相除的比值」。
 * 對每個節點維護：
 *   parent[x] = 父節點
 *   weight[x] = x / parent[x] 的比值
 *
 * 透過路徑壓縮時同步更新 weight，就能在 O(α(N)) 時間內查出任意兩個變數的比值。
 *
 * 時間複雜度：O((N + Q) · α(N))，N 為變數數量，Q 為查詢數量
 * 空間複雜度：O(N)
 */

class Solution {
private:
    // 帶權並查集：parent 和 weight 用 unordered_map 儲存（因為變數是字串）
    unordered_map<string, string> parent;
    unordered_map<string, double> weight;   // weight[x] = x / parent[x]

    // 查找根節點，同時做路徑壓縮並更新權重
    pair<string, double> find(const string& node) {
        // 如果是第一次出現的變數，初始化為自己，權重 1
        if (parent.find(node) == parent.end()) {
            parent[node] = node;
            weight[node] = 1.0;
            return {node, 1.0};
        }

        if (parent[node] != node) {
            // 遞迴找根，並更新當前節點的權重
            auto [root, parent_weight] = find(parent[node]);
            // 路徑壓縮：直接指向根
            parent[node] = root;
            // 權重更新：x / root = (x / parent) * (parent / root)
            weight[node] *= parent_weight;
        }
        return {parent[node], weight[node]};
    }

    // 合併兩個變數，並建立比值關係
    // 已知 dividend / divisor = value
    void unite(const string& dividend, const string& divisor, double value) {
        auto [root1, weight1] = find(dividend);   // weight1 = dividend / root1
        auto [root2, weight2] = find(divisor);    // weight2 = divisor / root2

        if (root1 != root2) {
            // 把 root1 掛到 root2 下面
            // 我們要讓：dividend / divisor = value
            // 即 (dividend / root1) * (root1 / root2) * (root2 / divisor) = value
            // 所以 root1 / root2 = value * weight2 / weight1
            parent[root1] = root2;
            weight[root1] = value * weight2 / weight1;
        }
    }

public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {
        // 1. 根據 equations 建立帶權並查集
        for (int i = 0; i < equations.size(); ++i) {
            const string& a = equations[i][0];
            const string& b = equations[i][1];
            double val = values[i];
            unite(a, b, val);
        }

        // 2. 處理每個查詢
        vector<double> results;
        for (const auto& q : queries) {
            const string& a = q[0];
            const string& b = q[1];

            // 任一變數沒出現過
            if (parent.find(a) == parent.end() || parent.find(b) == parent.end()) {
                results.push_back(-1.0);
                continue;
            }

            auto [root1, weight1] = find(a);  // weight1 = a / root1
            auto [root2, weight2] = find(b);  // weight2 = b / root2

            if (root1 != root2) {
                // 不在同一個連通分量
                results.push_back(-1.0);
            } else {
                // a / b = (a / root) / (b / root) = weight1 / weight2
                results.push_back(weight1 / weight2);
            }
        }

        return results;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1
    {
        vector<vector<string>> equations = {{"a","b"}, {"b","c"}};
        vector<double> values = {2.0, 3.0};
        vector<vector<string>> queries = {{"a","c"}, {"b","a"}, {"a","e"}, {"a","a"}, {"x","x"}};
        auto res = sol.calcEquation(equations, values, queries);
        cout << "Test 1: ";
        for (double x : res) cout << x << " ";
        cout << endl;
        // 預期：6.0 0.5 -1.0 1.0 -1.0
    }

    // 測試案例 2
    {
        vector<vector<string>> equations = {{"a","b"}, {"b","c"}, {"bc","cd"}};
        vector<double> values = {1.5, 2.5, 5.0};
        vector<vector<string>> queries = {{"a","c"}, {"c","b"}, {"bc","cd"}, {"cd","bc"}};
        auto res = sol.calcEquation(equations, values, queries);
        cout << "Test 2: ";
        for (double x : res) cout << x << " ";
        cout << endl;
        // 預期：3.75 0.4 5.0 0.2
    }

    return 0;
}