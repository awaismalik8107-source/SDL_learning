#include <SDL2/SDL.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include<iostream>

int main(int argc, char ** args)
{   
    //pointer set  to null
    SDL_Surface* winSurface=NULL;
    SDL_Window* window=NULL;
    
    //need to use the parameter 

    //Initialize SDL.SDL_Init will return -1 if it fails
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout<<"Error initializing SDL:" <<SDL_GetError()<<std::endl;
       //end program
        system("Pause");
        return 1;
    }

    //get Surface from the window 
    window=SDL_CreateWindow("Example no 1", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1280,720,SDL_WINDOW_SHOWN);

    //Make Sure creating the window succeded 
    if(!window)
    {
        std::cout<<"ERROR Creating WINDOW"<<SDL_GetError()<<std::endl;
        system("pause");
        return 1;
    }

    //GET the surface from the window
    winSurface=SDL_GetWindowSurface(window);
    // Make sure getting the surface succeeded
    if(!winSurface)
    {
        std::cout<<"ERROR getting Surface:"<<SDL_GetError()<<std::endl;

        system("pause");
        return 1;
    }

    SDL_FillRect(winSurface,NULL,SDL_MapRGB (winSurface->format,255,255,255));
    //update window after fill
    SDL_UpdateWindowSurface( window );

    system("pause");

    SDL_DestroyWindow( window );

    SDL_Quit();

    return 0;

}