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


int dots[2][30];
char tags[30];

//Draws and Recolors (if necessary) the Barracks in three
//different sizes (dependent on each district which is
//distinguishable via "tag")
void Draw_Barrack(SDL_Renderer *renderer,Sint16 x, Sint16 y, char tag, Uint32 color)
{
    Sint16 r;

    switch(tag)
    {
        case 's':
            r=10;
            break;
        case 'm':
            r=20;
            break;
        case 'l':
            r=30;
            break;
    }


    filledCircleColor(renderer, x, y, r, color);

}



//Reads the coordinates of dots (the location of the barracks)
// from txt file and saves them into an array
void dot_taker(int name, int x, int y, int district)
{
    FILE *dotfile;

    switch(name)
    {
        case 0:
            dotfile = fopen("txtfiles/Dots/Africa_dot-set-list.txt", "r");
            break;

        case 1:
            dotfile = fopen("txtfiles/Dots/Asia_dot-set-list.txt", "r");
            break;

        case 2:
            dotfile = fopen("txtfiles/Dots/Australia_dot-set-list.txt", "r");
            break;
    }


    Sint16 neededpush_x =x, neededpush_y =y;

    for(int i=0;i<district;i++)
    {
        fscanf(dotfile,"%d,", &dots[0][i]);
        dots[0][i]+=neededpush_x;
        fscanf(dotfile ,"%d,", &dots[1][i]);
        dots[1][i]+=neededpush_y;
    }
}

//Reads the tags from txt file (which are necessary for
//drawing the barracks)
void tag_taker(int name, int district)
{
    FILE *tagfile;

    switch(name)
    {
        case 0:
            tagfile=fopen("txtfiles/Tags/Africa.txt","r");
            break;

        case 1:
            tagfile=fopen("txtfiles/Tags/Asia.txt","r");
            break;

        case 2:
            tagfile=fopen("txtfiles/Tags/Australia.txt","r");
            break;
    }

    for(int i=0;i<district;i++)
    {
        fscanf(tagfile, "%c", &tags[i]);
    }
}



//returns 0(Africa),1(Asia),2(Australia)
//The program uses the numbers to load the correct image
//and set the right basic datas
int MenuDefaultmaps(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    const int menunum=3;

    int Y_TEMP=100;
    char *label[menunum];
    label[0]="Africa";
    label[1]="Asia";
    label[2]="Australia";

    bool select[menunum];
    select[0]=0;
    select[1]=0;
    select[2]=0;

    SDL_Rect buttons[menunum];

    for(int i=0;i<menunum;i++)
    {
        stringColor(renderer,(SCREEN_WIDTH/2)-50,Y_TEMP+((SCREEN_HEIGHT-500)/6),label[i],0xffffffff);

        buttons[i].x=(SCREEN_WIDTH-400)/3;
        buttons[i].y=Y_TEMP;
        buttons[i].h=(SCREEN_HEIGHT-500)/3;
        buttons[i].w=500;

        Y_TEMP+=(((SCREEN_HEIGHT-500)/3)+50);

    }

    SDL_RenderPresent(renderer);

    SDL_Event event;
    int x,y;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (int i=0;i<menunum;i++)
                    {
                        if (x>=buttons[i].x && x<=buttons[i].x + buttons[i].w && y>=buttons[i].y && y<=buttons[i].y + buttons[i].h)
                        {
                            if (!select[i])
                            {
                                select[i] = 1;
                                stringColor(renderer,(SCREEN_WIDTH/2)-50,buttons[i].y+((SCREEN_HEIGHT-500)/6),label[i],0xff0000ff);
                            }

                        }
                        else
                        {
                            if (select[i])
                            {
                                select[i]=0;
                                stringColor(renderer, (SCREEN_WIDTH/2)-50, buttons[i].y+((SCREEN_HEIGHT-500)/6), label[i], 0xffffffff);
                            }

                        }

                    }
                    SDL_RenderPresent(renderer);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i=0;i<menunum;i++)
                    {
                        if(x>=buttons[i].x && x<=buttons[i].x + buttons[i].w && y>=buttons[i].y && y<=buttons[i].y + buttons[i].h)
                        {
                            return i;
                        }
                    }
                    break;

            }
        }
    }

}
 int StartMenu(SDL_Renderer *renderer)
 {
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
     SDL_RenderClear(renderer);

 }





















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
    //
   //

    // the rectangle area you wanna put the image
    //
   //





    Uint32 color = 0xffffffff;

    int check_do_once=0;

    SDL_Texture *sdlTexture;

    int x,y,w,h;
    int district;

    int name=MenuDefaultmaps(sdlRenderer);
    switch(name)
    {
        case 0:
            sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Africa.bmp");
            x=188;
            y=14;
            w=623;
            h=772;
            district=15;
            break;

        case 1:
            sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Asia.bmp");
            x=10;
            y=53;
            w=1000;
            h=693;
            district=14;
            break;

        case 2:
            sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Australia.bmp");
            x=21;
            y=33;
            w=957;
            h=734;
            district=15;
            break;
    }
    SDL_Rect texture_rect={.x=x, .y=y, .w=w, .h=h};

    while (shallExit == SDL_FALSE)
    {
        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(sdlRenderer);

        SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);



        if(check_do_once==0)
        {
            check_do_once++;
            dot_taker(name,x,y,district);
            tag_taker(name,district);
        }

        for(int i=0;i<15;i++)
        {
            Draw_Barrack(sdlRenderer,dots[0][i],dots[1][i],tags[i],color);
        }

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
        SDL_Delay(1 / FPS);

    }

    return 0;

}