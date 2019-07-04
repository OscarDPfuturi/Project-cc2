#include <stdio.h>
#include <stdlib.h>

#include <time.h>

const int maxdisp = 10;



#include "inicia.h"

#include "nave.h"
#include "bala.h"
#include "item.h"


Bala::Bala(int _x,int _y,int _dx, int _dy) : Nave(_x,_y){//metodos de la clase Bala
    dx = _dx;
    dy = _dy;
}

bool Bala::contacto(Nave *nave){
    switch (getTipo()){
    case 1:
        if (getX() >= nave->getX() && getX() <= nave->getX()+50 &&
            getY() >= nave->getY() && getY() <= nave->getY()+50){
            return 1;
        }
        return 0;

    case 2:
        if (getX() >= nave->getX() && getX() <= nave->getX()+44 &&
            getY() >= nave->getY() && getY() <= nave->getY()+40){
            return 1;
        }
        return 0;
    }
    return 0;
}

void Bala::mostrar(BITMAP* bala,BITMAP* buffer){
    switch (getTipo()){
    case 1:
        masked_blit(bala, buffer, 0, 0,getX() ,getY(), 5, 6); break;
    case 2:
        masked_blit(bala, buffer, 2, 0,getX() ,getY(), 4, 20); break;
    }

}

void Bala::mover(){
        setX(getX() + getdX());
        setY(getY() + getdY());
}

void Item::mostrar(BITMAP* item,BITMAP* buffer){ //metodos de la clase Item
    masked_blit(item, buffer, 0, 0,getX() ,getY(), 20, 25);
}

void Item::mover(){
    if (getY() < ALTO-25){
        setY(getY()+2);
    }
    else{
        setY(-50);
    }
}

bool Item::contacto(Nave *nave){
    if (getX()+10 > nave->getX() && getX()+10 < nave->getX()+40 &&
        getY()+10 > nave->getY() && getY()+10 < nave->getY()+47){
        return 1;
    }
    return 0;
}


////////////////////////////////funciones para usar en main
bool contacto_balas_borde(Bala *bala){
    if (bala->getY() > ALTO+200 || bala->getY() < -100 ||
        bala->getX() > ANCHO+100 || bala->getX() < -100){
        return 1;
    }
    return 0;
}

bool iniciar_juego(BITMAP* titulo,BITMAP* buffer,BITMAP* cursor,BITMAP* fondo_menu2,BITMAP* fondo_menu){
    while (!key[KEY_ESC]){
        masked_blit(titulo,buffer,5,2,ANCHO/8,ALTO/4,490,92);

        // pinta el cursor
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13,22);

        // se muestra todo por pantalla
	    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
	    if (mouse_x > 270 && mouse_x < 370 && mouse_y > 295 && mouse_y < 340){

            blit(fondo_menu2, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            if ( mouse_b & 1) return 1;
        }
        else{
            blit(fondo_menu, buffer, 0, 0, 0, 0, ANCHO, ALTO);
        }
    }
    return 0;
}

bool game_over(BITMAP *gameOver,BITMAP *buffer){
    while (!key[KEY_ESC]){
        // se muestra todo por pantalla
	    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);

        masked_blit(gameOver,buffer,0,0,0,0,ANCHO,ALTO);

        textout_centre_ex(buffer, font, "Presione Enter para volver a jugar...", ANCHO/2, ALTO-100, 0xffffff, 0x7d7d7d);
        textout_centre_ex(buffer, font, "Presione Esc para salir...", ANCHO/2, ALTO-50, 0xffffff, 0x7d7d7d);
        if (key[KEY_ENTER]){
            return 0;
        }
    }
    return 1;
}

