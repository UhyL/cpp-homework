#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Plant.h"
#include "Zombie.h"

using namespace std;

bool check_zombie(vector<Zombie *> &zombies) {
    for (auto temp : zombies) {
        if (temp->y < 0)
            return true;
    }

    return false;
}

int main() {
    vector<Plant *> plants;
    vector<Zombie *> zombies;

    int num_p, num_z;

    cin >> num_p >> num_z;

    while (num_p--) {
        string type;
        cin >> type;

        if (type == "pea") {
            int hp, atk, pos_x, pos_y;
            cin >> hp >> atk >> pos_x >> pos_y;
            plants.push_back(new Pea(hp, atk, pos_x, pos_y));
        } else if (type == "nut") {
            int hp, pos_x, pos_y;
            cin >> hp >> pos_x >> pos_y;
            plants.push_back(new Nut(hp, pos_x, pos_y));
        } else if (type == "potato") {
            int atk, pos_x, pos_y;
            cin >> atk >> pos_x >> pos_y;
            plants.push_back(new Potato(atk, pos_x, pos_y));
        } else {
            string bin;
            getline(cin, bin);
        }
    }

    while (num_z--) {
        int hp, atk, speed, pos_x;
        cin >> hp >> atk >> speed >> pos_x;
        zombies.push_back(new Zombie(hp, atk, speed, pos_x));
    }

    auto cmp_plant_pos = [] (const Plant * a, const Plant *b) {
        if (a->x == b->x)
            return a->y < b->y;
        return a->x < b->x;
    };

    auto cmp_zombie_pos = [] (const Zombie * a, const Zombie *b) {
        if (a->x == b->x)
            return a->y < b->y;
        return a->x < b->x;
    };

    sort(plants.begin(), plants.end(), cmp_plant_pos);
    sort(zombies.begin(), zombies.end(), cmp_zombie_pos);

    int index = 0;

    while (++index) {

        // plants attack zombies
        for (auto it = plants.begin(); it != plants.end();) {
            Plant *plant = *it;
            if (typeid(*plant) == typeid(Pea)) {
                int pos_x = plant->x;
                int pos_y = -1;
                for (auto it1 = zombies.begin(); it1 != zombies.end();) {
                    Zombie *zombie = *it1;
                    if (zombie->x == pos_x) {
                        if (pos_y < 0)
                            pos_y = zombie->y;
                        if (pos_y == zombie->y)
                            zombie->hp -= plant->atk;

                        if (zombie->hp <= 0) {
                            zombies.erase(it1);
                            continue;
                        }
                    } else if (zombie->x > pos_x)
                        break;
                    ++it1;
                }
            } else if ((typeid(*plant) == typeid(Potato)) && plant->status == true) {
                int left_y = max(0, plant->y - 1);
                int right_y = min(9, plant->y + 1);
                int down_x = max(0, plant->x - 1);
                int up_x = min(4, plant->x + 1);

                auto in_range = [left_y, right_y, up_x, down_x](Zombie *zombie) -> bool {
                    if (zombie->x < down_x || zombie->x > up_x)
                        return false;
                    if (zombie->y < left_y || zombie->y > right_y)
                        return false;
                    return true;
                };

                for (auto it1 = zombies.begin(); it1 != zombies.end();) {
                    Zombie *zombie = *it1;
                    if (in_range(zombie)) {
                        zombie->hp -= plant->atk;

                        if (zombie->hp <= 0) {
                            zombies.erase(it1);
                            continue;
                        }
                    }
                    ++it1;
                }

                plants.erase(it);
                continue;
            }
            ++it;
        }

        // move zombies
        for (auto zombie : zombies) {
            int pos_x = zombie->x;
            int pos_y = zombie->y - zombie->speed;
            for (auto plant : plants) {
                if (pos_x == plant->x) {
                    if (typeid(*plant) == typeid(Potato)) {
                        continue;
                    }
                    pos_y = max(pos_y, plant->y);
                } else if (pos_x < plant->x)
                    break;
            }
            zombie->y = pos_y;

            for (auto plant : plants) {
                if (pos_x == plant->x) {
                    if (typeid(*plant) == typeid(Potato)) {
                            if (pos_y <= plant->y) {
                            plant->status = true;
                        }
                    }
                } else if (pos_x < plant->x)
                    break;
            }
        }

        // attack plants

        for (auto zombie : zombies) {
            int pos_x = zombie->x;
            int pos_y = zombie->y;
            for (auto it = plants.begin(); it != plants.end();) {
                Plant *plant = *it;
                if (plant->x == pos_x && plant->y == pos_y) {
                    if (typeid(*plant) == typeid(Potato)) {
                        ++it;
                        continue;
                    }
                    plant->hp -= zombie->atk;
                    if (plant->hp <= 0)
                        plants.erase(it);
                    break;
                } else if (plant->x > pos_x)
                    break;
                ++it;
            }
        }

        int p_size = plants.size();
        int z_size = zombies.size();
        cout << index << " " << p_size << " " << z_size << endl;

        if (zombies.empty()) {
            cout << "plants win" << endl;
            break;
        }
        if (check_zombie(zombies)) {
            cout << "zombies win" << endl;
            break;
        }
        

        sort(zombies.begin(), zombies.end(), cmp_zombie_pos);
    }
}