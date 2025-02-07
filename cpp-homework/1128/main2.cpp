#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

unordered_map<string, int> stock = {
    {"Chicken", 0},
    {"Lettuce", 0},
    {"Tomato", 0},
    {"Cheese", 0},
    {"Onion", 0},
    {"Sauce", 0}};

vector<string> Food = {"Chicken", "Lettuce", "Tomato", "Cheese", "Onion", "Sauce"};

void handleStock(string food, int num) {
    stock[food] += num;
    cout << "Stocked " << food << " with " << num << " units" << endl;
}

void handleOrder(string &customer_id, vector<pair<string, int>> &order) {
    unordered_map<string, int> missing;
    bool canFulfill = true;

    for (const auto &item : order) {
        const string &food = item.first;
        int num = item.second;
        if (stock[food] < num) {
            missing[food] = num - stock[food];
            canFulfill = false;
        }
    }

    if (canFulfill) {
        for (const auto &item : order) {
            stock[item.first] -= item.second;
        }
        cout << "Order " << customer_id << " completed" << endl;
    } else {
        cout << "Order " << customer_id << " failed: missing ";
        bool first = true;
        for (const auto &item : order) {
            if (missing.find(item.first) != missing.end()) {
                if (!first) {
                    cout << ", ";
                }
                cout << item.first << " " << missing[item.first];
                first = false;
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    string line;
    getline(cin, line);
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;
        if (command == "Stock") {
            string food;
            int num;
            ss >> food >> num;
            handleStock(food, num);
        } else if (command == "Order") {
            string customer_id;
            ss >> customer_id;
            vector<pair<string, int>> order;
            string food;
            int num;
            while (ss >> food >> num) {
                order.emplace_back(food, num);
            }
            handleOrder(customer_id, order);
        } else if (command == "Inventory") {
            cout << "=== Inventory === " << endl;
            for (auto &item : Food) {
                cout << item << ": " << stock[item] << endl;
            }
            cout << "=================" << endl;
        }
    }
}