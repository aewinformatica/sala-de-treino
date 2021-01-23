#include "onofre.h"


const int onoff_largura = 90;
const int onoff_altura = 10;


Mix_Chunk *som01 = NULL;

Mix_Music *som02 = NULL;

TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0xF0, 0xFF, 0xF0 };

     
//The direction status of the stick figure
const int Minhoca_RIGHT = 0;
const int Minhoca_LEFT = 1;
const int Minhoca_LEFT_UP = 2;
const int Minhoca_RIGHT_UP = 3;
//The surfaces




SDL_Surface *sorte = NULL;
SDL_Surface *fundo = NULL;
SDL_Surface *frente = NULL;
SDL_Surface *minhoca = NULL;
SDL_Surface *minhoca2 = NULL;
SDL_Surface *seconds = NULL;

SDL_Surface *onanda01 = NULL;
SDL_Surface *onanda02 = NULL;
SDL_Surface *onanda03 = NULL;
SDL_Surface *onanda04 = NULL;
SDL_Surface *onanda05 = NULL;
SDL_Surface *onanda06 = NULL;
SDL_Surface *onanda07 = NULL;
SDL_Surface *onanda08 = NULL;
SDL_Surface *onanda09 = NULL;
SDL_Surface *onanda10 = NULL;

SDL_Surface *onparado01 = NULL;
SDL_Surface *onparado02 = NULL;
SDL_Surface *onparado03 = NULL;
SDL_Surface *onparado04 = NULL;
SDL_Surface *onparado05 = NULL;

SDL_Surface *onpula01 = NULL;
SDL_Surface *onpula02 = NULL;
SDL_Surface *onpula03 = NULL;
SDL_Surface *onpula04 = NULL;
SDL_Surface *onpula05 = NULL;
SDL_Surface *onpula06 = NULL;
SDL_Surface *onpula07 = NULL;
SDL_Surface *onpula08 = NULL;
SDL_Surface *onpula09 = NULL;
SDL_Surface *onpula10 = NULL;


SDL_Surface *ondash01 = NULL;
SDL_Surface *ondash02 = NULL;
SDL_Surface *ondash03 = NULL;
SDL_Surface *ondash04 = NULL;


SDL_Surface *onantidash01 = NULL;
SDL_Surface *onantidash02 = NULL;
SDL_Surface *onantidash03 = NULL;
SDL_Surface *onantidash04 = NULL;


//The event structure
SDL_Event event;

//The areas of the sprite sheet

SDL_Rect back[1];







//The timer




void set_clips()
{
     
     
     back[0].x = 0;
     back[0].y = 0;
     back[0].w=1200;
     back[0].h=700;
    //Clip the sprites
   
    
    
    
   
}




