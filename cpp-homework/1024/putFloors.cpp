#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int getString2Byte(string s) {
    return (s.length() - 2) / 2;
}

void print_special_len(vector<string> &broads, int addr, int len, int max_len) {
    string ans = "";
    for (int i = 0; i < broads.size();) {
        int len_i = getString2Byte(broads[i]);
        ans += broads[i].substr(2);
        ++i;
        if (len_i < max_len) {
            int len_rest = max_len - len_i;
            while (i < broads.size() && (len_rest >= getString2Byte(broads[i]))) {
                len_rest -= getString2Byte(broads[i]);
                ans += broads[i].substr(2);
                ++i;
            }

            while (len_rest-- > 0)
                ans += "CC";
        }
    }

    string res = "";
    for (int i = addr * 2; i < len * 2 + addr * 2 && i + 1 < res.length(); i += 2) {
        res += ans.substr(i, 2);
    }
    while(res.length() < len * 2) {
        res += "CC";
    }

    cout << "0x" << res << endl;
}

void print_broads(vector<string> &broads, int max_len) {
    for (int i = 0; i < broads.size();) {
        int len_i = getString2Byte(broads[i]);
        cout << broads[i];
        ++i;
        if (len_i < max_len) {
            int len_rest = max_len - len_i;
            while (i < broads.size() && (len_rest >= getString2Byte(broads[i]))) {
                len_rest -= getString2Byte(broads[i]);
                cout << broads[i].substr(2);
                ++i;
            }

            while (len_rest-- > 0)
                cout << "CC";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<string> broads;
    int max_len = 0;

    for (int i = 0; i < n; ++i) {
        string op = "";
        cin >> op;

        if (op == "add") {
            string broad;
            cin >> broad;
            int new_len = getString2Byte(broad);
            max_len = max(max_len, new_len);
            broads.push_back(broad);
        } else if (op == "del") {
            string broad;
            cin >> broad;
            auto iter = remove(broads.begin(), broads.end(), broad);
            broads.erase(iter, broads.end());
            max_len = 0;
            for (int i = 0; i < broads.size(); ++i) {
                max_len = max(max_len, getString2Byte(broads[i]));
            }
        } else if (op == "print") {
            int addr = 0, len = 0;
            if (cin >> addr >> len) {
                print_special_len(broads, addr, len, max_len);
            } else {
                cin.clear();
                print_broads(broads, max_len);
            }
        }
    }
}
