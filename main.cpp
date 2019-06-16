#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "inicia.h"
#include <conio.h>
#include "nave.h"
#include "bala.h"

const int maxdisp = 10, ANCHO = 640, ALTO = 480;

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

void Bala::mover(){
    setX(getX() + getdX());
    setY(getY() - getdY());
}


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

    //BITMAP *buffer = create_bitmap(640, 480);
	BITMAP *fondo_menu = load_bitmap("simple1f.bmp",NULL);;
	BITMAP *fondo_menu2 = load_bitmap("simple1n.bmp",NULL);
	BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
	BITMAP *buffer = create_bitmap(ANCHO,ALTO);

	// inicializa las variables
	//clear_to_color(buffer, 0x333333);

    SAMPLE *archivo_sonido;

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio3.bmp",NULL);
    BITMAP *bala = load_bitmap("bala.bmp", NULL);  // otra cosa


    int i = ALTO ,flag_dispara=0, contt = 0,nro_disparos=0;

    bool salida = false;

    // menu simple
	while (!salida){
        // pinta el cursor
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);

        // se muestra todo por pantalla
	    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);

        // posicion del boton
        if (mouse_x > 270 && mouse_x < 370 &&
            mouse_y > 295 && mouse_y < 340){

            blit(fondo_menu2, buffer, 0, 0, 0, 0, ANCHO, ALTO);

            // se ha pulsado el boton del raton
            if ( mouse_b & 1 ){

                //sonido...
                archivo_sonido = load_wav("audio01.wav");

                inicia_audio(330,300,archivo_sonido);

                while(!key[KEY_ESC]){
                    blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);
                    if(i == 0) i=ALTO;

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
                            bala_jugador[cont]->mover();

                            /*bala_jugador[cont]->setX(bala_jugador[cont]->getX() + bala_jugador[cont]->getdX()); mueve la bala
                            bala_jugador[cont]->setY(bala_jugador[cont]->getY() - bala_jugador[cont]->getdY());*/
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
                  salida = true;
            }
        }
        else{
            blit(fondo_menu, buffer, 0, 0, 0, 0, ANCHO, ALTO);
        }
        if ( key[KEY_ESC] ){
            salida = true;
        }
    }

    // inicializa las variables con el nuevo menu
    salida = false;
	destroy_bitmap(fondo_menu);
	destroy_bitmap(fondo_menu2);


    destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