bool load_files()
{
    
    //Carrega os sprites
    fundo = load_image("fundo2.png");
    frente = load_image("Camada_frente2.png");
    onanda01= load_image("On_Anda/ONWLK01.png");  
    onanda02= load_image("On_Anda/ONWLK02.png");  
    onanda03= load_image("On_Anda/ONWLK03.png");  
    onanda04= load_image("On_Anda/ONWLK04.png");  
    onanda05= load_image("On_Anda/ONWLK05.png");  
    onanda06= load_image("On_Anda/ONWLK06.png");  
    onanda07= load_image("On_Anda/ONWLK07.png");                            
    onanda08= load_image("On_Anda/ONWLK08.png");  
    onanda09= load_image("On_Anda/ONWLK09.png");  
    onanda10= load_image("On_Anda/ONWLK10.png");  
    
    onparado01=load_image("On_Parado/ONST1.png");    
    onparado02=load_image("On_Parado/ONST2.png");   
    onparado03=load_image("On_Parado/ONST3.png");    
    onparado04=load_image("On_Parado/ONST4.png");    
    onparado04=load_image("On_Parado/ONST5.png");    
    
    onpula01=load_image("On_pula/ONJMP1.png");
    onpula02=load_image("On_pula/ONJMP2.png");
    onpula03=load_image("On_pula/ONJMP3.png");
    onpula04=load_image("On_pula/ONJMP4.png");
    onpula05=load_image("On_pula/ONJMP5.png");
    onpula06=load_image("On_pula/ONJMP6.png");
    onpula07=load_image("On_pula/ONJMP7.png");                        
    onpula08=load_image("On_pula/ONJMP8.png");    
    onpula09=load_image("On_pula/ONJMP9.png");
    onpula10=load_image("On_pula/ONJMP10.png");        
    
    
    ondash01=load_image("On_avanca/ONDASH1.png");
    ondash02=load_image("On_avanca/ONDASH2.png");
    ondash03=load_image("On_avanca/ONDASH3.png");    
    ondash04=load_image("On_avanca/ONDASH4.png");  
    
    
    onantidash01=load_image("On_recua/ONDASHB1.png");
    onantidash02=load_image("On_recua/ONDASHB2.png");
    onantidash03=load_image("On_recua/ONDASHB3.png");    
    onantidash04=load_image("On_recua/ONDASHB4.png");   
    
   font = TTF_OpenFont( "lazy.ttf", 20 );
    //If there was a problem in loading the sprite
    
    if( fundo == NULL )
    {
        return false;    
    }
     if( font == NULL )
    {
        return false;    
    }
    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( minhoca );
//    SDL_FreeSurface( parede );
    SDL_FreeSurface( fundo );
   
    Mix_FreeChunk(som01);
    //Quit SDL
    SDL_Quit();
}

ONOFRE::ONOFRE()
{
    //Initialize movement variables
    offSet = 0;
    posicao = 0;
    posicaoy=0;
    pulo=0;
    sair=0;
    dash=50;
    dash2=0;
    dashini=0;
    antidashini=0;
    fatordash=15;
    y = SCREEN_HEIGHT-130;
    //Initialize animation variables
    frame = 0;
    frame2=12;
    parado=0;
    cont=cont2=cont3=0;
    inverte=1;
    fatorpulo=20;
    pulo_acabou=1;
    status = Minhoca_RIGHT;
}
void ONOFRE::funcao_pulo(int x){
         
     
     if(pulo==0){
           switch(x){
            case 0:                      
            
            auxiliar=y;           
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula01, screen, NULL );
//            SDL_Flip( screen );
           SDL_Delay(30);
//            handle_events();
            move();
            break;
            case 1:
            y-=fatorpulo;
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula02, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            SDL_Delay(30); 
            move();
            break;
            case 2:
            y-=fatorpulo;


           
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula03, screen, NULL );
//            SDL_Flip( screen );
            SDL_Delay(30);
//            handle_events();
            move();
            break;
            case 3:
            y-=fatorpulo;
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula04, screen, NULL );
//            SDL_Flip( screen );
            SDL_Delay(30);
//            handle_events();
            move();
            break;
            case 4:
            y-=fatorpulo;
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula05, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            move();
            SDL_Delay(30);   
            break;
            case 5:         
            y-=fatorpulo;
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula06, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            move();
            y+=fatorpulo;
//            SDL_Delay(70);    
            break;
            case 6:        
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula07, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            move();
//            SDL_Delay(70);
            y+=fatorpulo;
            break;
            case 7:
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula07, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            move();
//            SDL_Delay(70);
            y+=fatorpulo; 
            break;
            case 8:                
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula08, screen, NULL );
//            SDL_Flip( screen );
//            SDL_Delay(70);            
            y+=fatorpulo;
            break;
            case 9:
//            apply_surface(0, 0, fundo, screen,&back[0] );
            apply_surface( offSet, y, onpula01, screen, NULL );
//            SDL_Flip( screen );
//            handle_events();
            move();
            y+=fatorpulo;
//            SDL_Delay(100);    
            y=auxiliar;
            break;
            case 10:
            pulo_acabou=1;
            break;
            default:
              pulo_acabou=1;
                    break;
            }
     
} 
     
     
     }
     
     
