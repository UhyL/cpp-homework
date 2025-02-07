#pragma GCC optimize(2)
#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <cstdint>

using namespace std;

int main() {
    string cmd;
    getline(cin, cmd);

    uint8_t chars[1000] = {};
    int ptr_chars = 0;

    map<int, int> brackets_map;
    stack<int> left_brackets;

    for (int i = 0; i < cmd.length(); i++) {
        if (cmd[i] == '[')
            left_brackets.push(i);
        else if (cmd[i] == ']') {
            int left_pos = left_brackets.top();
            left_brackets.pop();
            brackets_map[left_pos] = i;
            brackets_map[i] = left_pos;
        }
    }

    for (int i = 0; i < cmd.length(); i++) {
        char word = cmd[i];
        if (word == '+') {
            chars[ptr_chars]++;
        } else if (word == '-') {
            chars[ptr_chars]--;
        } else if (word == '>') {
            ptr_chars++;
        } else if (word == '<') {
            ptr_chars--;
        } else if (word == '.') {
            char ch = static_cast<char>(chars[ptr_chars]);
            cout << ch;
        } else if (word == ',') {
            char c;
            uint8_t byte = 0;
            if (std::cin.get(c)) {
                byte = static_cast<uint8_t>(c);
                ;
            }
            chars[ptr_chars] = byte;

        } else if (word == '[') {
            if (chars[ptr_chars] == 0) {
                i = brackets_map[i];
            }
        } else if (word == ']') {
            if (chars[ptr_chars] != 0) {
                i = brackets_map[i];
            }
        }
    }
}