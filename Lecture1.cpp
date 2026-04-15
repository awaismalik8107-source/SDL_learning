#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 768;
//Defining screen width 

int main(int argc, char *args[])//compiler testing 
//Defualt argument

{
    SDL_Window *window = NULL;
    //Pointers for window 
    SDL_Surface *surface = NULL;
    //error handler for initiation 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //error handleing 
        std::cout << "SDL cannot be initialized: " << SDL_GetError() << std::endl;
    }
    else 
    {
        //defining window 
        //syntax screen title ,x and y position on opening ,than screen with and height 
        //than 
        window = SDL_CreateWindow(
            "SDL Lesson1",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        //error handling 
        if (window == NULL)
        {
            std::cout << "SDL cannot create window: " << SDL_GetError() << std::endl;
        }

        else
        {
            //Surface define
            surface = SDL_GetWindowSurface(window);
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
            SDL_UpdateWindowSurface(window);

            // SDL_Delay() will not draw the window properly
            bool loop = true;
            //window loop
            while (loop) {
                SDL_Event e;
                //Inside the SDL_event.h 
                /*
                use to get event from event quenue 
                throuh Poll event  
                event are basically the keyboard and mouse input
                */
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        //cross
                        //as soon as loop false it quites 
                        loop = false;
                    }
                    //later
                //     if (e.type == SDL_KEYDOWN) {

                //     if (e.key.keysym.sym == SDLK_a) {
                // std::cout << "A key pressed!" << std::endl;
                // }

                // if (e.key.keysym.sym == SDLK_w) {
                //     std::cout << "W key pressed!" << std::endl;
                //     }
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
    }
;