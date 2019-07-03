
class Item : public Nave{
public:
    Item(){};
    ~Item(){};
    void mostrar(BITMAP*,BITMAP*);

    void mover();

    bool contacto(Nave*);


};
