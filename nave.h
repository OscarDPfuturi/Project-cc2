#include <allegro.h>

const int maxdisp = 10, ANCHO = 640, ALTO = 480;

class Nave{
    int x,y;
    int dir;

public:
    Nave(){};
    Nave(int _x,int _y,int _dir) : x(_x), y(_y), dir(_dir){};
    ~Nave(){};
    virtual void mostrar_nave(BITMAP*,BITMAP*);
    virtual void mostrar_enemigo(BITMAP*,BITMAP*);
    virtual void mover();
    int getX(){return x;}
    int getY(){return y;}

    void setX(const int _x){x = _x;}
    void setY(const int _y){y = _y;}
    void setDir(const int _dir){dir = _dir;}



    void borrar();
};

