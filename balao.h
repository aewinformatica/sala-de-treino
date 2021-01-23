#ifndef BALAO_H
#define BALAO_H
#include "SDL/SDL.h"


class Balao{
      
      public:
             Balao();
             int x;
             int y;
             int direcao,status,colisoes;
             int furado;
              void aplica_imagem( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip  );
              
              void solta_balao(SDL_Surface* destination,int xscreen,int yscreen);
              int choca_balao(int px,int largura,int py,int altura);
      };

#endif
