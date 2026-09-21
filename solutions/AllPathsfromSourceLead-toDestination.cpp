#include "../templates/common.h"

/*
 * 題號：1059
 * 標題：All Paths from Source Lead to Destination
 * 難度：Medium
 *
 * 思路：
 * 使用 DFS + 三色標記法（類似拓撲排序中的顏色標記）來判斷：
 * 1. 從 source 出發的所有路徑是否最終都能到達 destination
 * 2. 路徑中是否存在環（有環則不可能所有路徑都導向 destination）
 *
 * 顏色定義：
 * - 0 (None/White)：尚未訪問
 * - 1 (Gray)：正在訪問中（遞迴棧中）
 * - 2 (Black)：已完全處理完畢
 *
 * 如果在 DFS 過程中遇到 Gray 節點 → 存在環 → 返回 false
 * 如果遇到葉子節點，必須是 destination 才返回 true
 *
 * 時間複雜度：O(N + E)
 * 空間複雜度：O(N + E)
 */

class Solution {
private:
    static const int GRAY = 1;
    static const int BLACK = 2;

    // 建立鄰接表
    vector<vector<int>> buildDigraph(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        return graph;
    }

    // DFS 檢查從 node 出發是否所有路徑都導向 dest
    bool leadsToDest(const vector<vector<int>>& graph, int node, int dest, vector<int>& states) {
        // 如果已經訪問過
        if (states[node] != 0) {
            // 只有變成 BLACK 才代表之前確認過是安全的
            return states[node] == BLACK;
        }

        // 葉子節點：必須是 destination
        if (graph[node].empty()) {
            return node == dest;
        }

        // 標記為正在訪問（Gray）
        states[node] = GRAY;

        for (int next : graph[node]) {
            if (!leadsToDest(graph, next, dest, states)) {
                return false;
            }
        }

        // 所有鄰居都處理完畢，標記為 Black
        states[node] = BLACK;
        return true;
    }

public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int>> graph = buildDigraph(n, edges);
        vector<int> states(n, 0);  // 0 = 未訪問
        return leadsToDest(graph, source, destination, states);
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1：true
    {
        int n = 3;
        vector<vector<int>> edges = {{0,1}, {0,2}};
        int source = 0, destination = 2;
        cout << "Test 1: " << (sol.leadsToDestination(n, edges, source, destination) ? "true" : "false") << endl;
        // 預期：false（因為 0→1 是死路，且 1 不是 destination）
    }

    // 測試案例 2：true
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1}, {0,3}, {1,2}, {2,1}};
        int source = 0, destination = 3;
        cout << "Test 2: " << (sol.leadsToDestination(n, edges, source, destination) ? "true" : "false") << endl;
        // 預期：false（存在環 1↔2）
    }

    // 測試案例 3：true
    {
        int n = 4;
        vector<vector<int>> edges = {{0,1}, {0,2}, {1,3}, {2,3}};
        int source = 0, destination = 3;
        cout << "Test 3: " << (sol.leadsToDestination(n, edges, source, destination) ? "true" : "false") << endl;
        // 預期：true
    }

    return 0;
}