bool win(BITMAP *winner,BITMAP *buffer){
    while (!key[KEY_ESC]){
        // se muestra todo por pantalla
	    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);

        masked_blit(winner,buffer,0,0,0,0,ANCHO,ALTO);

        textout_centre_ex(buffer, font, "Presione Enter para volver a jugar...", ANCHO/2, ALTO-75, 0xffffff, 0x7d7d7d);
        textout_centre_ex(buffer, font, "Presione Esc para salir...", ANCHO/2, ALTO-50, 0xffffff, 0x7d7d7d);
        if (key[KEY_ENTER]){
            return 0;
        }
    }
    return 1;
}


int main()
{
    Nave *nave_jugador = new Nave();
    nave_jugador->setX(ANCHO/2-20);
    nave_jugador->setY(3*ALTO/4);
    nave_jugador->setDir(1);
    nave_jugador->setTipo(1);

    Bala *bala_jugador[maxdisp];
    Bala *bala_enemigo[maxdisp];

    Nave *nave_enemigo;
    Nave *nave_enemigo2;
    Nave *nave_enemigo3;

    for (int i=0;i<maxdisp;i++){
        bala_jugador[i] = new Bala();
    }
    nave_enemigo = new Nave();
    nave_enemigo->setX(ANCHO/2-22);
    nave_enemigo->setY(-62);
    nave_enemigo->setTipo(2);
    nave_enemigo->setVida(3);

    nave_enemigo2 = new Nave();
    nave_enemigo2->setX(-20);
    nave_enemigo2->setY(ALTO/2-10);
    nave_enemigo2->setTipo(3);
    nave_enemigo2->setVida(1);

    nave_enemigo3 = new Nave();
    nave_enemigo3->setX(ANCHO+20);
    nave_enemigo3->setY(ALTO/2-50);
    nave_enemigo3->setTipo(4);
    nave_enemigo3->setVida(1);

    Nave *asteroide = new Nave();
    asteroide->setX(ANCHO/3);
    asteroide->setY(-25);
    asteroide->setTipo(5);
    asteroide->setVida(5);

    Item *laserA = new Item();
    laserA->setX(ANCHO-100);
    laserA->setY(-25);
    laserA->setTipo(2);

    Item *vida = new Item();
    vida->setX(100);
    vida->setY(25);
    vida->setTipo(2);



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
    archivo_sonido = load_wav("audio01.wav");

    //inicializa la nave del jugador y el fondo de juego
    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio3.bmp",NULL);
    BITMAP *bala1 = load_bitmap("bala.bmp", NULL);
    BITMAP *bala2 = load_bitmap("bala2.bmp", NULL);
    BITMAP *laser = load_bitmap("lasser.bmp", NULL);

    //inicializa a los enemigos
    BITMAP *nave_e1 = load_bitmap("enemigo2.bmp",NULL);
    BITMAP *nave_e2 = load_bitmap("enemigo3.bmp",NULL);
    BITMAP *nave_e3 = load_bitmap("enemigo4.bmp",NULL);
    BITMAP *asteroid = load_bitmap("asteroide.bmp",NULL);

    //inicializa los objetos
    BITMAP *itemlaser = load_bitmap("L.bmp",NULL);
    BITMAP *vidaup = load_bitmap("vida.bmp",NULL);

    //fin de juego...
    BITMAP *gameOver = load_bitmap("game-over.bmp",NULL);
    BITMAP *winner = load_bitmap("ganar.bmp",NULL);

    int i = ALTO, tiempo = 0,tiempo2=0, nro_disparos=0, nro_disparos2 = 0;
    bool flag_dispara = 0,flag_dispara2 = 0;

    bool salida = 0;

    while (salida == 0){
        // menu simple
        if(iniciar_juego(titulo,buffer,cursor,fondo_menu2,fondo_menu)){

            //sonido...

            inicia_audio(330,300,archivo_sonido);

            nave_jugador->setVida(4);
            int nro_enemigos = 20;
            int tipo_bala = 1;

            while(!key[KEY_ESC] && (nave_jugador->getVida() > 0) && nro_enemigos > 0){//inicia el juego
                blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);
                if(i == 0) i=ALTO;

                textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
                textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",nave_jugador->getVida());//vidas...

                nave_jugador->mostrar(nave,buffer);
                nave_jugador->mover();

                if (nro_enemigos > 0){
                    nave_enemigo->mostrar(nave_e1,buffer);
                    nave_enemigo->mover();
                    if (nave_enemigo->getVida()==0) nave_enemigo->setVida(3);

                    nave_enemigo2->mostrar(nave_e2,buffer);
                    nave_enemigo2->mover();
                    if (nave_enemigo2->getVida()==0) nave_enemigo2->setVida(1);

                    nave_enemigo3->mostrar(nave_e3,buffer);
                    nave_enemigo3->mover();
                    if (nave_enemigo3->getVida()==0) nave_enemigo3->setVida(1);

                    asteroide->mostrar(asteroid,buffer);
                    asteroide->mover();
                    if (asteroide->getVida()==0) asteroide->setVida(5);
                }

                if (nro_disparos2 < maxdisp && !flag_dispara2){
                    bala_enemigo[nro_disparos2] = new Bala(nave_enemigo->getX()+31,nave_enemigo->getY()+62,0,3);
                    bala_enemigo[nro_disparos2]->setTipo(1);
                    nro_disparos2++;
                    flag_dispara2 = 1;
                }

                vida->mostrar(vidaup,buffer);
                vida->mover();

                laserA->mostrar(itemlaser,buffer);
                laserA->mover();

                //rutina de disparos
                if(key[KEY_SPACE]  && !flag_dispara){
                    if(nro_disparos < maxdisp){

                        bala_jugador[nro_disparos]->setX(nave_jugador->getX()+20);
                        bala_jugador[nro_disparos]->setY(nave_jugador->getY()+3);
                        bala_jugador[nro_disparos]->setdX(0);
                        bala_jugador[nro_disparos]->setdY(-3);
                        bala_jugador[nro_disparos]->setTipo(tipo_bala);

                        nro_disparos++;
                        flag_dispara = 1;
                    }
                }

                if(nro_disparos > 0){
                    for(int cont = 0; cont < nro_disparos; cont++){
                        if (tipo_bala == 1){
                            bala_jugador[cont]->mostrar(bala1,buffer);
                        }
                        else {bala_jugador[cont]->mostrar(laser,buffer);}


                        //mostrar la bala del jugador y moverla
                        bala_jugador[cont]->mover();

                        if (contacto_balas_borde(bala_jugador[cont])){

                            for (int i=0; i<nro_disparos; i++){
                                bala_jugador[i] = bala_jugador[i+1];
                            }

                            nro_disparos--;
                            if (nro_disparos < 0) nro_disparos = 0;

                            bala_jugador[nro_disparos] = new Bala();
                        }
                        for (int k=0; k<4; k++){
                            Nave *naveF;
                            if (k==0){ naveF = nave_enemigo; }
                            else if (k==1){ naveF = nave_enemigo2;}
                            else if (k==2){ naveF = nave_enemigo3;}
                            else { naveF = asteroide;}

                            if (bala_jugador[cont]->contacto(naveF)){
                                naveF->setVida(naveF->getVida()-1);
                                if (naveF->getVida()==0) {
                                    srand(time(NULL));

                                    if (k==0){
                                        naveF->setX(rand()%(ANCHO-50));
                                        naveF->setY(-50);
                                    }
                                    else if (k==1){
                                        naveF->setX(-25);
                                        naveF->setY(rand()%(ALTO-50));
                                    }
                                    else if (k==2){
                                        naveF->setX(ANCHO+25);
                                        naveF->setY(rand()%ALTO-50);
                                    }
                                    else {
                                        naveF->setX(rand()%(ANCHO-50));
                                        naveF->setY(-50);
                                    }
                                    nro_enemigos--;
                                }


                                for (int i=cont; i<nro_disparos; i++){
                                    bala_jugador[i] = bala_jugador[i+1];
                                }

                                nro_disparos--;
                                if (nro_disparos < 0) nro_disparos = 0;

                                bala_jugador[nro_disparos] = new Bala();
                            }
                        }
                    }
                    if (tiempo++ > 20){
                        flag_dispara = 0; tiempo = 0;
                    }
                }

                if (nro_disparos2 > 0){
                    for(int cont = 0; cont < nro_disparos2; cont++){
                        //mostrar la bala del enemigo y moverla.....................
                        bala_enemigo[cont]->mostrar(bala2,buffer);
                        bala_enemigo[cont]->mover();

                        if (contacto_balas_borde(bala_enemigo[cont])){

                            for (int i=0; i<nro_disparos2; i++){
                                bala_enemigo[i] = bala_enemigo[i+1];
                            }

                            nro_disparos2--;
                            if (nro_disparos2 < 0) nro_disparos2 = 0;

                            bala_enemigo[nro_disparos2] = new Bala();
                        }

                        if (bala_enemigo[cont]->contacto(nave_jugador)){
                            nave_jugador->setVida(nave_jugador->getVida()-1);

                            nave_jugador->setX(ANCHO/2-20);
                            nave_jugador->setY(3*ALTO/4);

                            for (int i=cont; i<nro_disparos2; i++){
                                bala_enemigo[i] = bala_enemigo[i+1];
                            }

                            nro_disparos2--;
                            if (nro_disparos2 < 0) nro_disparos2 = 0;

                            bala_enemigo[nro_disparos2] = new Bala();
                        }
                    }
                    if (tiempo2++ > 50){
                        flag_dispara2 = 0; tiempo2 = 0;
                    }

                }
                for (int k=0; k<4; k++){
                    Nave *naveG;
                    if (k == 0){ naveG = nave_enemigo; }
                    else if (k == 1){ naveG = nave_enemigo2; }
                    else if (k == 2){ naveG = nave_enemigo3; }
                    else { naveG = asteroide;}

                    if (naveG->contacto(nave_jugador)){
                        nave_jugador->setVida(nave_jugador->getVida()-1);

                        nave_jugador->setX(ANCHO/2-20);
                        nave_jugador->setY(3*ALTO/4);

                        srand(time(NULL));
                        naveG->setVida(0);

                        if (k==0){
                            naveG->setX(rand()%(ANCHO-50));
                            naveG->setY(-25);
                        }
                        else if (k==1){
                            naveG->setX(-25);
                            naveG->setY(rand()%(ALTO-50));
                        }
                        else if (k==2){
                            naveG->setX(ANCHO+25);
                            naveG->setY(rand()%(ALTO-50));
                        }
                        else {
                            naveG->setX(rand()%(ANCHO-50));
                            naveG->setY(-25);
                        }
                        nro_enemigos--;
                    }
                }
                if (vida->contacto(nave_jugador)){
                    vida->setX(rand()%(ANCHO-30));
                    vida->setY(-20);
                    //destroy_bitmap(vidaup);
                    nave_jugador->setVida(nave_jugador->getVida()+1);
                }
                if (laserA->contacto(nave_jugador)){
                    laserA->setX(rand()%(ANCHO-30));
                    laserA->setY(-20);
                    //destroy_bitmap(vidaup);
                    tipo_bala = 2;
                }

                blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
                rest(10);
            }//se ha presionado Esc y termina el juego.......................

            midi_pause();
            if (nave_jugador->getVida() < 1){
                if (game_over(gameOver,buffer)){
                    salida = 1;
                }

            }
            else if(nro_enemigos < 1){
                if (win(winner,buffer)){
                    salida = 1;
                }

            }

        }
        else {salida = 1;}
    }

	destroy_bitmap(fondo_menu);
	destroy_bitmap(fondo_menu2);
    destroy_bitmap(nave_e1);
    destroy_bitmap(nave_e2);
    destroy_bitmap(nave_e3);

    destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
