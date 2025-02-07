#include <iostream>
#include <algorithm>
#define MAX_ACTIVITY_NUM 1000
#define LONGEST_STEP 27

int main() {
    int n;

    std::cin >> n;
    std::pair<int, int> club[MAX_ACTIVITY_NUM];

    for (int i = 0; i < n; ++i) {
        int begin, end;
        std::cin >> begin;
        std::cin >> end;
        club[i] = std::make_pair(begin, end);
    }

    std::sort(club, club + n, [](std::pair<int, int> a, std::pair<int, int> b) {
        return a.first < b.first;
    });

    int rest_time = 0;
    int pos = 0;
    int ptr = 0;

    while (ptr < n) {
        while (pos + LONGEST_STEP < club[ptr].first) {
            rest_time += 1;
            pos += LONGEST_STEP;
        }

        int far = ptr + 1;
        int early_end = club[ptr].second;
        for (; far < n; ++far) {
            if (pos + LONGEST_STEP < club[far].first || early_end < club[far].first) {
                break;
            }
            early_end = early_end < club[far].second ? early_end : club[far].second;
        }

        if (pos + LONGEST_STEP < early_end) {
            pos += LONGEST_STEP;
            rest_time += 1;
        } else {
            pos = early_end;
            rest_time += 1;
        }
        ptr = far;
    }

    std::cout << rest_time << "T" << std::endl;
}
