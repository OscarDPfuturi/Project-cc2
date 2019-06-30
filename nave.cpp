#include "nave.h"

/*Nave::Nave(int _x,int _y,int _dx){
    setX(_x);
    setY(_y);
    dx = _dx;
}*/

void Nave::mostrar(BITMAP* nave,BITMAP* buffer,int tipo){
    switch (tipo){
    case 1:
        masked_blit(nave, buffer, 40*dir, 0, x, y, 40, 47); break;
    case 2:
        masked_blit(nave, buffer, 0, 0, x, y, 62, 62); break;
    case 3:
        masked_blit(nave, buffer, 0, 0, x, y, 44, 40); break;
    }
}

void Nave::mover(int tipo){
    switch (tipo){
    case 1://movimiento de la nave del jugador
        if(key[KEY_UP] && y > 0)
            { dir = 1; y -= 2; }

        else if(key[KEY_DOWN] && y < ALTO-47)
            { dir = 1; y += 2; }

        if(key[KEY_RIGHT] && x < ANCHO-40)
            { dir = 2; x += 2; }

        else if(key[KEY_LEFT] && x > 0)
            { dir = 0; x -= 2; }

        else dir = 1; break;
    case 2://movimiento de los enemigos 2,3,...
        if (getY() < ALTO-50){
            setY(getY()+2);
        }
        else{
            setY(-62);
        }
        break;
    case 3:
        if (getX() < ANCHO-10){
            setX(getX()+2);
        }
        else{
            setX(-25);
        }
        break;
    case 4:
        if (getX() > -20){
            setX(getX()-2);
        }
        else{
            setX(ANCHO+25);
        }
        break;
    }
}

bool Nave::contacto(Nave nave){
    if (getX() == nave.getX()){
        return 1;
    }
    return 0;
}
