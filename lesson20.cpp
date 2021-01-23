

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "SDL/SDL_mixer.h"
#include "bola.h"
#include "timer.h"
#include "onofre.h"
#include <sstream>
#include<time.h>
#include<stdlib.h>


//Screen attributes
const int SCREEN_WIDTH =400;
const int SCREEN_HEIGHT = 295;


int randomico (int x);

const int SCREEN_BPP = 32;

//The frames per second
const int FRAMES_PER_SECOND = 12;

//The dimenstions of the stick figure

const int deslocamentox = 10;
const int deslocamentoy = 8;

 int direcaoposi = 10;
 int direcaonega = -10;

const int direita=1;
const int baixo=2;
const int esquerda=3;
const int cima=4;

SDL_Surface *screen = NULL;
SDL_Surface *fundo = NULL;
SDL_Surface *fundo2 = NULL;
SDL_Surface *inicio = NULL;
SDL_Surface *message2 = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *sorte = NULL;
SDL_Surface *message = NULL;
SDL_Surface *barra_vida = NULL;

Mix_Chunk *som01 = NULL;
Mix_Music *som02 = NULL;

Mix_Music *musicadefundo = NULL;

TTF_Font *font = NULL;
TTF_Font *font2 = NULL;
TTF_Font *font3 = NULL;
//The event structure
SDL_Event event;
SDL_Event evento2;

SDL_Rect life[150];

//The color of the font
SDL_Color textColor = { 0xF0, 0xFF, 0xF0 };
SDL_Color textColor2 = { 0, 0, 0 };

 int randomico (int x)
  {
    return (rand()%x) + 1;
  }

SDL_Surface *load_image2( std::string filename ) 
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old surface
        SDL_FreeSurface( loadedImage );
        
        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
    //Return the optimized surface
    return optimizedImage;
}

void aplica_superficie( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void set_life(int cont)
{
     
     if(cont*4<150){
     life[cont].x = 0;
     life[cont].y = 0;
     life[cont].w=4*cont;
     life[cont].h=6;
     }
     else{
     life[cont].x = 0;
     life[cont].y = 0;
     life[cont].w=150;
     life[cont].h=6;
     }
   
   
}

bool load_files()
{
    
    //Carrega os sprites
    fundo = load_image2("fundo2.png");
    fundo2 = load_image2("Camada_frente2.png");
    inicio =load_image2("matrix.jpg");
    musicadefundo=Mix_LoadMUS("sons/evebory.wav");
    barra_vida=load_image2("life.png");
    
   font = TTF_OpenFont( "lazy.ttf", 25 );
   font2 = TTF_OpenFont( "AARDC.ttf", 25 );
   font3 = TTF_OpenFont( "BABY.ttf", 20 );
    //If there was a problem in loading the sprite
    
    if( fundo == NULL )
    {
        return false;    
    }
    if(musicadefundo==NULL){
                            
        printf("musica failed: %s\n", SDL_GetError());
        
         fprintf(stderr,Mix_GetError());
         return false;    
                            
                            }
     if( font == NULL )
    {
        return false;    
    }
    //If everything loaded fine
    return true;
}


bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;    
    }
    
     if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }
    if( TTF_Init() == -1 )
    {
        return false;    
    }
    //Set the window caption
    SDL_WM_SetCaption( "Sala de treino", NULL );
    
    //If everything initialized fine
    return true;
}

