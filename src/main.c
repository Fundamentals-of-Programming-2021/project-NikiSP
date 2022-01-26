#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>

const int FPS = 60;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

SDL_Texture *getImageTexture(SDL_Renderer *sdlRenderer, char *image_path) {
    SDL_Surface *image = SDL_LoadBMP(image_path);

    /* Let the user know if the file failed to load */
    if (!image) {
        printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
        return 0;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, image);

    SDL_FreeSurface(image);
    image = NULL;

    return texture;
}


int main()
{
    SDL_bool shallExit = SDL_FALSE;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("State.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    // the texture of the image
    // It's "../me.bmp" because the relative path is based on "cmake-build-debug" path
   // SDL_Texture *sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Africa.bmp");
    SDL_Texture *sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Asia.bmp");
    // the rectangle area you wanna put the image
   // SDL_Rect texture_rect = {.x=188, .y=0, .w=623, .h=772};
    SDL_Rect texture_rect = {.x=0, .y=53, .w=1000, .h=693};

    while (shallExit == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);

        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);




        // listen for key events
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent))
        {
            switch (sdlEvent.type)
            {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }

        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
    }

    return 0;

}