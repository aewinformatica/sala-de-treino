#ifndef BOLA_H
#define BOLA_H
#include "SDL/SDL.h"


class Bola{
      
      public:
             Bola();
             int x;
             int y;
             int frame,sentido,cano;
             int direcao,status,colisoes;
             int contador,inifumaca;
             int furado;
             void aplica_imagem( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip  );
             void fumaca(SDL_Surface* destination,int xini,int yini,int cont);
              void solta_bola(SDL_Surface* destination,int xscreen,int yscreen,int xini , int yini,int tipo,int direcao);
              int choca_bola(int px,int largura,int py,int altura,int xini , int yini);
              
          
      };

#endif
