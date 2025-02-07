#include <iostream>

#include <climits>

#include <vector>

using namespace std;


int dfs(int pos, int m,
    const vector < pair < int, int >> & orders, vector < vector < int >> & dp,
        const vector < vector < int >> & dist, int finished) {
    if (dp[pos][finished] != -1) return dp[pos][finished];
    
    // 如果所有订单都完成了
    if (finished == (1 << 2 * orders.size()) - 1) return 0;
    int min_Time = INT_MAX;

    for (int i = 0; i < orders.size(); i++) {
        int rest = orders[i].first - 1;
        int cust = orders[i].second - 1;
        int picked = 1 << (2 * i);
        int delivered = 1 << (2 * i + 1);

        // 如果没有取该订单
        if (!(picked & finished)) {
            if (dist[pos][rest] != INT_MAX) {
                min_Time = min(min_Time, dist[pos][rest] + dfs(rest, m, orders, dp, dist, finished | picked));
            }

        }

        // 如果没有送该订单
        if (!(delivered & finished) && (picked & finished)) {
            if (dist[pos][cust] != INT_MAX) {
                min_Time = min(min_Time, dist[pos][cust] + dfs(cust, m, orders, dp, dist, finished | delivered));
            }

        }


    }
    dp[pos][finished] = min_Time;
    return min_Time;
}



int main() {
    int n, m;
    cin >> n >> m;

    vector < vector < int >> dist(m, vector < int > (m));
    vector < pair < int, int >> orders(n);


    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; j++) {
            cin >> dist[i][j];
            if (dist[i][j] == -1) dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < n; ++i) {
        cin >> orders[i].first >> orders[i].second;
    }

    // 计算任意两点之间的最短距离
    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 记录在pos位置 完成掩码（取餐 + 送餐）任务的最短时间
    vector < vector < int >> dp(m, vector < int > (1 << (2 * n), -1));


    int min_Time = dfs(0, m, orders, dp, dist, 0);
    cout << min_Time << endl;
}
