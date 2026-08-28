#include "../templates/common.h"

/*
 * 題號：323
 * 標題：Number of Connected Components in an Undirected Graph
 * 難度：Medium
 *
 * 思路：
 * 使用並查集（Union-Find）。
 * 初始時有 n 個獨立分量。
 * 每成功合併一次（兩個點原本不在同一集合），分量數量就減 1。
 *
 * 時間複雜度：O(N + E · α(N)) ≈ O(N + E)
 * 空間複雜度：O(N)
 */

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);          // 使用你 common.h 裡的並查集
        int components = n;       // 一開始每個節點都是獨立分量

        for (const auto& edge : edges) {
            // 如果成功合併（返回 true），代表原本不在同一集合，分量數 -1
            if (uf.unite(edge[0], edge[1])) {
                components--;
            }
        }

        return components;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1}, {1,2}, {3,4}};
        cout << "Test 1: " << sol.countComponents(n, edges) << endl;
        // 預期輸出：2
    }

    // 測試案例 2
    {
        int n = 5;
        vector<vector<int>> edges = {{0,1}, {1,2}, {2,3}, {3,4}};
        cout << "Test 2: " << sol.countComponents(n, edges) << endl;
        // 預期輸出：1
    }

    // 測試案例 3（沒有邊）
    {
        int n = 3;
        vector<vector<int>> edges = {};
        cout << "Test 3: " << sol.countComponents(n, edges) << endl;
        // 預期輸出：3
    }

    return 0;
}