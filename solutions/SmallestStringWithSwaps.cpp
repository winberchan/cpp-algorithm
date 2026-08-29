#include "../templates/common.h"

/*
 * 題號：1202
 * 標題：Smallest String With Swaps
 * 難度：Medium
 *
 * 思路：
 * 1. pairs 中的索引對表示可以交換的位置，這些關係具有傳遞性。
 * 2. 使用並查集把可以互相交換的位置連成同一個連通分量。
 * 3. 同一個連通分量內的所有字元可以任意重排。
 * 4. 為了得到字典序最小的字串，把每個連通分量內的字元排序後，
 *    再按索引從小到大放回原位置。
 *
 * 時間複雜度：O(N + M · α(N) + N log N)，N 為字串長度，M 為 pairs 數量
 * 空間複雜度：O(N)
 */

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        UnionFind uf(n);

        // 1. 根據 pairs 建立連通關係
        for (const auto& edge : pairs) {
            uf.unite(edge[0], edge[1]);
        }

        // 2. 把屬於同一個根的索引分組
        unordered_map<int, vector<int>> rootToIndices;
        for (int i = 0; i < n; ++i) {
            int root = uf.find(i);
            rootToIndices[root].push_back(i);
        }

        // 3. 對每個連通分量處理
        string result = s;   // 先複製一份，之後覆蓋

        for (auto& [root, indices] : rootToIndices) {
            // 取出這個分量中的所有字元
            vector<char> chars;
            for (int idx : indices) {
                chars.push_back(s[idx]);
            }

            // 字元排序（字典序最小）
            sort(chars.begin(), chars.end());

            // 索引也排序，保證按位置從小到大填回去
            sort(indices.begin(), indices.end());

            // 把排序後的字元放回對應位置
            for (int i = 0; i < indices.size(); ++i) {
                result[indices[i]] = chars[i];
            }
        }

        return result;
    }
};

// ==================== 本地測試 ====================
int main() {
    Solution sol;

    // 測試案例 1
    {
        string s = "dcab";
        vector<vector<int>> pairs = {{0,3}, {1,2}};
        cout << "Test 1: " << sol.smallestStringWithSwaps(s, pairs) << endl;
        // 預期輸出：bacd
    }

    // 測試案例 2
    {
        string s = "dcab";
        vector<vector<int>> pairs = {{0,3}, {1,2}, {0,2}};
        cout << "Test 2: " << sol.smallestStringWithSwaps(s, pairs) << endl;
        // 預期輸出：abcd
    }

    // 測試案例 3
    {
        string s = "cba";
        vector<vector<int>> pairs = {{0,1}, {1,2}};
        cout << "Test 3: " << sol.smallestStringWithSwaps(s, pairs) << endl;
        // 預期輸出：abc
    }

    return 0;
}