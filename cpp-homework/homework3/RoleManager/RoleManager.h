#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
class Role {

public:
    string getId() const {
        return this->character_id;
    }

    virtual double getStrength() const {
        return this->base_strength;
    }
    virtual double getMana() const {
        return this->base_mana;
    }
    virtual double getAgility() const {
        return this->base_agility;
    }

    virtual double getPower() const = 0;

    virtual void upgrade() = 0;

    virtual void apply_equipment(double equipment, string type) = 0;

    void set_base_strength(double strength) {
        this->base_strength = strength;
    }

    void set_base_mana(double mana) {
        this->base_mana = mana;
    }

    void set_base_agility(double agility) {
        this->base_agility = agility;
    }

    void set_character_id(string character_id) {
        this->character_id = character_id;
    }

protected:
    double base_strength = 0;
    double base_mana = 0;
    double base_agility = 0;
    int level = 0;
    string character_id;
    bool is_equipped = false;
};

class Warrior : public Role {
public:
    double getStrength() const override {
        return this->base_strength + this->weapon_strength;
    }

    double getPower() const override {
        return getStrength() * 1.5 + getMana() * 0.5 + getAgility() * 0.8;
    }

    void upgrade() override {
        if (level >= 5)
            cout << "Character " << this->character_id << " is already at max level" << endl;
        else {
            ++level;
            this->base_strength *= 1.1;
        }
    }

    void apply_equipment(double equipment, string type) {

        if (is_equipped)
            cout << "Character " << this->character_id << " already has equipment" << endl;
        else {
            if (type != "weapon")
                return;
            this->is_equipped = true;
            this->weapon_strength = equipment;
        }
    }

    double weapon_strength = 0;
};

class Mage : public Role {

public:
    double getMana() const override {
        return this->base_mana + 2 * this->staff_power;
    }

    double getPower() const override {
        return getMana() * 2.0 + getStrength() * 0.6 + getAgility() * 0.7;
    }

    void upgrade() override {
        if (level >= 5)
            cout << "Character " << this->character_id << " is already at max level" << endl;
        else {
            ++level;
            this->base_mana *= 1.2;
        }
    }

    void apply_equipment(double equipment, string type) override {

        if (is_equipped)
            cout << "Character " << this->character_id << " already has equipment" << endl;
        else {

            if (type != "staff")
                return;
            this->is_equipped = true;
            this->staff_power = equipment;
        }
    }

    double staff_power = 0;
};

class Rogue : public Role {

public:
    double getAgility() const override {
        return this->base_agility + this->stealth_bonus;
    }

    double getPower() const override {
        return getAgility() * 1.8 + getStrength() * 0.6 + getMana() * 0.4;
    }

    void upgrade() override {
        if (level >= 5)
            cout << "Character " << this->character_id << " is already at max level" << endl;
        else {
            ++level;
            this->base_agility *= 1.15;
        }
    }

    void apply_equipment(double equipment, string type) override {

        if (is_equipped)
            cout << "Character " << this->character_id << " already has equipment" << endl;
        else {
            if (type != "cloak")
                return;
            this->is_equipped = true;
            this->stealth_bonus = equipment;
        }
    }

    double stealth_bonus = 0;
};
