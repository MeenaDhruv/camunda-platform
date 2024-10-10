#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void buildTree(vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node + 1, start, mid);
            buildTree(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int L, int R) {
        if (R < start || L > end)
            return 0;
        if (L <= start && end <= R)
            return tree[node];

        int mid = (start + end) / 2;
        int leftSum = query(2 * node + 1, start, mid, L, R);
        int rightSum = query(2 * node + 2, mid + 1, end, L, R);
        return leftSum + rightSum;
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid)
                update(2 * node + 1, start, mid, idx, value);
            else
                update(2 * node + 2, mid + 1, end, idx, value);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        buildTree(arr, 0, 0, n - 1);
    }

    int rangeQuery(int L, int R) {
        return query(0, 0, n - 1, L, R);
    }

    void updateValue(int idx, int value) {
        update(0, 0, n - 1, idx, value);
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(arr);

    cout << "Sum of values in range(1, 3): " << segTree.rangeQuery(1, 3) << endl;

    segTree.updateValue(1, 10);
    cout << "After update, sum of values in range(1, 3): " << segTree.rangeQuery(1, 3) << endl;

    return 0;
}
