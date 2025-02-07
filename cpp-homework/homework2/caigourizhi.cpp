#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

     int current_price[n + 1];

    map<int, int> products[n + 1]; // 左参数表示价格、右参数表示数量
    int total_cost = 0;

    while (m--) {
        string temp;
        int id, price;
        cin >> temp >> id >> price;
        if (temp == "buy") {
            products[id][price]++;
            total_cost += price;
        }
        for (auto it = products[id].begin(); it != products[id].end();) {
            if (it->first < price) {
                products[id][price] += it->second;
                it = products[id].erase(it);
            } else {
                break;
            }
        }
    }
    int total_price = 0;
    for (int i = 1; i <= n; i++) {
       for(auto & pair : products[i]) {
        total_price += pair.first * pair.second;
       }
    }
    int total_earn = total_price - total_cost;
    cout << total_earn << endl;
}