void clean_up()
{
    //Free the surface
   
    SDL_FreeSurface( fundo );
   
    Mix_FreeChunk(som01);
    //Quit SDL
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
    bool entrada =false;
    bool fim =false;
    //Initialize
    if( init() == false )
    {
        fprintf(stderr,"nao pode inicializar\n");
        return 1;
    }
    
    //Load the files
    if( load_files() == false )
    {
        fprintf(stderr,"erro ao carregar aarquivos\n");
        return 1;
    }
    
    
    srand(time(NULL));//para pegar numero randomico
    


    //The frame rate regulator
    Timer fps;
    
    //The stick figure
    int i,sair=0,baixou=0,levantou;
   
    int numero_randomico=4;
    int pause=0;
    int cano=5;
    int nivel=1;
    int bolas_desviadas=0,colisao_bola=0,aux,nivelveloci=1;
    ONOFRE walk;
    Bola bola[100];
    
   
    int numero_baloes=6;
    int contador;
    
  
     // abertura
     while(entrada==false){
      aplica_superficie( 0,0, inicio, screen );
     message2 = TTF_RenderText_Solid( font3, "Sala de treino", textColor );
           aplica_superficie( 120,50, message2, screen );
      walk.show(screen);
      message = TTF_RenderText_Solid( font3, "Pressione enter para começar", textColor );
      aplica_superficie( 50,100, message, screen );
      
      
        fps.start();
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
       
        SDL_PollEvent( &event );
        if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN ){
        entrada=true;
                
        }
        if(event.type == SDL_QUIT){
         entrada=true;
         quit=true;
         fim=true;
         }
       while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait...    
        }
   }
      Mix_PlayMusic( musicadefundo, -1 );      
    
     fprintf(stderr,"%d channels are playing\n", Mix_Playing(-1));
     
     
     
     
    //While the user hasn't quit
    while( quit==false )
    {
    
        //Start the frame timer
          fps.start();
    
        //While there's events to handle
       while( SDL_PollEvent( &event ))

        {
            //Handle events for the stick figure
            walk.handle_eventos(&event);
            
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
             
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p){
             pause=1;
             } 
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q){
              Mix_FreeMusic( musicadefundo);
             }
                
        }

                        

        //Move the stick figure
        walk.move();
       
      aplica_superficie(0, 0, fundo, screen );
       
       std::stringstream time;
            
        //Convert the timer's time to a string
        time << "Tempo: " << SDL_GetTicks()/1000 ;
       
        time << "  Nivel: " << nivelveloci ; 
        //Render the time surface
       seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );
       
        //Apply the time surface
        aplica_superficie( ( SCREEN_WIDTH - seconds->w ) / 2+60, 0, seconds, screen );
 
        //Free the time surface
        SDL_FreeSurface( seconds );
    
       
        if(walk.pulo_acabou==0){
                 levantou=walk.funcao_pulo(walk.cont,screen);   
                   walk.cont++; 
                   if(walk.cont>10)
                   walk.cont=0;    
//                   levantou=20;
                                   }
                                   else levantou=0; 
          if(walk.pulo_acabou==0 && walk.offSet<=5)
             walk.duplo_pulo=1;
            else walk.duplo_pulo=0;
                                   
          if(walk.pulo_parede==0){
                 walk.pulo_acabou=1;                 
                 walk.funcao_pulo_parede(walk.cont4,screen);   
                   walk.cont4++; 
                   if(walk.cont4>3)
                   walk.cont4=0;    
                              }                                   
        
        if(walk.dashini==1){
                                   
                   walk.funcao_dash(walk.cont2,screen);   
                   walk.cont2++; 
                   if(walk.cont2>3)
                   walk.cont2=0;   
                   baixou=10; 
                        }
          
                         
         if(walk.antidashini==1){
                                   
                   walk.funcao_antidash(walk.cont3,screen);   
                   walk.cont3++; 
                   if(walk.cont3>3)
                   walk.cont3=0; 
                   baixou=10;   
                        }           
           if(walk.dashini==0 && walk.antidashini==0)                             
           baixou=0;
           
   

         
         
         
         if(nivel<=10){
          for(i=0;i<=nivel;i++){
          if(bola[i].status==1 && bola[i].furado==1){
               bola[i].status=0;
               bola[i].furado=0;
               bola[i].inifumaca=1;
               bola[i].contador=0;
               bola[i].x=0;
               bola[i].y=0;
               bolas_desviadas++;
               }
                               }            
          for(i=0;i<=nivel;i++){                       
            if(bola[i].status==0 && bola[i].furado==0){
                          bola[i].sentido=randomico(numero_randomico);
                          bola[i].cano=randomico(cano);
                          bola[i].furado=1;
                                 }                                          
          switch(bola[i].sentido){         
                       
                case direita:
                     
                     if(bola[i].inifumaca==0){
                       bola[i].solta_bola(screen,SCREEN_WIDTH,SCREEN_HEIGHT,340,40+40*bola[i].cano,2,direcaonega);
                      if(levantou>0)
                       aux=bola[i].choca_bola(walk.offSet,25,levantou+45,55-baixou,340,40+40*bola[i].cano);         
                       
                       else
                       aux=bola[i].choca_bola(walk.offSet,25,walk.y+40,55-baixou,340,40+40*bola[i].cano);         
                       if(aux==1)
                        colisao_bola++;
                        
                     }                                       
                                       
                    if(bola[i].contador<9){
                       bola[i].fumaca(screen,340,35+37*bola[i].cano,bola[i].contador);
                       bola[i].contador++;
                     }
                     
                     break;
                 case baixo:
                     if(bola[i].inifumaca==0){
                       bola[i].solta_bola(screen,SCREEN_WIDTH,SCREEN_HEIGHT,340,40+40*bola[i].cano,2,direcaonega);
                       if(levantou>0)
                       aux=bola[i].choca_bola(walk.offSet,25,levantou+45,55-baixou,340,40+40*bola[i].cano);         
                       else
                       aux=bola[i].choca_bola(walk.offSet,25,walk.y+40,55-baixou,340,40+40*bola[i].cano);
                       if(aux==1)
                        colisao_bola++;     
                                                   
                     }                                       
                                       
                    if(bola[i].contador<9){
                       bola[i].fumaca(screen,340,35+37*bola[i].cano,bola[i].contador);
                       bola[i].contador++;
                     }
                    
                      break;
                 case esquerda:
                     
                     if(bola[i].inifumaca==0){
                       bola[i].solta_bola(screen,SCREEN_WIDTH,SCREEN_HEIGHT,0,40+40*bola[i].cano,2,direcaoposi);
                       if(levantou>0)
                       aux=bola[i].choca_bola(walk.offSet,25,levantou+45,55-baixou,0,40+40*bola[i].cano);         
                       else
                       aux=bola[i].choca_bola(walk.offSet,25,walk.y+40,55-baixou,0,40+40*bola[i].cano); 
                       if(aux==1)
                        colisao_bola++;       
                                              
                     }                                       
                                       
                    if(bola[i].contador<9){
                       bola[i].fumaca(screen,0,35+37*bola[i].cano,bola[i].contador);
                       bola[i].contador++;
                     }
                    
                      
                      
                      break;
                 case cima:
                       if(bola[i].inifumaca==0){
                       bola[i].solta_bola(screen,SCREEN_WIDTH,SCREEN_HEIGHT,0,40+40*bola[i].cano,2,direcaoposi);
                      if(levantou>0)
                       aux=bola[i].choca_bola(walk.offSet,25,levantou+45,55-baixou,0,40+40*bola[i].cano);         
                       else
                        aux=bola[i].choca_bola(walk.offSet,25,walk.y+40,55-baixou,0,40+40*bola[i].cano); 
                        if(aux==1)
                        colisao_bola++;       
                         
                     }                                       
                                       
                    if(bola[i].contador<9){
                       bola[i].fumaca(screen,0,35+37*bola[i].cano,bola[i].contador);
                       bola[i].contador++;
                     }
                     
                      break;
                                                                      
                }     
        
                               
         
              
              }
                    
           }
           if(bolas_desviadas>15 && bolas_desviadas<30 && nivelveloci==1){
            nivelveloci=2;
            direcaonega-=3;
            direcaoposi+=3;
            }
            if(bolas_desviadas>30 && bolas_desviadas<50 && nivelveloci==2){
            nivelveloci=3;
            direcaonega-=5;
            direcaoposi+=5;
            }
            if(bolas_desviadas>50 && bolas_desviadas<55 && nivelveloci==3){
            nivelveloci=4;
            direcaonega-=3;
            direcaoposi+=3;
            }
            if(bolas_desviadas>55 && bolas_desviadas<60 && nivelveloci==4){
            nivelveloci=5;
            direcaonega-=1;
            direcaoposi+=1;
            }
            if(bolas_desviadas>55 && bolas_desviadas<60 && nivelveloci==5){
            nivelveloci=6;
            nivel=2;
            direcaonega+=10;
            direcaoposi-=10;
            }
            if(bolas_desviadas>70 && bolas_desviadas<80 && nivelveloci==6){
            nivelveloci=7;
            direcaonega-=4;
            direcaoposi+=4;
            }
            if(bolas_desviadas>80 && bolas_desviadas<90 && nivelveloci==7){
            nivelveloci=8;
            nivel=3;
            direcaonega+=4;
            direcaoposi-=4;
            }
            if(bolas_desviadas>90 && bolas_desviadas<100 && nivelveloci==8){
            nivelveloci=9;
            nivel=2;
            direcaonega-=4;
            direcaoposi+=4;
            }
           set_life(colisao_bola);
           aplica_superficie(20,9, barra_vida, screen, &life[colisao_bola] );
           if(colisao_bola==30)
           quit=true;
              contador=0;
             
              
          
       if( (walk.offSet) > 270 && (walk.offSet) < 350 && (walk.y) > SCREEN_HEIGHT - 60 )
        { walk.offSet -= walk.posicao;
          if( (walk.offSet) > 271 && (walk.offSet) < 349 && (walk.y) > SCREEN_HEIGHT -60 ){
           walk.y-=walk.posicaoy;
//            balao.status=0; 
            
           
            }
            
        } 

                    
                     
        //Show the stick figure on the screen
      if(walk.pulo_acabou==1 && walk.dashini==0 && walk.antidashini==0 && walk.pulo_parede==1)
        walk.show(screen);
       
       
       
        
       
     
        
        

        
      
         //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
        //Cap the frame rate
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait...    
        }
       
        if(pause==1)
        {
                    
            message = TTF_RenderText_Solid( font3, "Pause", textColor2 );
           aplica_superficie( 150,150, message, screen );
            Mix_PauseMusic();
           if( SDL_Flip( screen ) == -1 )
            {
            return 1;    
            }
                    
                    }
        while(pause==1)
        {
          SDL_PollEvent( &evento2 );             
         if(evento2.type == SDL_KEYDOWN && evento2.key.keysym.sym == SDLK_p){
          pause=0;
          Mix_ResumeMusic();
          walk.posicao=0;
           evento2.key.keysym.sym == SDLK_s;
          
           }
        
        }   
        
    }
    
    
    Mix_PauseMusic();
    message = TTF_RenderText_Solid( font2, "Game Over", textColor2 );
    aplica_superficie( 150,150, message, screen );
         if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
        
//        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xff, 0xff, 0xff ) );
//       aplica_superficie( 200,50, sorte, screen );
        /* if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
        */
        quit=false;
        while(fim==false)
                       
        while( SDL_PollEvent( &event ) ){
                 
            walk.handle_eventos(&event);
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                fim = true;
            }

            }
       
        
        
    //Clean up
    clean_up();
//  
    return 0;    
}
