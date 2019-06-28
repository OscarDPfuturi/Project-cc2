#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const int maxdisp = 10;

#include "inicia.h"

#include "nave.h"
#include "bala.h"



void Bala::contacto(Nave nave,BITMAP* buffer){
    if (getX() == nave.getX() && getY() == nave.getY()){
        //Nave::borrar();
        textout_centre_ex(buffer, font, "LE DISTE", ANCHO/2, ALTO/2, 0xffffff, 0x999999);
    }
}



void Bala::mostrar_nave(BITMAP* bala,BITMAP* buffer,Nave* nave_jugador){
    masked_blit(bala, buffer, 0, 0,getX() ,getY(), 6, 6);
}

void Bala::mover(){
    setX(getX() + getdX());
    setY(getY() - getdY());
}



int main()
{
    //setlocale(LC_ALL,"spanish");//gramática
    Nave *nave_jugador = new Nave();
    nave_jugador->setX(ANCHO/2-20);
    nave_jugador->setY(3*ALTO/4);
    nave_jugador->setDir(1);

    Bala *bala_jugador[maxdisp];
    Nave *nave_enemigo[maxdisp];

    for (int i=0;i<maxdisp;i++){
        bala_jugador[i] = new Bala();
        nave_enemigo[i] = new Nave();
    }

    nave_enemigo[0]->setX(ANCHO/2-22);
    nave_enemigo[0]->setY(1);



    //inicia la libreria de allegro...
    inicia_allegro(ANCHO,ALTO);

    //inicia el menu de fondo...
	BITMAP *fondo_menu = load_bitmap("simple1f.bmp",NULL);
	BITMAP *fondo_menu2 = load_bitmap("simple1n.bmp",NULL);
	BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
	BITMAP *buffer = create_bitmap(ANCHO,ALTO);


	//clear_to_color(buffer, 0x333333);
    //inicializa el sonido
    SAMPLE *archivo_sonido;

    //inicializa las naves y el fondo de juego
    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio3.bmp",NULL);
    BITMAP *bala = load_bitmap("bala.bmp", NULL);  // otra cosa

    BITMAP *nave_e1 = load_bitmap("enemigo1.bmp",NULL);
    BITMAP *nave_e2 = load_bitmap("enemigo1.bmp",NULL);

    int i = ALTO ,flag_dispara=0, contt = 0,nro_disparos=0;

    bool salida = false;

    // menu simple
	while (!salida){
        textout_centre_ex(buffer, font, "SHOOTING PLANES", ANCHO/2, ALTO/4, 0xffffff, 0x999999);
        // pinta el cursor
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);

        // se muestra todo por pantalla
	    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);

        // posicion del boton
        if (mouse_x > 270 && mouse_x < 370 &&
            mouse_y > 295 && mouse_y < 340){

            blit(fondo_menu2, buffer, 0, 0, 0, 0, ANCHO, ALTO);



            // se ha pulsado el boton del raton
            if ( mouse_b & 1){

                //sonido...
                archivo_sonido = load_wav("audio01.wav");

                inicia_audio(330,300,archivo_sonido);

                while(!key[KEY_ESC]){
                    blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);
                    if(i == 0) i=ALTO;

                    textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
                    textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",4);//vidas...


                    nave_jugador->mostrar_nave(nave,buffer);
                    nave_jugador->mover();

                    nave_enemigo[0]->mostrar_enemigo(nave_e1,buffer);
                    //nave_enemigo[0]->mover();

                    //rutina de disparos
                    if(key[KEY_SPACE]  && flag_dispara == 0){
                        if(nro_disparos < maxdisp-1){

                            bala_jugador[nro_disparos]->setX(nave_jugador->getX()+20);
                            bala_jugador[nro_disparos]->setY(nave_jugador->getY()+3);
                            bala_jugador[nro_disparos]->setdX(0);
                            bala_jugador[nro_disparos]->setdY(3);

                            nro_disparos++;
                            flag_dispara = 1;
                        }
                    }

                    if(nro_disparos > 0){
                        for(int cont = 0; cont < nro_disparos; cont++){

                            bala_jugador[cont]->mostrar_nave(bala,buffer,nave_jugador);

                            bala_jugador[cont]->mover();

                            /*bala_jugador[cont]->setX(bala_jugador[cont]->getX() + bala_jugador[cont]->getdX()); mueve la bala
                            bala_jugador[cont]->setY(bala_jugador[cont]->getY() - bala_jugador[cont]->getdY());*/
                            if (bala_jugador[cont]->getY() > ALTO || bala_jugador[cont]->getY() < 0 ||
                                bala_jugador[cont]->getX() > ANCHO || bala_jugador[cont]->getX() < 0){

                                for (int i=0; i<nro_disparos; i++){
                                    bala_jugador[i] = bala_jugador[i+1];
                                }

                                nro_disparos--;
                                if (nro_disparos < 0) nro_disparos = 0;

                                bala_jugador[nro_disparos] = new Bala();
                            }
                        }
                        if (contt++ > 20){
                            flag_dispara = 0; contt = 0;
                        }
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
