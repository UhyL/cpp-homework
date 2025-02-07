class Zombie {
    public:
        int hp;
        int atk;
        int speed;
        int x;
        int y;
        
        Zombie();
        
        Zombie(int h, int a, int s, int pos_x) : atk(a), hp(h), speed(s), x(pos_x), y(9){}
};