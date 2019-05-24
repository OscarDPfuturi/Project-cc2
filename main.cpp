#include <allegro.h>
#include "inicia.h"

const int maxdisp = 500, ANCHO = 500, ALTO = 450;

struct NAVE{
    int x,y;
    int dir;
    int ndisparos;
}nav = {250,300,1,0};

struct Balas{
   int x, y;
   int dx, dy;

}disparos[maxdisp];

void pintar_nave(BITMAP *nave,BITMAP *buffer,struct NAVE nav)
{
  masked_blit( nave, buffer, 40*nav.dir, 0, nav.x, nav.y, 40, 47);

}

int main()
{
    inicia_allegro(500,450);
    inicia_audio(70,70);

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *nube = load_bitmap("nube.bmp",NULL);
    BITMAP *bala = load_bitmap("bala2.bmp", NULL);  // otra cosa
    BITMAP *buffer = create_bitmap(500,450);


    int i = 450 , dsw = 0 , contt = 0;
    while(!key[KEY_ESC]){
        blit(nube,buffer,0,--i,0,0,500,450);  if(i == 0) i=450;
        pintar_nave(nave,buffer,nav);

       if(key[KEY_UP])
       { nav.dir = 1; nav.y -= 2; }

       else if(key[KEY_DOWN])
       { nav.dir = 1; nav.y += 2; }

       if(key[KEY_RIGHT])
       { nav.dir = 2; nav.x += 2; }

       else if(key[KEY_LEFT])
       { nav.dir = 0; nav.x -= 2; }

       else nav.dir = 1;

       ////rutina de disparos
       if(key[KEY_SPACE])
       {
        if(nav.ndisparos < maxdisp)
        {
         nav.ndisparos++;
         disparos[nav.ndisparos].x = nav.x +20;
         disparos[nav.ndisparos].y = nav.y;
         disparos[nav.ndisparos].dx = 0;
         disparos[nav.ndisparos].dy = -3;
        }

       }
       if(nav.ndisparos > 0)
       {
        for(int cont = 1; cont <= nav.ndisparos; cont++)
        {
         disparos[cont].x += disparos[cont].dx;
         disparos[cont].y += disparos[cont].dy;
         masked_blit(bala, buffer, 0, 0,disparos[cont].x ,disparos[cont].y, 6, 6);
        }
       }
       blit(buffer,screen,0,0,0,0,500,450);
       rest(5);

    }

    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(nube);

    return 0;
}
END_OF_MAIN();
