#include "nave.h"


void Nave::mostrar_nave(BITMAP* nave,BITMAP* buffer){
    masked_blit(nave, buffer, 40*dir, 0, x, y, 40, 47);
}

void Nave::mostrar_enemigo(BITMAP* nave,BITMAP* buffer){
    masked_blit(nave, buffer, 44, 0, x, y, 44, 44);
}

void Nave::mover(){
    if(key[KEY_UP] && y > 0)
       { dir = 1; y -= 2; }

       else if(key[KEY_DOWN] && y < ALTO-47)
       { dir = 1; y += 2; }

       if(key[KEY_RIGHT] && x < ANCHO-40)
       { dir = 2; x += 2; }

       else if(key[KEY_LEFT] && x > 0)
       { dir = 0; x -= 2; }

       else dir = 1;
}
