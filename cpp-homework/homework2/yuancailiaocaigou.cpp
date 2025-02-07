#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using std::cout;

bool checkOil(vector<int> &funds, double target, double k, int price);

int main() {
    int n = 2;
    double target = 2.01, k = 1;
    int sum = 2;
    vector<int> funds = {1, 1};

    // cin >> n >> target >> k;

    // while (n--) {
    //     int temp;
    //     cin >> temp;
    //     sum += temp;
    //     funds.push_back(temp);
    // }

    int left = ceil(k) - 1;
    int right = sum;

    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (checkOil(funds, target, k, mid))
            left = mid;
        else
            right = mid;
    }

    if (left <= 0)
        cout << -1 << endl;
    else
        cout << left << endl;
}
bool checkOil(vector<int> &funds, double target, double k, int price) {
    double ans = 0;
    int res = 0;

    for (int fund : funds) {
        ans += fund / price;
        res += fund % price;
    }

    ans += res / (price - k);
    if (ans >= target)
        return true;
    else
        return false;
}