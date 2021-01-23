#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "balao.h"
#include "SDL/SDL_mixer.h"




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
Balao::Balao(){
               furado=0;
               x=100;
               y=200;
               direcao=5;
               status=0;
               colisoes=0;
               };
void Balao::aplica_imagem( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


void Balao::solta_balao(SDL_Surface* destination,int xscreen,int yscreen){
      SDL_Surface *balao = NULL;
      balao = carrega_imagem2("balao.png");
     
     if(status!=1){
                           
      aplica_imagem( x, y, balao, destination,NULL );
      x+=direcao;
      if(x>xscreen)
       direcao=-5;
        }
      if(x<0)
      direcao=5;
          
     } 
int Balao::choca_balao(int px,int largura,int py,int altura){
     Mix_Chunk *som_beep = NULL;
     Mix_Chunk *pum = NULL;
    
      som_beep = Mix_LoadWAV( "sons/futurebeep.wav" );
      pum=Mix_LoadWAV( "sons/futurebeep.wav" );

      
       if( (px-largura+25<x && px+largura-25>x) && (py-altura+10<y && py+altura-10>y ))    {
              if(status!=1){
              Mix_PlayChannel( 0, som_beep, 0 );
              
              }
              status=1;
              
               
                 return 1;
                 }
                 else return 0;        
        }

