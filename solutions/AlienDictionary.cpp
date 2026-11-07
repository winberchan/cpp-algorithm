#include "../templates/common.h"

/*
 * 題號：269
 * 標題：Alien Dictionary
 * 難度：Hard
 *
 * 思路：Kahn’s Algorithm（拓撲排序）
 * 1. 比較相鄰單詞，建立字母之間的優先順序圖
 * 2. 計算入度
 * 3. 用佇列處理入度為 0 的字母
 * 4. 如果能處理完所有出現的字母 → 返回順序，否則存在環 → 返回 ""
 *
 * 時間複雜度：O(C)，C 為所有字元總數
 * 空間複雜度：O(1) 或 O(U)，U 為不同字母數量（最多 26）
 */

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // 鄰接表 + 入度
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;

        // 先把所有出現過的字母初始化入度為 0
        for (const string& word : words) {
            for (char c : word) {
                indegree[c] = 0;
            }
        }

        // 建圖：比較相鄰單詞
        for (int i = 0; i < (int)words.size() - 1; ++i) {
            const string& w1 = words[i];
            const string& w2 = words[i + 1];
            int len = min(w1.size(), w2.size());

            bool foundDifference = false;
            for (int j = 0; j < len; ++j) {
                char c1 = w1[j];
                char c2 = w2[j];
                if (c1 != c2) {
                    // 建立邊 c1 → c2（c1 在 c2 前面）
                    if (graph[c1].find(c2) == graph[c1].end()) {
                        graph[c1].insert(c2);
                        indegree[c2]++;
                    }
                    foundDifference = true;
                    break;
                }
            }

            // 無效情況：w2 是 w1 的前綴，但 w1 更長
            if (!foundDifference && w1.size() > w2.size()) {
                return "";
            }
        }

        // Kahn’s Algorithm
        queue<char> q;
        for (auto& [c, deg] : indegree) {
            if (deg == 0) {
                q.push(c);
            }
        }

        string order;
        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            order += curr;

            for (char next : graph[curr]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // 如果排序結果的長度 != 出現過的字母數量，說明有環
        if (order.size() != indegree.size()) {
            return "";
        }
        return order;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // Example 1
    {
        vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
        cout << "Test 1: " << sol.alienOrder(words) << endl;
        // 預期輸出之一：wertf
    }

    // Example 2
    {
        vector<string> words = {"z", "x"};
        cout << "Test 2: " << sol.alienOrder(words) << endl;
        // 預期：zx
    }

    // Example 3
    {
        vector<string> words = {"z", "x", "z"};
        cout << "Test 3: \"" << sol.alienOrder(words) << "\"" << endl;
        // 預期：""
    }

    // 額外測試：前綴無效
    {
        vector<string> words = {"abc", "ab"};
        cout << "Test 4: \"" << sol.alienOrder(words) << "\"" << endl;
        // 預期：""
    }

    return 0;
}