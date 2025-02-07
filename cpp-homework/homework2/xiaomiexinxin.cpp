#include <vector>

#include <iostream>

using namespace std;



void eliminate(vector < vector < int >> & star_map, int x, int y, int flag, int m, int n) {
    if (x >= 0 && x < n && y >= 0 && y < m) {
        if (star_map[x][y] == flag) {
            star_map[x][y] = 0;
            eliminate(star_map, x + 1, y, flag, m, n);
            eliminate(star_map, x - 1, y, flag, m, n);
            eliminate(star_map, x, y + 1, flag, m, n);
            eliminate(star_map, x, y - 1, flag, m, n);
        }

    }
}


int main() {
    int n, m, x, y;

    cin >> n >> m;

    vector < vector < int >> star_map(n, vector < int > (m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> star_map[i][j];
        }
    }

    cin >> x >> y;

    int flag = star_map[x - 1][y - 1];

    eliminate(star_map, x - 1, y - 1, flag, m, n);

    for (int j = 0; j < m; ++j) {
        int empty_block = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (star_map[i][j] != 0) {
                int temp = star_map[i][j];
                star_map[i][j] = star_map[empty_block][j];
                star_map[empty_block][j] = temp;
                --empty_block;

            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            cout << star_map[i][j] << " ";
        }
        cout << star_map[i][m - 1] << endl;
    }
}