void ONOFRE::funcao_dash(int x){
         dashini=1;
        
         
           
           switch(x){
            case 0:                      
            apply_surface( offSet, y, ondash01, screen, NULL );
            SDL_Delay(60);
            move();
            break;
            case 1:
            offSet+=fatordash;
            move();
            apply_surface( offSet, y, ondash02, screen, NULL );
            SDL_Delay(60); 
            
            break;
            case 2:
            offSet+=fatordash;
            move();
            apply_surface( offSet, y, ondash03, screen, NULL );
            SDL_Delay(60);
            
            break;
            case 3:
            offSet+=fatordash;
            move();
            apply_surface( offSet, y, ondash04, screen, NULL );
            SDL_Delay(60);
            dashini=0;
            break;
            default:
            dashini=0;  
            }
     
     }     
     
     
     
void ONOFRE::funcao_antidash(int x){
         antidashini=1;
       if(  SDL_GetTicks() - dash2 < 200){
       antidashini=0;
       return;
       }
           switch(x){
            case 0:                      
            apply_surface( offSet, y, onantidash01, screen, NULL );
            SDL_Delay(60);
            move();
            break;
            case 1:
            offSet-=fatordash;
            move();
            apply_surface( offSet, y, onantidash02, screen, NULL );
            SDL_Delay(60); 
            
            break;
            case 2:
            offSet-=fatordash;
            move();
            apply_surface( offSet, y, onantidash03, screen, NULL );
            SDL_Delay(60);
            
            break;
            case 3:
            offSet-=fatordash;
            move();
            apply_surface( offSet, y, onantidash04, screen, NULL );
            SDL_Delay(60);
            antidashini=0;
            break;
            default:
            antidashini=0;  
            }
     
     }     
     
     
     
void ONOFRE::handle_events()
{
    //If a key was pressed
    
    
    
   
    
    if( event.type == SDL_KEYDOWN )
    {
        //Set the posicao
        switch( event.key.keysym.sym )
        {
                
                
            case SDLK_UP:// posicaoy -= minhoca_altura/2;
            
           if(pulo_acabou==1){
              pulo_acabou=0;
              pulo=0;
              fatorpulo=20; 
              }
            break;
            
            case SDLK_DOWN: // posicaoy += minhoca_altura/2; 
            break; 
            
            case SDLK_RIGHT: 
            posicao += deslocamentox;
            
            dash=SDL_GetTicks();
            
            if((dash-dash2)<200 && pulo_acabou==1){
               dashini=1; 
             }
                                 
             break;
            case SDLK_LEFT: 
            posicao -= deslocamentox;
            antidash=SDL_GetTicks();
            
            if((antidash-antidash2)<200 && pulo_acabou==1){
               antidashini=1; 
             }
            
              break;

          
                break;
            case SDLK_1:
             Mix_PlayChannel( 0, som01, 0 );
             
                    
                    break;
           case SDLK_2:
             Mix_PlayChannel( -1,som01, 0 );
                    
                    break;
          
                
            
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the posicao
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: posicao -= deslocamentox;
              
              if((dash-dash2)<200 && (pulo_acabou==1)){
               dashini=1; 
             }
             dash2=SDL_GetTicks();
             break;
            
            case SDLK_UP:
                    if(pulo_acabou==0){
                    fatorpulo=5;
                            } 
                            else fatorpulo=20;                   
                   pulo=0;
                 
                 
                 //posicaoy += minhoca_altura/2; 
            break;
            case SDLK_DOWN: //posicaoy-= minhoca_altura/2;
             break; 
            
            case SDLK_LEFT: posicao += deslocamentox;
             if((antidash-antidash2)<200 && pulo_acabou==1){
               antidashini=1; 
             }
             antidash2=SDL_GetTicks();
             break;
             
                break;
        }
    }

}

