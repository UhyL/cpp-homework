#include "Custom.h"

using namespace std;

int main() {
    CommentsSystem system;
    int n;
    cin >> n;

    while (n--) {
        string op;
        cin >> op;

        if (op == "insert") {
            int custom_id;
            double food_rating, service_rating, environment_rating;
            string timestamp;

            cin >> custom_id >> food_rating >> service_rating >> environment_rating;
            cin.ignore();
            getline(cin, timestamp);
            system.insertComment(custom_id, food_rating, service_rating, environment_rating, timestamp);
        } else if (op == "modify") {
            int custom_id;
            string dimension, timestamp;
            double new_rating;

            cin >> custom_id >> dimension >> new_rating;
            cin.ignore();
            getline(cin, timestamp);
            system.modifyComment(custom_id, dimension, new_rating, timestamp);
        } else if (op == "delete") {
            int custom_id;
            cin >> custom_id;
            system.deleteCustom(custom_id);
        } else if (op == "history") {
            int custom_id;
            string dimension = "";
            cin >> custom_id;
            if (cin.peek() != '\n')
                cin >> dimension;
            system.history(custom_id, dimension);
        } else if (op == "display") {
            string dimension = "";
            if (cin.peek() != '\n')
                cin >> dimension;
            system.display(dimension);
        } else if (op == "range_query") {
            double food_low, food_high, service_low, service_high, environment_low, environment_high;
            cin >> food_low >> food_high >> service_low >> service_high >> environment_low >> environment_high;
            system.range_query(food_low, food_high, service_low, service_high, environment_low, environment_high);
        }
    }

    return 0;
}