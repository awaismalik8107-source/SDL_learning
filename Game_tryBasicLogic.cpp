#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <stdlib.h>
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 768;
//Defining screen width 

class ground{
    public:
    SDL_Rect surface;
    static int  number;
    
    ground()
    {
        surface.x=0;
        surface.y=400;
        surface.h=200;
        surface.w=800;
        number+=1;

    }
    ground(int x,int y,int h,int w){
        this->surface.x=x;
        this->surface.y=y;
        this->surface.h=h;
        this->surface.w=w;
        number+=1;
    }

    void distroyer();
   

    ~ground()
    {
        number-=1;
        // std::cout<<"The ground name "<<number<<"Have been distroyed"<<std::endl;
        
    }
};

 int ground::number=0;
 void ground::distroyer(){
     {
        if(surface.x==-50)
        {
            this->~ground();
        }
    }
 }







//new generator
void clear();
bool generative(const ground &g1,int y,int h,int w);
ground* newGround(ground* g1, int& size);

int main(int argc, char *args[])//compiler testing 
//Defualt argument

{

    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Renderer* renderer = NULL;
    //score;
    int score=0;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL cannot be initialized: " << SDL_GetError() << std::endl;
    }
    else 
    {
        window = SDL_CreateWindow(
            "SDL Lesson1",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            std::cout << "SDL cannot create window: " << SDL_GetError() << std::endl;
        }

        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            surface = SDL_GetWindowSurface(window);

            bool loop = true;
            int size = 1;
            int i=0;
            int cameraX = 0;
            float speed = 2.0f;

            ground* g1 = new ground[size];

            while (loop) 
            {
                i+=1;
                score+=1;

                if(i%10==0)
                {
                    g1=newGround(g1,size);
                }

                SDL_Event e;

                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        loop = false;
                    }
                }
                if(i%6==0)
                {   
                    score +=1;
                    
                    if((int)speed==10)
                    {
                        std::cout << "Score: " << score << (((int)speed >= 10) ? " | MAX SPEED" : "") << "      \r" << std::flush;
                    }
                    else
                    speed+=0.05f;
                    std::cout << "Score: " << score << "\r" << std::flush;
                 
                    // std::cout << "Speed: " << speed << "\r" << std::flush;
                }

                // std::cout<<score<<std::endl;
                


                SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
                SDL_RenderClear(renderer);

                cameraX += (int)speed;

                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // brown color

                for(int j=0;j<size;j++)
                {
                    SDL_Rect temp = g1[j].surface;
                    temp.x -= cameraX;
                    SDL_RenderFillRect(renderer, &temp);
                }

                SDL_RenderPresent(renderer);

                SDL_Delay(16); // ~60 FPS
                // clear();
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

bool generative(const ground &g1, int y, int h, int w)
{
    int ydif = g1.surface.y - y;

    if (ydif > -60 && ydif < 20 && h > 310 && h < 430 && w > 640 && w < 850)
        return false;

    return true;
}
//packages
ground* newGround(ground* g1, int& size)
{
    int tempx, tempy, temph, tempw;
    int lastRight = g1[size-1].surface.x + g1[size-1].surface.w;

    std::random_device rd;
    std::mt19937 gen(rd());

    bool check = true;

    while (check)
    {
        //from chat gpt

        std::uniform_int_distribution<> distX(lastRight+200, lastRight+300);
        std::uniform_int_distribution<> distY(0, 600);
        std::uniform_int_distribution<> distW(500, 800);
        std::uniform_int_distribution<> distH(400, 600);

        tempx = distX(gen);
        tempy = distY(gen);
        tempw = distW(gen);
        temph = distH(gen);

        check = generative(g1[size - 1], tempy, temph, tempw);
    }

    ground* temp = new ground[size + 1];

    for (int i = 0; i < size; i++)
    {
        temp[i] = g1[i];
    }

    temp[size] = ground(tempx, tempy, temph, tempw);

    delete[] g1;

    size++;

    return temp;
}
void clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}