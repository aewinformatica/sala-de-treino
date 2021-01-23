#ifndef ONOFRE_H
#define ONOFRE_H
#include "SDL/SDL.h"
#include <sstream>

//The stick figure
class ONOFRE
{
    public:
    //The offset
    int offSet;
    int y;
    //Its rate of movement
    int posicao;
    int posicaoy;
    int pulo;
    int placar;
    int sair;
    //Its current frame
    int frame;
    int frame2;
    int parado;
    int inverte;
    //Its animation status
    int status;
    int i,auxiliar;
    int fatorpulo;
    int cont,cont2,cont3,cont4;
    int pulo_acabou,pulo_parede,duplo_pulo;
    int fatordash,dashini;
    std::stringstream time;
    int dash,dash2;
    int antidashini;
    int antidash,antidash2;
    int primeiro,primeiro2;
    //The event structure
    SDL_Event* evento;
    
    public:
    //Initializes the variables
    ONOFRE();
    
    //Handles input
    void handle_eventos(SDL_Event* evento);
    
    //Moves the stick figure
    void move();    
    
    //Shows the stick figure
    void show(SDL_Surface* destination);  
    int funcao_pulo(int x,SDL_Surface* screen2);  
    void funcao_dash(int x,SDL_Surface* screen2);  
    void funcao_antidash(int x,SDL_Surface* screen2);
    int funcao_pulo_parede(int x,SDL_Surface* screen2);
  
};

#endif
