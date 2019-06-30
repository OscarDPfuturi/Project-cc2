#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const int maxdisp = 10;
int nro_enemigos = 1;

#include "inicia.h"

#include "nave.h"
#include "bala.h"
#include "item.h"

bool Bala::contacto(Nave *nave, int tipo){
    switch (tipo){
    case 1:
        if (getX() >= nave->getX() && getX() <= nave->getX()+62 &&
            getY() >= nave->getY() && getY() <= nave->getY()+62){
            return 1;
        }

    case 2:
        if (getX() >= nave->getX() && getX() <= nave->getX()+44 &&
            getY() >= nave->getY() && getY() <= nave->getY()+40){
            return 1;
        }
        return 0;
    }
    return 0;
}

void Bala::mostrar(BITMAP* bala,BITMAP* buffer,int tipo){
    switch (tipo){
    case 1:
        masked_blit(bala, buffer, 0, 0,getX() ,getY(), 6, 6); break;
    case 2:
        masked_blit(bala, buffer, 2, 0,getX() ,getY(), 4, 20); break;
    }

}

void Bala::mover(){

        setX(getX() + getdX());
        setY(getY() + getdY());
}

void Item::mostrar(BITMAP* item,BITMAP* buffer,int tipo){
    switch (tipo){
    case 1:
        masked_blit(item, buffer, 0, 0,getX() ,getY(), 37, 51); break;
    case 2:
        masked_blit(item, buffer, 0, 0,getX() ,getY(), 20, 25); break;
    }

}




int main()
{
    //setlocale(LC_ALL,"spanish");//gramática
    Nave *nave_jugador = new Nave();
    nave_jugador->setX(ANCHO/2-20);
    nave_jugador->setY(3*ALTO/4);
    nave_jugador->setDir(1);
    nave_jugador->setVida(4);

    Bala *bala_jugador[maxdisp];
    Bala *bala_enemigo[maxdisp];

    Nave *nave_enemigo;
    Nave *nave_enemigo2;
    Nave *nave_enemigo3;

    for (int i=0;i<maxdisp;i++){
        bala_jugador[i] = new Bala();
        bala_enemigo[i] = new Bala();
    }
    nave_enemigo = new Nave();
    nave_enemigo->setX(ANCHO/2-22);
    nave_enemigo->setY(-62);

    nave_enemigo2 = new Nave();
    nave_enemigo2->setX(-20);
    nave_enemigo2->setY(ALTO/2-10);

    nave_enemigo3 = new Nave();
    nave_enemigo3->setX(ANCHO+20);
    nave_enemigo3->setY(ALTO/2-50);

    Item *asteroide = new Item();
    asteroide->setX(ANCHO/3);
    asteroide->setY(-25);

    Item *balatriple = new Item;
    balatriple->setX(ANCHO-100);
    balatriple->setY(-25);



    //inicia las funciones de allegro...
    inicia_allegro(ANCHO,ALTO);

    //inicia el menu de fondo...
	BITMAP *fondo_menu = load_bitmap("simple1f.bmp",NULL);
	BITMAP *fondo_menu2 = load_bitmap("simple1n.bmp",NULL);
	BITMAP *cursor = load_bitmap("cursor.bmp",NULL);
	BITMAP *titulo = load_bitmap("nombre_juego.bmp",NULL);
	BITMAP *buffer = create_bitmap(ANCHO,ALTO);


	//clear_to_color(buffer, 0x333333);
    //inicializa el sonido
    SAMPLE *archivo_sonido;

    //inicializa la nave del jugador y el fondo de juego
    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio3.bmp",NULL);
    BITMAP *bala1 = load_bitmap("bala.bmp", NULL);
    BITMAP *bala2 = load_bitmap("lasser.bmp", NULL);

    //inicializa a los enemigos
    BITMAP *nave_e1 = load_bitmap("enemigo2.bmp",NULL);
    BITMAP *nave_e2 = load_bitmap("enemigo3.bmp",NULL);
    BITMAP *nave_e3 = load_bitmap("enemigo4.bmp",NULL);

    //inicializa los objetos
    BITMAP *asteroid = load_bitmap("asteroide.bmp",NULL);
    BITMAP *tresbalas = load_bitmap("itembala.bmp",NULL);

    int i = ALTO ,flag_dispara=0, contt = 0,nro_disparos=0;

    bool salida = false;

    // menu simple
	while (!salida){
        masked_blit(titulo,buffer,5,2,ANCHO/8,ALTO/4,490,92);

        //textout_centre_ex(buffer, font, "SHOOTING PLANES", ANCHO/2, ALTO/4, 0xffffff, 0x999999);
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

                while(!key[KEY_ESC] && (nave_jugador->getVida() > 0)){
                    blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);
                    if(i == 0) i=ALTO;

                    textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
                    textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",nave_jugador->getVida());//vidas...


                    nave_jugador->mostrar(nave,buffer,1);
                    nave_jugador->mover(1);

                    /*if (!bala_jugador->contacto(nave_enemigo,1)){

                    }*/

                    if (nro_enemigos > 0){
                        nave_enemigo->mostrar(nave_e1,buffer,2);
                        nave_enemigo->mover(2);
                    }



                    nave_enemigo2->mostrar(nave_e2,buffer,3);
                    nave_enemigo2->mover(3);

                    nave_enemigo3->mostrar(nave_e3,buffer,3);
                    nave_enemigo3->mover(4);

                    asteroide->mostrar(asteroid,buffer,1);
                    asteroide->mover(2);

                    balatriple->mostrar(tresbalas,buffer,2);
                    balatriple->mover(2);


                    //nave_enemigo[0]->mover();

                    //rutina de disparos
                    if(key[KEY_SPACE]  && flag_dispara == 0){
                        if(nro_disparos < maxdisp){

                            bala_jugador[nro_disparos]->setX(nave_jugador->getX()+20);
                            bala_jugador[nro_disparos]->setY(nave_jugador->getY()+3);
                            bala_jugador[nro_disparos]->setdX(0);
                            bala_jugador[nro_disparos]->setdY(-3);

                            nro_disparos++;
                            flag_dispara = 1;
                        }
                    }

                    if(nro_disparos > 0){
                        for(int cont = 0; cont < nro_disparos; cont++){

                            //mostrar la bala del jugador y moverla
                            bala_jugador[cont]->mostrar(bala2,buffer,2);
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

                            if (bala_jugador[cont]->contacto(nave_enemigo,1)){

                                nave_enemigo->~Nave();

                                destroy_bitmap(nave_e1);
                                nro_enemigos--;


                                for (int i=cont; i<nro_disparos; i++){
                                    bala_jugador[i] = bala_jugador[i+1];
                                }


                                nro_disparos--;
                                if (nro_disparos < 0) nro_disparos = 0;

                                bala_jugador[nro_disparos] = new Bala();





                                /*Enemigo *nave_enemigo2 = new Enemigo();
                                nave_enemigo2->setX(0);
                                nave_enemigo2->setY(0);*/
                            }


                        }
                        if (contt++ > 20){
                            flag_dispara = 0; contt = 0;
                        }
                    }





                    blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
                    rest(10);
                }

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
