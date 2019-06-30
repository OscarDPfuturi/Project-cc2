
class Bala : public Nave{
    int dx,dy;

public:
    Bala(){};
    void mostrar(BITMAP*,BITMAP*,int);

    ~Bala(){};
    int getdX(){return dx;}
    int getdY(){return dy;}
    void setdX( int _dx){dx = _dx;}
    void setdY( int _dy){dy = _dy;}

    void mover();

    bool contacto(Nave*,int);
};

