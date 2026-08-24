#include "../templates/common.h"

/*
 * 題號: 261
 * 標題: Graph Valid Tree
 * 難度: Medium
 * 思路: 使用並查集檢查圖是否為有效的樹
 * 
 * 時間複雜度: O(N⋅α(N))
 * 空間複雜度: O(N)
 */

class Solution {
public:
    // 在這裡寫解法
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) {
            return false;
        }

        UnionFind uf(n);

        for (const auto& edge : edges) {
            if (!uf.unite(edge[0], edge[1])) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    // 測試 1：是樹
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1},{0,2},{0,3},{1,4}};
        cout << "Test 1: " << (sol.validTree(n, edges) ? "true" : "false") << endl;
    }

    // 測試 2：有環
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1},{1,2},{2,3},{1,3},{1,4}};
        cout << "Test 2: " << (sol.validTree(n, edges) ? "true" : "false") << endl;
    }

    // 測試 3：邊數不足
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1},{0,2},{0,3}};
        cout << "Test 3: " << (sol.validTree(n, edges) ? "true" : "false") << endl;
    }

    return 0;
}