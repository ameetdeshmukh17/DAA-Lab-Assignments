#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order {
    int id;
    long long timestamp;
};

void merge(vector<Order>& a, vector<Order>& temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i].timestamp <= a[j].timestamp)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= right)
        temp[k++] = a[j++];

    for (i = left; i <= right; i++)
        a[i] = temp[i];
}

void mergeSort(vector<Order>& a) {
    int n = a.size();
    vector<Order> temp(n);

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min(left + 2 * size - 1, n - 1);

            merge(a, temp, left, mid, right);
        }
    }
}

int main() {
    int n;

    cin >> n;

    vector<Order> orders(n);

    for (int i = 0; i < n; i++)
        cin >> orders[i].id >> orders[i].timestamp;

    mergeSort(orders);

    cout << "\nOrders sorted by timestamp:\n";
    cout << "Order ID\tTimestamp\n";

    for (const auto& order : orders)
        cout << order.id << "\t\t" << order.timestamp << '\n';

    return 0;
}