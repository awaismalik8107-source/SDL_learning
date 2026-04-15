#include <SDL2/SDL.h>
#include <iostream>

// Screen constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

// Global variables for simplicity (common in early SDL lessons)
SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gStretchedSurface = nullptr;

/**
 * Initializes SDL, creates the window, and grabs the surface.
 */
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Lesson 02 - Refactored", 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Get window surface
    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

/**
 * Loads the BMP image.
 */
bool loadMedia() {
    // Path to your image
    const char* path = "img/star.bmp";
    gStretchedSurface = SDL_LoadBMP(path);
    
    if (gStretchedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/**
 * Cleans up memory and shuts down SDL.
 */
void close() {
    // Deallocate surface
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = nullptr;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
    } else {
        // Load media
        if (!loadMedia()) {
            std::cerr << "Failed to load media!" << std::endl;
        } else {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // While application is running
            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // 1. Clear/Fill the background (Red)
                SDL_FillRect(gScreenSurface, nullptr, SDL_MapRGB(gScreenSurface->format, 255, 0, 0));

                // 2. Apply the image
                // Use a Rect if you want to place it somewhere specific, 
                // otherwise NULL blits to (0,0)
                SDL_BlitSurface(gStretchedSurface, nullptr, gScreenSurface, nullptr);

                // 3. Update the surface
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}