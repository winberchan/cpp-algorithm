#ifndef MYCODE_COMMON_H
#define MYCODE_COMMON_H

#include <bits/stdc++.h>
using namespace std;

// ==================== 常用型別別名 ====================
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

// ==================== 並查集 (Union-Find) ====================
class UnionFind {
public:
    vector<int> parent;
    vector<int> size;

    // 構造函數：初始化 n 個集合
    UnionFind(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 查找根節點（帶路徑壓縮）
    int find(int A) {
        int root = A;
        while (root != parent[root]) {
            root = parent[root];
        }
        // 路徑壓縮
        while (A != root) {
            int old_parent = parent[A];
            parent[A] = root;
            A = old_parent;
        }
        return root;
    }

    // 合併兩個集合（按大小合併），返回是否成功合併
    bool unite(int A, int B) {
        int root_A = find(A);
        int root_B = find(B);

        if (root_A == root_B) {
            return false;   // 已經在同一個集合
        }

        // 按大小合併
        if (size[root_A] < size[root_B]) {
            parent[root_A] = root_B;
            size[root_B] += size[root_A];
        } else {
            parent[root_B] = root_A;
            size[root_A] += size[root_B];
        }
        return true;
    }
};

// ==================== 鏈表節點 ====================
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 建立鏈表輔助函數
ListNode* createList(const vector<int>& nums) {
    ListNode dummy;
    ListNode* cur = &dummy;
    for (int x : nums) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return dummy.next;
}

// 打印鏈表
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// ==================== 二元樹節點 ====================
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif // MYCODE_COMMON_H