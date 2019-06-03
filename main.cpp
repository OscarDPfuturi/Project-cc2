#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "inicia.h"
#include <conio.h>
#include "nave.h"
#include "bala.h"

const int maxdisp = 10, ANCHO = 500, ALTO = 450;

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



void Bala::mostrar_nave(BITMAP* bala,BITMAP* buffer,Nave nave_jugador){
    masked_blit(bala, buffer, 0, 0,getX() ,getY(), 6, 6);
}

/*void Bala::mover(BITMAP* bala,BITMAP* buffer){
    int flag_dispara = 0,nro_disparos = 0,contt = 0;
    if(nro_disparos > 0){
        for(int cont = 0; cont < nro_disparos; cont++){
            setX(getX() + getdX());
            setY(getY() - getdY());
            //masked_blit(bala, buffer, 0, 0,getX() ,getY(), 6, 6);

            if (getY() > ALTO || getY() < 0 ||
                getX() > ANCHO || getX() < 0){
                    //bala_jugador[cont] = bala_jugador[nro_disparos];
                    nro_disparos--;
                    if (nro_disparos < 0)
                        nro_disparos = 0;
            }
        }
    }
}*/


int main()
{
    //setlocale(LC_ALL,"spanish");//gramática
    Nave nave_jugador(ANCHO/2-20,3*ALTO/4,1);

    Bala *bala_jugador[maxdisp];

    for (int i=0;i<maxdisp;i++){
        bala_jugador[i] = new Bala();

    }

    //inicia la libreria de allegro...
    inicia_allegro(ANCHO,ALTO);

    //sonido...
    SAMPLE *archivo_sonido = load_wav("audio01.wav");

    inicia_audio(330,300,archivo_sonido);

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
        if(key[KEY_SPACE]  && flag_dispara == 0){
            if(nro_disparos < maxdisp){
                bala_jugador[nro_disparos]->setX(nave_jugador.getX()+20);
                bala_jugador[nro_disparos]->setY(nave_jugador.getY()+3);
                bala_jugador[nro_disparos]->setdX(0);
                bala_jugador[nro_disparos]->setdY(3);
                nro_disparos++;
                flag_dispara = 1;
            }
        }

        if(nro_disparos > 0){
            for(int cont = 0; cont < nro_disparos; cont++){

                bala_jugador[cont]->setX(bala_jugador[cont]->getX() + bala_jugador[cont]->getdX());
                bala_jugador[cont]->setY(bala_jugador[cont]->getY() - bala_jugador[cont]->getdY());
                bala_jugador[cont]->mostrar_nave(bala,buffer,nave_jugador);

                if (bala_jugador[cont]->getY() > ALTO || bala_jugador[cont]->getY() < 0 ||
                    bala_jugador[cont]->getX() > ANCHO || bala_jugador[cont]->getX() < 0){
                    /*int aux= *(A+t-1);
                    for (int i=t-1; i>=0; i--){
                        *(A+i) = *(A+i-1);
                    }
                    *A = aux;*/
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
    destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
