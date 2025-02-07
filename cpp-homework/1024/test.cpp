#include <iostream>
#include <vector>

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
    cout << ans << endl;
    string res = "";
    for (int i = addr * 2; i < len * 2 + addr * 2; i += 2) {
        res += ans.substr(i, 2);
    }

    cout << "0x" << res << endl;
}

int main() {
    vector<string> broads = {"0x1111", "0x222222", "0x33333333"};
    int addr = 1;
    int len = 4;
    int max_len = 4;

    print_special_len(broads, addr, len, max_len);
}