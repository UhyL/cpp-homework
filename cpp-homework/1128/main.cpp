#include <iostream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

int main() {
    int chicken = 0, lettuce = 0, tomato = 0, cheese = 0, onion = 0, sauce = 0;

    int n;
    cin >> n;

    while (n--) {
        string op;
        cin >> op;
        if (op == "Stock") {
            string type;
            cin >> type;
            int num;
            cin >> num;
            if (type == "Chicken")
                chicken += num;
            else if (type == "Lettuce")
                lettuce += num;
            else if (type == "Tomato")
                tomato += num;
            else if (type == "Cheese")
                cheese += num;
            else if (type == "Onion")
                onion += num;
            else if (type == "Sauce")
                sauce += num;

            cout << "Stocked " << type << " with " << num << " units" << endl;
        } else if (op == "Order") {
            string order_name;
            cin >> order_name;
            map<string, int> consume;
            string rest;
            getline(cin, rest);
            stringstream s(rest);

            string type;
            string num;

            while (s >> type) {
                s >> num;
                consume[type] = stoi(num);
            }

            bool enough = true;
            map<string, int> less;

            for (auto every : consume) {
                string type1 = every.first;
                int num1 = every.second;
                if (type1 == "Chicken") {
                    if (chicken < num1) {
                        enough = false;
                        less[type1] = num1 - chicken;
                    }
                } else if (type1 == "Lettuce") {
                    if (lettuce < num1) {
                        enough = false;
                        less[type1] = num1 - lettuce;
                    }
                } else if (type1 == "Tomato") {
                    if (tomato < num1) {
                        enough = false;
                        less[type1] = num1 - tomato;
                    }
                } else if (type1 == "Cheese") {
                    if (cheese < num1) {
                        enough = false;
                        less[type1] = num1 - cheese;
                    }
                } else if (type == "Onion") {
                    if (onion < num1) {
                        enough = false;
                        less[type1] = num1 - onion;
                    }
                } else if (type == "Sauce") {
                    if (sauce < num1) {
                        enough = false;
                        less[type1] = num1 - sauce;
                    }
                }
            }
            if (!enough) {
                int index = less.size();
                cout << "Order " << order_name << " failed: missing ";
                if (less["Chicken"] != 0) {
                    cout << "Chicken " << less["Chicken"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                if (less["Lettuce"] != 0) {
                    cout << "Lettuce " << less["Lettuce"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                if (less["Tomato"] != 0) {
                    cout << "Tomato " << less["Tomato"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                if (less["Cheese"] != 0) {
                    cout << "Cheese " << less["Cheese"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                if (less["Onion"] != 0) {
                    cout << "Onion " << less["Onion"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                if (less["Sauce"] != 0) {
                    cout << "Sauce " << less["Sauce"];
                    index--;
                    if (index != 0) cout << ", ";
                }

                cout << endl;
            } else {
                cout << "Order " << order_name << " completed" << endl;
                for (auto every : consume) {
                    string type1 = every.first;
                    int num1 = every.second;
                    if (type1 == "Chicken") {
                        chicken -= num1;
                    } else if (type1 == "Lettuce") {
                        lettuce -= num1;
                    } else if (type1 == "Tomato") {
                        tomato -= num1;
                    } else if (type1 == "Cheese") {
                        cheese -= num1;
                    } else if (type == "Onion") {
                        onion -= num1;
                    } else if (type == "Sauce") {
                        sauce -= num1;
                    }
                }
            }

        } else if (op == "Inventory") {
            cout << "=== Inventory ===" << endl;
            cout << "Chicken: " << chicken << endl;
            cout << "Lettuce: " << lettuce << endl;
            cout << "Tomato: " << tomato << endl;
            cout << "Cheese: " << cheese << endl;
            cout << "Onion: " << onion << endl;
            cout << "Sauce: " << sauce << endl;
            cout << "=================" << endl;
        }
    }
}