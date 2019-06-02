#include <stdlib.h>
#include <allegro.h>
#include "inicia.h"
#include <locale.h>

const int maxdisp = 10, ANCHO = 500, ALTO = 450;


class Nave{
    int x,y;
    int dir;

public:
    Nave(){};
    Nave(int _x,int _y,int _dir) : x(_x), y(_y), dir(_dir){};
    ~Nave(){};
    virtual void mostrar_nave(BITMAP*,BITMAP*);
    virtual void mover();
    int getX(){return x;}
    int getY(){return y;}

    void setX( int _x){x = _x;}
    void setY( int _y){y = _y;}



    void tipo_nave();
};

void Nave::mostrar_nave(BITMAP* nave,BITMAP* buffer){
    masked_blit(nave, buffer, 40*dir, 0, x, y, 40, 47);
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


class Bala : public Nave{
    int dx,dy;

public:
    Bala(){};
    //Bala(int _x,int _y,int _dx,int _dy) : Nave(_x,_y){};
    //void mostrar_nave(BITMAP*,BITMAP*);

    ~Bala(){};
    int getdX(){return dx;}
    int getdY(){return dy;}
    void setdX( int _dx){dx = _dx;}
    void setdY( int _dy){dy = _dy;}

    void mover(){};
};

/*void Bala::mostrar_nave(BITMAP* bala,BITMAP* buffer){
    masked_blit(bala, buffer, 0, 0, dx, dy, 6, 6);
}*/

/*void Bala::mover(){
    int flag_dispara = 0,nro_disparos = 0;
    if(key[KEY_SPACE]  && flag_dispara == 0)
       {
        if(nro_disparos < maxdisp)
        {
         nro_disparos++;
         dx = 0;
         dy = -3;
         flag_dispara = 1;
        }
       }
       if (contt++ > 10){
        flag_dispara = 0; contt = 0;
       }
       if(nro_disparos > 0)
       {
        for(int cont = 1; cont <= nro_disparos; cont++)
        {
         x += dx;
         y += dy;
         masked_blit(bala, buffer, 0, 0,x ,y, 6, 6);

         if (y > ALTO || y < 0 || x > ANCHO || x < 0){
            nro_disparos--;
            if (nro_disparos < 0)
                nro_disparos = 0;
         }

        }
       }
}*/


int main()
{
    setlocale(LC_ALL,"spanish");//gramática
    Nave nave_jugador(ANCHO/2-20,3*ALTO/4,1);

    Bala *bala_jugador[maxdisp];

    for (int i=0;i<maxdisp;i++){
        bala_jugador[i] = new Bala();

    }

    //inicia la libreria de allegro...
    inicia_allegro(ANCHO,ALTO);

    //sonido...
    //SAMPLE *archivo_sonido = load_wav("audio01.wav");

    //inicia_audio(330,300,archivo_sonido);

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio.bmp",NULL);
    BITMAP *bala = load_bitmap("bala.bmp", NULL);  // otra cosa
    BITMAP *buffer = create_bitmap(ANCHO,ALTO);


    int i = ALTO ,flag_dispara=0, contt = 0,nro_disparos=0;



    while(!key[KEY_ESC]){

        blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);  if(i == 0) i=ALTO;
        //mostrar_nave(nave,buffer,nav);
        nave_jugador.mostrar_nave(nave,buffer);

        textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
        textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",4);//vidas...

        textout_centre_ex(buffer, font, "SHOOTING PLANES", 150, 25, 0xffffff, 0x999999);

        nave_jugador.mover();

       //rutina de disparos
       if(key[KEY_SPACE]  && flag_dispara == 0)
       {

        if(nro_disparos < maxdisp){

        //nave_jugador.getX() + 19,nave_jugador.getY() + 2,0,0,-3);

         bala_jugador[nro_disparos]->setX(nave_jugador.getX()+20);
         bala_jugador[nro_disparos]->setY(nave_jugador.getY()+3);
         bala_jugador[nro_disparos]->setdX(0);
         bala_jugador[nro_disparos]->setdY(3);
        nro_disparos++;
         flag_dispara = 1;
        }

       }

       if(nro_disparos > 0)
       {

        for(int cont = 0; cont < nro_disparos; cont++){
            bala_jugador[cont]->setX(bala_jugador[cont]->getX() + bala_jugador[cont]->getdX());
            bala_jugador[cont]->setY(bala_jugador[cont]->getY() - bala_jugador[cont]->getdY());
            masked_blit(bala, buffer, 0, 0,bala_jugador[cont]->getX() ,bala_jugador[cont]->getY(), 6, 6);

            if (bala_jugador[cont]->getY() > ALTO || bala_jugador[cont]->getY() < 0 ||
                bala_jugador[cont]->getX() > ANCHO || bala_jugador[cont]->getX() < 0){
                    bala_jugador[cont] = bala_jugador[nro_disparos];
                    nro_disparos--;
                    if (nro_disparos < 0)
                        nro_disparos = 0;
            }
        }
       }

       if (contt++ > 20){
        flag_dispara = 0; contt = 0;
       }

       blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
       rest(10);

    }
    //destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
