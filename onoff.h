#ifndef ONOFF_H
#define ONOFF_H
#include "SDL/SDL.h"

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
    int cont,cont2,cont3;
    int pulo_acabou;
    int fatordash,dashini;
    std::stringstream time;
    int dash,dash2;
    int antidashini;
    int antidash,antidash2;
    
    
    public:
    //Initializes the variables
    ONOFRE();
    
    //Handles input
    void handle_events();
    
    //Moves the stick figure
    void move();    
    
    //Shows the stick figure
    void show();  
    void funcao_pulo(int);  
    void funcao_dash(int);  
    void funcao_antidash(int);  
};
