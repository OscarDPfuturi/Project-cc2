#include <allegro.h>

class Bala : public Nave{
    int dx,dy;

public:
    Bala(){};
    //Bala(int _x,int _y,int _dx,int _dy) : Nave(_x,_y){};
    void mostrar_nave(BITMAP*,BITMAP*,Nave);

    ~Bala(){};
    int getdX(){return dx;}
    int getdY(){return dy;}
    void setdX( int _dx){dx = _dx;}
    void setdY( int _dy){dy = _dy;}

    void mover();
};

