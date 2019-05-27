#include <stdlib.h>
#include <allegro.h>
#include "inicia.h"
#include <locale.h>

const int maxdisp = 10, ANCHO = 500, ALTO = 450;


//template <class obj>
class Nave{
    int x,y;
    int dir;

public:
    Nave(int _x,int _y,int _dir) : x(_x), y(_y), dir(_dir){};
    virtual void mostrar_nave(BITMAP*,BITMAP*);
    virtual void mover();
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
    Bala(int _x,int _y,int _dir,int _dx,int _dy) : Nave(_x,_y,_dir){dx=_dx,dy=_dy;};
    void mostrar_nave(BITMAP*,BITMAP*);
};

void Bala::mostrar_nave(BITMAP* nave,BITMAP* buffer){
    masked_blit(nave, buffer, 0, 0, dx, dy, 6, 6);
}




struct NAVE{
    int x,y;
    int dir;
    int ndisparos;
}nav = {ANCHO/2-20,3*ALTO/4,1,0};

struct Balas{
   int x, y;
   int dx, dy;

}disparos[maxdisp];

void mostrar_nave(BITMAP *nave,BITMAP *buffer,struct NAVE nav)
{
  masked_blit( nave, buffer, 40*nav.dir, 0, nav.x, nav.y, 40, 47);
}

int main()
{
    setlocale(LC_ALL,"spanish");//gramática

    Nave nave_jugador(250,300,1);


    inicia_allegro(ANCHO,ALTO);

    //SAMPLE *archivo_sonido = load_wav("RE3-fin.wav");

    //inicia_audio(330,300,archivo_sonido);

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio.bmp",NULL);
    BITMAP *bala = load_bitmap("bala.bmp", NULL);  // otra cosa
    BITMAP *buffer = create_bitmap(ANCHO,ALTO);





    int i = ALTO ,flag_dispara=0, contt = 0;
    while(!key[KEY_ESC]){

        blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);  if(i == 0) i=ALTO;

        nave_jugador.mostrar_nave(nave,buffer);
        //mostrar_nave(nave,buffer,nav);

        textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
        textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",4);//vidas...

        textout_centre_ex(buffer, font, "SHOOTING PLANES", 150, 25, 0xffffff, 0x999999);


        nave_jugador.mover();
       /*if(key[KEY_UP] && nav.y > 0)
       { nav.dir = 1; nav.y -= 2; }

       else if(key[KEY_DOWN] && nav.y < ALTO-47)
       { nav.dir = 1; nav.y += 2; }

       if(key[KEY_RIGHT] && nav.x < ANCHO-40)
       { nav.dir = 2; nav.x += 2; }

       else if(key[KEY_LEFT] && nav.x > 0)
       { nav.dir = 0; nav.x -= 2; }

       else nav.dir = 1;*/

       ////rutina de disparos
       if(key[KEY_SPACE]  && flag_dispara == 0)
       {
        if(nav.ndisparos < maxdisp)
        {
         nav.ndisparos++;
         disparos[nav.ndisparos].x = nav.x + 19;
         disparos[nav.ndisparos].y = nav.y + 2;
         disparos[nav.ndisparos].dx = 0;
         disparos[nav.ndisparos].dy = -3;
         flag_dispara = 1;
        }

       }
       if (contt++ > 10){
        flag_dispara = 0; contt = 0;
       }
       if(nav.ndisparos > 0)
       {
        for(int cont = 1; cont <= nav.ndisparos; cont++)
        {
         disparos[cont].x += disparos[cont].dx;
         disparos[cont].y += disparos[cont].dy;
         masked_blit(bala, buffer, 0, 0,disparos[cont].x ,disparos[cont].y, 6, 6);

         if (disparos[cont].y > ALTO || disparos[cont].y < 0 || disparos[cont].x > ANCHO || disparos[cont].x < 0){

            disparos[cont] = disparos[nav.ndisparos];
            nav.ndisparos--;
            if (nav.ndisparos < 0)
                nav.ndisparos = 0;
         }

        }
       }
       blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
       rest(5);

    }
    //destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
