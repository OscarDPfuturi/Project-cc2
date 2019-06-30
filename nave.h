#include <allegro.h>

const int ANCHO = 640, ALTO = 480;

class Nave{
    int x,y;
    int dir;
    int vidas;

public:

    Nave(){};
    Nave(int _x,int _y,int _dir) : x(_x), y(_y), dir(_dir){};
    ~Nave(){};
    virtual void mostrar(BITMAP*,BITMAP*,int);

     void mover(int);

    virtual bool contacto(Nave);

    int getVida(){return vidas;};
    void setVida(int _vida){vidas = _vida;};

    int getX(){return x;}
    int getY(){return y;}

    void setX(const int _x){x = _x;}
    void setY(const int _y){y = _y;}
    void setDir(const int _dir){dir = _dir;}

    void borrar();
};

