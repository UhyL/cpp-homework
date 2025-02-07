class Plant {
public:
    int x;
    int y;
    int atk;
    int hp;
    bool status;
    
    virtual ~Plant(){};
};

class Pea : public Plant {
public:
    Pea(int h, int a, int pos_x, int pos_y) {
        this->atk = a;
        this->hp = h;
        this->x = pos_x;
        this->y = pos_y;
    }
};

class Nut : public Plant {
public:
    Nut(int h, int pos_x, int pos_y) {
        this->x = pos_x;
        this->y = pos_y;
        this->hp = h;
    }
};

class Potato : public Plant {
public:

    Potato() {
        this->status = false;
    }

    Potato(int a, int pos_x, int pos_y) {
        this->atk = a;
        this->status = false;
        this->x = pos_x;
        this->y = pos_y;
    }
};