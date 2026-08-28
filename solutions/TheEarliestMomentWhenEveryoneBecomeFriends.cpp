#include "../templates/common.h"

/*
 * 題號：1101
 * 標題：The Earliest Moment When Everyone Become Friends
 * 難度：Medium
 *
 * 思路：
 * 1. 先把 logs 按照時間戳排序
 * 2. 使用並查集，初始有 n 個獨立群體
 * 3. 依時間順序合併朋友關係，每成功合併一次群體數就減 1
 * 4. 當群體數變成 1 時，返回當前時間戳
 * 5. 如果最後還有超過 1 個群體，返回 -1
 *
 * 時間複雜度：O(M log M + M · α(N))，M 為 logs 長度
 * 空間複雜度：O(N)
 */

class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
        // 按照時間戳排序，確保找到最早的時刻
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        UnionFind uf(n);
        int group_cnt = n;   // 初始每個人都是獨立群體

        for (const auto& log : logs) {
            int timestamp = log[0];
            int friend_a = log[1];
            int friend_b = log[2];

            // 如果成功合併（原本不在同一群體）
            if (uf.unite(friend_a, friend_b)) {
                group_cnt--;
            }

            // 所有人都連通了
            if (group_cnt == 1) {
                return timestamp;
            }
        }

        // 還有超過一個群體，無法全部成為朋友
        return -1;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1
    {
        vector<vector<int>> logs = {
            {20190101, 0, 1},
            {20190104, 3, 4},
            {20190107, 2, 3},
            {20190211, 1, 5},
            {20190224, 2, 4},
            {20190301, 0, 3},
            {20190312, 1, 2},
            {20190322, 4, 5}
        };
        int n = 6;
        cout << "Test 1: " << sol.earliestAcq(logs, n) << endl;
        // 預期輸出：20190301
    }

    // 測試案例 2（無法全部連通）
    {
        vector<vector<int>> logs = {
            {0, 2, 0},
            {1, 0, 1},
            {3, 0, 3},
            {4, 1, 2},
            {7, 3, 1}
        };
        int n = 4;
        cout << "Test 2: " << sol.earliestAcq(logs, n) << endl;
        // 預期輸出：3
    }

    return 0;
}