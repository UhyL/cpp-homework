#include <iostream>
#include <string>
#include <vector>
#include "time.h"
using namespace std;

struct my_time{
    int hour;
    int min;
};


int main() {
    int n;
    cin >> n;

    vector<pair<my_time, my_time>> time_intervals;

    for (int i = 0; i < n; ++i) {
        string temp;
        getline(cin, temp);

        size_t pos = temp.find('-');
        string temp1 = temp.substr(0, pos); 
        string temp2 = temp.substr(pos + 1, temp.size());

        size_t pos1 = temp1.find(':');
        size_t pos2 = temp2.find(':');
        string hour1 = temp1.substr(0, pos1);
        string min1 = temp1.substr(pos1 + 1, temp1.size());
        string hour2 = temp2.substr(0, pos2);
        string min2 = temp2.substr(pos2 + 1, temp2.size());

        my_time time1 = {stoi(hour1), stoi(min1)};
        my_time time2 = {stoi(hour2), stoi(min2)};
        time_intervals.push_back(make_pair(time1, time2));
    }

    my_time left = {0,0};
    my_time right = {0,0};
    for(auto & time_interval : time_intervals) {
        
    }
}