#include "../templates/common.h"

/*
 * 題號：1168
 * 標題：Optimize Water Distribution in a Village
 * 難度：Hard
 *
 * 思路：
 * 把問題轉換成最小生成樹（MST）。
 * 新增一個虛擬節點 0，代表「水源」。
 * 每個房子 i（1 ~ n）連到虛擬節點 0 的邊權重 = wells[i-1]（自己挖井的成本）。
 * 原本的 pipes 就是房子之間的邊。
 * 對所有邊按權重排序後，用 Kruskal + 並查集求 MST，總成本就是答案。
 *
 * 時間複雜度：O(E log E)，E = n + pipes.size()
 * 空間複雜度：O(N)
 */

class Solution {
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        // 邊格式：{cost, u, v}
        vector<tuple<int, int, int>> edges;

        // 1. 加入虛擬節點 0 到每個房子的邊（挖井成本）
        for (int i = 0; i < n; ++i) {
            // 房子編號為 1 ~ n，虛擬節點為 0
            edges.emplace_back(wells[i], 0, i + 1);
        }

        // 2. 加入原本的水管邊
        for (const auto& pipe : pipes) {
            int house1 = pipe[0];
            int house2 = pipe[1];
            int weight = pipe[2];
            edges.emplace_back(weight, house1, house2);
        }

        // 3. 按成本排序
        sort(edges.begin(), edges.end());

        // 4. Kruskal 求 MST（節點 0 ~ n，共 n+1 個）
        UnionFind uf(n + 1);
        int total_cost = 0;

        for (const auto& [cost, u, v] : edges) {
            if (uf.unite(u, v)) {          // 成功合併才加入這條邊
                total_cost += cost;
            }
        }

        return total_cost;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1
    {
        int n = 3;
        vector<int> wells = {1, 2, 2};
        vector<vector<int>> pipes = {{1, 2, 1}, {2, 3, 1}};
        cout << "Test 1: " << sol.minCostToSupplyWater(n, wells, pipes) << endl;
        // 預期輸出：3
    }

    // 測試案例 2
    {
        int n = 2;
        vector<int> wells = {1, 1};
        vector<vector<int>> pipes = {{1, 2, 1}, {1, 2, 2}};
        cout << "Test 2: " << sol.minCostToSupplyWater(n, wells, pipes) << endl;
        // 預期輸出：2
    }

    return 0;
}