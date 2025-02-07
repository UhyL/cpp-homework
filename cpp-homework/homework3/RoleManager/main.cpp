#include "RoleManager.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int lines;
    cin >> lines;
    unordered_map<string, Role *> roles;
    unordered_map<string, vector<Role *>> teams;

    while (lines--) {
        string op = "";
        cin >> op;

        if (op == "Add") {
            string role;
            cin >> role;
            Role *new_roles;
            if (role == "Warrior")
                new_roles = new Warrior();
            else if (role == "Mage")
                new_roles = new Mage();
            else if (role == "Rogue")
                new_roles = new Rogue();

            string id;
            cin >> id;
            new_roles->set_character_id(id);
            roles[id] = new_roles;
        } else if (op == "Set") {
            string id;
            cin >> id;

            string attribute;
            cin >> attribute;

            double value;
            cin >> value;

            if (attribute == "base_strength")
                roles[id]->set_base_strength(value);
            else if (attribute == "base_mana")
                roles[id]->set_base_mana(value);
            else if (attribute == "base_agility")
                roles[id]->set_base_agility(value);
        } else if (op == "Team") {
            vector<Role *> new_team;
            string team_id;
            cin >> team_id;

            string rest;
            getline(cin, rest);
            stringstream ss(rest);
            string id;
            while (ss >> id) {
                new_team.push_back(roles[id]);
            }
            teams[team_id] = new_team;

        } else if (op == "Modify") {
            string team_id;
            cin >> team_id;

            string attribute;
            cin >> attribute;

            double value;
            cin >> value;

            auto team = teams[team_id];

            for (Role *role : team) {
                if (attribute == "base_strength")
                    role->set_base_strength(value);
                else if (attribute == "base_mana")
                    role->set_base_mana(value);
                else if (attribute == "base_agility")
                    role->set_base_agility(value);
            }

        } else if (op == "List") {
             string mode;
             cin >> mode;

            vector<Role *> sorted_roles;
            for (const auto &pair : roles)
                sorted_roles.push_back(pair.second);

            if (mode == "Normal")
                sort(sorted_roles.begin(), sorted_roles.end(),
                     [](Role *a, Role *b) {
                         return stoi(a->getId().substr(1)) < stoi(b->getId().substr(1));
                     });
            else if (mode == "Power")
                sort(sorted_roles.begin(), sorted_roles.end(),
                     [](Role *a, Role *b) {
                         if(a->getPower() == b->getPower()) {
                             return stoi(a->getId().substr(1)) < stoi(b->getId().substr(1));
                         }
                         return a->getPower() > b->getPower();
                     });

            for (const auto &role : sorted_roles)
                cout << role->getId() << " strength " << role->getStrength() << " mana " << role->getMana() << " agility " << role->getAgility() << std::endl;

        } else if (op == "Upgrade") {
            string id;
            cin >> id;

            roles[id]->upgrade();
        } else if (op == "Equip") {
            string id;
            cin >> id;
            Role *temp = roles[id];

            string equipment_type;
            cin >> equipment_type;

            double value;
            cin >> value;

            temp->apply_equipment(value, equipment_type);
        } else if (op == "PowerList") {
            vector<Role *> sorted_roles;
            for (const auto &pair : roles)
                sorted_roles.push_back(pair.second);

            sort(sorted_roles.begin(), sorted_roles.end(),
                 [](Role *a, Role *b) {
                     return stoi(a->getId().substr(1)) < stoi(b->getId().substr(1));
                 });

            for (const auto &role : sorted_roles)
                cout << role->getId() << " power: " << role->getPower() << endl;
        } else if (op == "Battle") {
            string c1, c2;
            cin >> c1 >> c2;

            double value1 = roles[c1]->getPower();
            double value2 = roles[c2]->getPower();

            double diff = std::abs(value1 - value2);
            if (diff > 0.1 * std::max(value1, value2))
                cout << ((value1 > value2) ? c1 : c2) << " wins" << endl;
            else
                cout << "Draw" << endl;
        }
    }
}