void ONOFRE::move()
{
    //Move
    offSet += posicao;
    y+=posicaoy;
    //Keep the stick figure in bounds
    if( ( offSet < 0 ) || ( offSet + onoff_largura > SCREEN_WIDTH ) )
    {
        offSet -= posicao;    
    }
    if(offSet + onoff_largura > SCREEN_WIDTH)
    offSet=SCREEN_WIDTH-onoff_largura;
    if(offSet < 0)
    offSet=0;
    
   if(y > SCREEN_HEIGHT -130 || y< 0)
    
    y-=posicaoy ;
    
    
}

void ONOFRE::show()
{
     
    if(dashini==1 || antidashini==1 )
    return;    
        //If Minhoca is moving left
    if( posicao < 0 )
    {
        //Set the animation to left
        status = Minhoca_LEFT;
        
        //Move to the next frame in the animation
        frame++;
        frame2++;
        parado=0;
    }
    //If Minhoca is moving right
    else if ( posicao > 0 )
    {
        //Set the animation to right
        status = Minhoca_RIGHT;
        
        //Move to the next frame in the animation
        frame++;
        frame2++;
        parado=0;
    } else 
    {
        //Restart the animation
        frame = 0;
        frame2=-1;
        parado=parado+inverte;
        
            
    }
    
    
    //Loop the animation
    if( frame >= 4 )
    {
        frame = 0;
    }
     if( frame2 >= 10 )
    {
        frame2 = 0;
    }
    
    if(parado>3)
    {
                
          
          apply_surface( offSet, y, onparado04, screen, NULL );
          inverte=inverte*(-1);       
          
                 }
    if(parado<=0)
    {
            parado=0;
                
          inverte=inverte*(-1);       
          
                 }             
                 
    if(posicao==0)
    {
      if(parado==0)
      apply_surface( offSet, y, onparado01, screen, NULL );
      if(parado==1)
      apply_surface( offSet, y, onparado02, screen, NULL );
      if(parado==2)
      apply_surface( offSet, y, onparado03, screen, NULL );
      if(parado==3)
      apply_surface( offSet, y, onparado04, screen, NULL ); 
      if(parado==4)
      apply_surface( offSet, y, onparado05, screen, NULL );       
      
                  
    }
    
     
    //Show the stick figure
    if( status == Minhoca_RIGHT )
    {
       
      if(frame2==0)
      apply_surface( offSet, y, onanda01, screen, NULL );
      if(frame2==1)
      apply_surface( offSet, y, onanda02, screen, NULL );
      if(frame2==2)
      apply_surface( offSet, y, onanda03, screen, NULL );
      if(frame2==3)
      apply_surface( offSet, y, onanda04, screen, NULL );
      if(frame2==4)
      apply_surface( offSet, y, onanda05, screen, NULL );
      if(frame2==5)
      apply_surface( offSet, y, onanda06, screen, NULL );
      if(frame2==6)
      apply_surface( offSet, y, onanda07, screen, NULL );
      if(frame2==7)
      apply_surface( offSet, y, onanda08, screen, NULL );
      if(frame2==8)
      apply_surface( offSet, y, onanda09, screen, NULL );
      if(frame2==9)
      apply_surface( offSet, y, onanda10, screen, NULL );
     
    }  
    else if( status == Minhoca_LEFT )
    {
      if(frame2==0)
      apply_surface( offSet, y, onanda09, screen, NULL );
      if(frame2==1)
      apply_surface( offSet, y, onanda08, screen, NULL );
      if(frame2==2)
      apply_surface( offSet, y, onanda07, screen, NULL );
      if(frame2==3)
      apply_surface( offSet, y, onanda06, screen, NULL );
      if(frame2==4)
      apply_surface( offSet, y, onanda05, screen, NULL );
      if(frame2==5)
      apply_surface( offSet, y, onanda04, screen, NULL );
      if(frame2==6)
      apply_surface( offSet, y, onanda03, screen, NULL );
      if(frame2==7)
      apply_surface( offSet, y, onanda02, screen, NULL );
      if(frame2==8)
      apply_surface( offSet, y, onanda01, screen, NULL );
      if(frame2==9)
      apply_surface( offSet, y, onanda10, screen, NULL );
    }
}
