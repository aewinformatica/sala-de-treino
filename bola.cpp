#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "bola.h"
#include "SDL/SDL_mixer.h"

const int tamanho_bola=-30;

SDL_Rect partes[ 4 ];

SDL_Surface *carrega_imagem2( std::string filename ) 
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
             SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
     //Return the optimized surface
    return optimizedImage;
}



void seta_clips(){
     
     
     partes[0].x=10;
     partes[0].y=10;
     partes[0].w=30;
     partes[0].h=30;
     
      partes[1].x=15;
     partes[1].y=15;
     partes[1].w=30;
     partes[1].h=30;
     
      partes[2].x=10;
     partes[2].y=0;
     partes[2].w=30;
     partes[2].h=10;
     
     partes[3].x=0;
     partes[3].y=20;
     partes[3].w=30;
     partes[3].h=10;
     
     }
     
Bola::Bola(){
               furado=0;
               x=0;
               y=0;
               direcao=15;
               status=0;
               colisoes=0;
               frame=0;
               inifumaca=1;//representa que ainda não soltou fumaça
               contador=1; // estado do frame da fumaça
               };
               
                
void Bola::aplica_imagem( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}




void Bola::fumaca(SDL_Surface* destination,int xini,int yini,int cont){
     SDL_Surface* fumaca01;
     SDL_Surface* fumaca02;
     SDL_Surface* fumaca03;
     SDL_Surface* fumaca04;
     SDL_Surface* fumaca05;
     SDL_Surface* fumaca06;
     SDL_Surface* fumaca07;     
     fumaca01 = carrega_imagem2("Fumaca/FUMA1.png");
     fumaca02 = carrega_imagem2("Fumaca/FUMA2.png");
     fumaca03 = carrega_imagem2("Fumaca/FUMA3.png");
     fumaca04 = carrega_imagem2("Fumaca/FUMA4.png");
     fumaca05 = carrega_imagem2("Fumaca/FUMA5.png");
     fumaca06 = carrega_imagem2("Fumaca/FUMA6.png");
     fumaca07 = carrega_imagem2("Fumaca/FUMA7.png");
     
     switch(cont){
      case 1:            
       aplica_imagem(xini,yini,fumaca01,destination); 
       break;
       case 2:            
       aplica_imagem(xini,yini,fumaca01,destination); 
       break;
       case 3:            
       aplica_imagem(xini,yini,fumaca01,destination); 
       inifumaca=0;
       break;
       
       case 4:            
       aplica_imagem(xini,yini,fumaca02,destination);   
       
        break;
       case 5:            
       aplica_imagem(xini,yini,fumaca03,destination);   

       break;
       case 6:            
       aplica_imagem(xini,yini,fumaca04,destination);    
      
       break;
       case 7:            
       aplica_imagem(xini,yini,fumaca05,destination);    
       
       break;
       case 8:            
       aplica_imagem(xini,yini,fumaca06,destination);   
         
       break;
       case 9:            
       aplica_imagem(xini,yini,fumaca07,destination);
         
       break;
     }
     
     }
     
     
void Bola::solta_bola(SDL_Surface* destination,int xscreen,int yscreen,int xini,int yini,int tipo,int direcao){
      SDL_Surface *Bola = NULL;

      Bola = carrega_imagem2("Bola_lateral.png");
       
     if(status!=1){
                           
      aplica_imagem( x+xini, y+yini, Bola, destination, NULL );
//      aplica_imagem( x, y, Bola, destination, NULL );
      frame++;
      if(frame>3)
      frame=0;
      
      
      if(tipo==1){
      x+=direcao;
      }
      if(tipo==2){
      x+=direcao;
      }
      if(tipo==3){
      y+=direcao;
      }
      if(tipo==4){
      y+=direcao;
      }
      
      if(x>xscreen-xini || x+xini<-10 || y >yscreen-yini || y+yini<-10){
       status=1;
       
       }
       
     /* if(tipo==2){
      x+=direcao;
      if(x>xscreen-xini)
       direcao=-15;
        
      if(x+xini<-10)
      direcao=15;
      }
      */
      
      }
      
          
     } 
int Bola::choca_bola(int px,int largura,int py,int altura,int xini,int yini){
     Mix_Chunk *som_beep = NULL;
     Mix_Chunk *pum = NULL;
    
      som_beep = Mix_LoadWAV( "sons/futurebeep.wav" );
//      pum=Mix_LoadWAV( "sons/futurebeep.wav" );

//      && (py-altura<y && py+altura>y )) 
//(px-largura<x+xini+tamanho_bola && px+largura>x+xini+tamanho_bola) 
       if( (px-largura<x+xini+tamanho_bola && px+largura>x+xini+tamanho_bola) && (py-altura<y+yini && py+altura>y+yini) )   {
              if(status!=1){
              Mix_PlayChannel( 0, som_beep, 0 );
              
              }
              status=1;
              
               
                 return 1;
                 }
                 else return 0;        
        }

