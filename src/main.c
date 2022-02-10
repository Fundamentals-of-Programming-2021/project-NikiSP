#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

//default variables
const int FPS = 60;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

Uint32 playerscolors[1000];
int attack[30][10][10000];

int dots[2][30];
char tags[30];
int soldierlimit[30];
int select_dots[2][30];
char count[5000];
int counter[30];
time_t begintime;

int checkattack=0;
int start=-1;
int end=-1;


double soldiers_coordinate[10][2][10000];


int temp[30][10][1];

int currentattackumber;
char username[1000];

int equal(char temp[])
{
    int i=0;
    while(username[i]!='\0')
    {
        if(username[i]!=temp[i])
        {
            return 0;
        }
        i++;
    }
if(temp[i]!='\0'&&temp[i]!=' ')
{
    return 0;
}

return 1;

}


int checkusername()
{
    FILE *ptr= fopen("txtfiles/ScoreBoard/Usernames.txt","r+");
        char x[1000];
for(int i=0;i<1000;i++)
{
    x[i]='\0';
}
        while (fscanf(ptr, " %1023s", x) == 1)
        {
            if(equal(x))
            {
                return 1;
            }
        }

        fprintf(ptr,username);
        fprintf(ptr," ");
        fclose(ptr);
        return 0;

}

void getusername(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);



    int length=0;
    SDL_Event event;
    SDL_bool Exit=SDL_FALSE;

    SDL_Rect typebox;
    typebox.x=SCREEN_WIDTH/2-100;
    typebox.y=SCREEN_HEIGHT/2;
    typebox.h=60;
    typebox.w=SCREEN_WIDTH/5;

    while(!Exit)
    {


        while(SDL_PollEvent(&event))
        {
            stringColor(renderer,SCREEN_WIDTH/2-100,typebox.y-50,"Please Enter Your Name", 0xffffffff);

            switch(event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_RETURN || event.key.keysym.sym==SDLK_KP_ENTER) {
                        Exit = SDL_TRUE;
                    }else if (event.key.keysym.sym==SDLK_BACKSPACE && length!=0)
                    {
                        SDL_RenderClear(renderer);
                        length--;
                        username[length]='\0';
                        stringColor(renderer,SCREEN_WIDTH/2-100,typebox.y-50,"Please Enter Your Name", 0xffffffff);
                        stringColor(renderer,typebox.x,typebox.y,username,0xff0000ff);
                    }
                    break;

                case SDL_TEXTINPUT:
                    username[length]=*event.text.text;
                    length++;
                    stringColor(renderer,typebox.x,typebox.y,username,0xff0000ff);
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

}






int isitthere(int num,double x,double y)
{
    int x1,y1,r;
    x1 = dots[0][num];
    y1 = dots[1][num];
    switch (tags[num])
    {
        case 's':
            r = 10;
            break;

        case 'm':
            r = 20;
            break;

        case 'l':
            r = 30;
            break;
    }

    if ((((x - x1) * (x - x1)) + ((y - y1) * (y - y1))) <= (r * r))
    {
        return 1;
    }
    return 0;
}


void check_destination(int end, int playernum)
{


    if(!select_dots[0][end]||(counter[end]==0))
    {
        select_dots[0][end]=1;
        select_dots[1][end]=playernum;

    }
    else
    {
        if(select_dots[1][end]==playernum)
        {
            counter[end]++;

        }
        else
        {
            counter[end]--;
        }
    }



}

int next_soldier(int x, int y, int start)
{
    int overall=60;
    switch(tags[start])
    {
        case 's':
            overall+=10;
            break;

        case 'm':
            overall+=20;
            break;

        case 'l':
            overall+=30;
            break;
    }

    int currentdistance=((dots[0][start]-x)*(dots[0][start]-x))+((dots[1][start]-y)*(dots[1][start]-y));
    if(currentdistance<0)
    {
        currentdistance*=-1;
    }

    if(currentdistance>=overall)
    {
        return 1;

    }

    return 0;

}





int attackcount[30];

int tempcurrentstate[30][10];

///////////////
#define playercount 5

int do_once[playercount][10];
 int attack_soldiercount[playercount][10];
 bool attack_status[playercount][10];
 int attackcount_mp=0;
 int attack_startingpoint[playercount][10];
 int attack_endingpoint[playercount][10];
 double soldiers_coordinates[10][2][10000];
 int startdraw[30][10];
 int eliminatefurthur[playercount][10];

double tan1[playercount][10];
double change[playercount][10];
double sign[playercount][10];
int checkreset=0;

/////////////


int attack_function(int attacknum,int attackernum, SDL_Renderer *sdlRenderer )
{
    if(attack_soldiercount[attackernum][attacknum]<=0)
    {
        attack_status[attackernum][attacknum]=0;
        do_once[attackernum][attacknum]=0;
        return 1;
    }

    if(!do_once[attackernum][attacknum])
    {

        do_once[attackernum][attacknum]=1;

        tan1[attackernum][attacknum]=( ((double)(dots[1][attack_endingpoint[attackernum][attacknum]]) - (double)(dots[1][attack_startingpoint[attackernum][attacknum]])) /    ((double) (dots[0][attack_endingpoint[attackernum][attacknum]]) - (double)(dots[0][attack_startingpoint[attackernum][attacknum]])));

        if(tan1[attackernum][attacknum]>0)
        {
            if(dots[0][attack_endingpoint[attackernum][attacknum]]>dots[0][attack_startingpoint[attackernum][attacknum]])
            {
                change[attackernum][attacknum]=2/(sqrt((tan1[attackernum][attacknum]*tan1[attackernum][attacknum])+1));
                sign[attackernum][attacknum]=1;
            }
            else
            {
                change[attackernum][attacknum]=-2/(sqrt((tan1[attackernum][attacknum]*tan1[attackernum][attacknum])+1));
                sign[attackernum][attacknum]=1;
            }

        }
        else
        {
            if(dots[0][attack_endingpoint[attackernum][attacknum]]>dots[0][attack_startingpoint[attackernum][attacknum]])
            {
                change[attackernum][attacknum]=2/(sqrt((tan1[attackernum][attacknum]*tan1[attackernum][attacknum])+1));
                sign[attackernum][attacknum]=1;
            }
            else
            {
                change[attackernum][attacknum]=-2/(sqrt((tan1[attackernum][attacknum]*tan1[attackernum][attacknum])+1));
                sign[attackernum][attacknum]=1;
            }

        }

        for(int i=0;i<attack_soldiercount[attackernum][attacknum];i++)
        {

            soldiers_coordinates[attacknum][0][i]=(double )dots[0][attack_startingpoint[attackernum][attacknum]];
            soldiers_coordinates[attacknum][1][i]=(double) dots[1][attack_startingpoint[attackernum][attacknum]];

        }

        eliminatefurthur[attackernum][attacknum]=0;
        startdraw[attackernum][attacknum]=1;

    }

    int i;
    for(i=eliminatefurthur[attackernum][attacknum];i<startdraw[attackernum][attacknum];i++)
    {

        if(isitthere(attack_endingpoint[attackernum][attacknum],soldiers_coordinates[attacknum][0][i],soldiers_coordinates[attacknum][1][i]))
        {
            check_destination(attack_endingpoint[attackernum][attacknum],attackernum);
            attack_soldiercount[attackernum][attacknum]--;
            eliminatefurthur[attackernum][attacknum]++;
        }


        filledCircleColor(sdlRenderer, soldiers_coordinates[attacknum][0][i],soldiers_coordinates[attacknum][1][i],5, playerscolors[attackernum]);



        if(dots[0][attack_startingpoint[attackernum][attacknum]]!=dots[0][attack_endingpoint[attackernum][attacknum]])
        {
            soldiers_coordinates[attacknum][0][i]+=change[attackernum][attacknum];
            soldiers_coordinates[attacknum][1][i]+=((double)(sign[attackernum][attacknum]*change[attackernum][attacknum]*tan1[attackernum][attacknum]));

        }

        else
        {
            if(dots[1][attack_startingpoint[attackernum][attacknum]]>dots[1][attack_endingpoint[attackernum][attacknum]])
                soldiers_coordinates[attacknum][0][i]-=2;
            else
                soldiers_coordinates[attacknum][0][i]+=2;
        }

    }

    i--;

    if((startdraw[attackernum][attacknum]<attack_soldiercount[attackernum][attacknum])&&next_soldier(soldiers_coordinates[attacknum][0][i],soldiers_coordinates[attacknum][1][i],attack_startingpoint[attackernum][attacknum]))
    {
        startdraw[attackernum][attacknum]++;
        counter[attack_startingpoint[attackernum][attacknum]]--;
    }


return 0;

}










/*
void attack_func(int attackernum, int target[][10][1] , SDL_Renderer *sdlRenderer)
{
    for(int j=0;j<attackcount[attackernum];j++)
    {
            if(!do_once[j][attackernum])
            {
                temp[attackernum][j][0]=checkattack;
                do_once[j][attackernum]=1;

                tan1=(((double)(dots[1][end]) - (double)(dots[1][start])) /(double)((dots[0][end]) - (double)(dots[0][start])));

                if(tan>0)
                {
                    if(dots[0][end]>dots[0][start])
                    {
                        change=1;
                        sign=1;
                    }
                    else
                    {
                        change=-1;
                        sign=1;
                    }

                }
                else
                {
                    if(dots[0][end]>dots[0][start])
                    {
                        change=1;
                        sign=1;
                    }
                    else
                    {
                        change=-1;
                        sign=1;
                    }

                }

                for(int i=0;i<temp[attackernum][j][0];i++)
                {
                    soldiers_coordinate[j][0][i]=dots[0][start];
                    soldiers_coordinate[j][1][i]=dots[1][start];
                    attack[attackernum][j][i]=1;
                }
                checkattack=0;
            }


        for(int i=0;i<temp[attackernum][j][0];i++)
        {
            int reached_destination=isitthere(target[attackernum][j][0],soldiers_coordinate[j][0][i],soldiers_coordinate[j][1][i]);
            if(reached_destination)
            {
                check_destination(start,end,0);
                attack[attackernum][j][i]=0;
            }

            if(attack[attackernum][j][i]!=0)
            {                                                                                                //REMEMBER TO CHANGE THE COLOR
                filledCircleColor(sdlRenderer,(Sint16) soldiers_coordinate[0][i],(Sint16)soldiers_coordinate[1][i],5, playerscolors[attackernum]);

            }
            if(dots[0][start]!=dots[0][end])
            {
                soldiers_coordinate[j][0][i] += (change);
                soldiers_coordinate[j][1][i] += ((sign*(change)) * tan1);

            }
            if(dots[0][start]==dots[0][end])
            {
                soldiers_coordinate[j][1][i]+=1;
            }

        }

    }


}
*/




int RandomNumber(int start, int end)
{

    srand(time(0));
    return ((rand()%(end-start+1))+start);

}


struct potions
{               //playersnum
    bool is_on;
    bool is_onplace;

    int x;
    int y;

    Uint32 color;


};


int ifpotion(struct potions potion[4])
{
    for(int i=0;i<4;i++)
    {
        if(potion[i].is_onplace)
        {
            return 0;
        }
    }




    int Random= RandomNumber(0,1000);
    time_t now=time(NULL);

    if((Random%23==0)||((now-begintime)>20))
    {
        begintime=time(NULL);
        switch(Random%4)
        {
            case 0:
                return 1;
                break;

            case 1:
                return 2;
                break;

            case 2:
                return 3;
                break;

            case 3:
                return 4;
                break;
        }
    }

    return 0;
}


















struct potions findrandomspot(int district)
{
    int a=RandomNumber(0,district-1);
    int b;
    while(1)
    {
        b=RandomNumber(0,district-1);
        if(b!=a)
        {
            break;
        }
    }

    struct potions temp;

    int Random=RandomNumber(2,6);


            temp.x=(dots[0][a]+dots[0][b])/Random;
            temp.y=(dots[1][a]+dots[1][b])/Random;



    return temp;

}









void RandomMap(int *district,int District)
{


    int num;
    int check=0;
    *district=District;
    // SetTheDots;

    for(int i=0;i<District;i++)
    {
        num= RandomNumber(0,930);
        for(int j=0;j<i;j++)
        {
            if(num==dots[0][j]&&((num-dots[0][j]>50)||(dots[0][j]-num)>50))
            {
                check++;
                break;
            }
        }

        if(check!=0)
        {
            i--;
            check=0;
        }
        dots[0][i]=num;

    }

    for(int i=0;i<District;i++)
    {
        num= RandomNumber(0,730);
        for(int j=0;j<i;j++)
        {
            if(num==dots[1][j]&&((num-dots[1][j]>50)||(dots[1][j]-num)>50))
            {
                check++;
                break;
            }
        }

        if(check!=0)
        {
            i--;
            check=0;
        }
        dots[1][i]=num;

    }

    //Set The Tags
    for(int i=0;i<District;i++)
    {
        switch(RandomNumber(0,10000)%3)
        {
            case 0:
                tags[i]='s';
                break;

            case 1:
                tags[i]='m';
                break;

            case 2:
                tags[i]='l';
                break;
        }
    }

     //Set the players Starting Point
     for(int i=0;i<2/*Playercount*/;i++)
     {
         int num;
         num= RandomNumber(0,District);

             if(select_dots[0][num]==1)
             {
                 i--;
                 continue;
             }

         select_dots[0][i]=1;
         select_dots[1][i]=i;

     }





}






int soldierleft(int player_count,int temp[][10][0], int attack[][10][1])
{
    for(int i=0;i<player_count;i++)
    {
        for(int j=0;j<attackcount[i];j++)
        {
            for(int k=0;k<temp[i][j][0];k++)
            {
                if(attack[i][j][k])
                {
                    return 1;
                }
            }

        }

    }
return 0;
}











//Checks if the chosen area is a barrack in tho modes

//Start mode (tag='s') :
//To define whether the user has clicked on one of his/her barracks
//Returns the number of that barrack
//Returns 0 if the user has not clicked on one of his/her barracks

//Target mode (tag='t')
//To define whether the user has chosen an attackable part of map (barracks)
//Returns the number of that barrack
//Returns 0 if the chosen area is not attackable

int inthecircle(char tag,int x, int y, int district, int select_dots[][30]) {
    int x1, y1, r;
    int C;
    if (tag == 's')
    {
            for (int i = 0; i < district; i++)
            {
                if (select_dots[1][i] == 0)
                {

                    x1 = dots[0][i];
                    y1 = dots[1][i];
                    C = i;
                    switch (tags[i])
                    {
                        case 's':
                            r = 10;
                            break;

                        case 'm':
                            r = 20;
                            break;

                        case 'l':
                            r = 30;
                            break;
                    }


                    if ((((x - x1) * (x - x1)) + ((y - y1) * (y - y1))) <= (r * r))
                    {
                        return C + 1;
                    }

                }
            }
    }
    if(tag=='t')
    {
        for (int i = 0; i < district; i++)
        {
                x1 = dots[0][i];
                y1 = dots[1][i];
                C = i;
                switch (tags[i])
                {
                    case 's':
                        r = 10;
                        break;

                    case 'm':
                        r = 20;
                        break;

                    case 'l':
                        r = 30;
                        break;
                }


                if ((((x - x1) * (x - x1)) + ((y - y1) * (y - y1))) <= (r * r))
                {
                    return C + 1;
                }

        }

    }

       return 0;
}





//Draws and Recolors (if necessary) the Barracks in three
//different sizes (dependent on each district which is
//distinguishable via "tag")
void Draw_Barrack(SDL_Renderer *renderer,int num,Sint16 x, Sint16 y, char tag, Uint32 color)
{
    Sint16 r;

    switch(tag)
    {
        case 's':
            r=10;
            soldierlimit[num]=30;
            break;
        case 'm':
            r=20;
            soldierlimit[num]=40;
            break;
        case 'l':
            r=30;
            soldierlimit[num]=50;
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

    const int menunum=4;

    int Y_TEMP=100;
    char *label[menunum];
    label[0]="Africa";
    label[1]="Asia";
    label[2]="Australia";
    label[3]="Random Map";

    bool select[menunum];
    select[0]=0;
    select[1]=0;
    select[2]=0;

    SDL_Rect buttons[menunum];

    for(int i=0;i<menunum;i++)
    {
        stringColor(renderer,(SCREEN_WIDTH/2)-50,Y_TEMP+(((SCREEN_HEIGHT-200)-((menunum-1)*50))/(menunum*2)),label[i],0xffffffff);

        buttons[i].x=(SCREEN_WIDTH-400)/menunum;
        buttons[i].y=Y_TEMP;
        buttons[i].h=((SCREEN_HEIGHT-200)-((menunum-1)*50))/menunum;
        buttons[i].w=500;

        Y_TEMP+=(buttons[i].h+50);

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
                                stringColor(renderer,(SCREEN_WIDTH/2)-50,buttons[i].y+(((SCREEN_HEIGHT-200)-((menunum-1)*50))/(menunum*2)),label[i],0xff0000ff);
                            }

                        }
                        else
                        {
                            if (select[i])
                            {
                                select[i]=0;
                                stringColor(renderer, (SCREEN_WIDTH/2)-50, buttons[i].y+(((SCREEN_HEIGHT-200)-((menunum-1)*50))/(menunum*2)), label[i], 0xffffffff);
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

//Main Menu
//Returns 0-->New Game
//        1-->Load Game
//        2-->Score Board
//        3-->About
//        4-->Exit

 int StartMenu(SDL_Renderer *renderer)
 {
     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
     SDL_RenderClear(renderer);

     const menunum=5;

     char *label[menunum];

     label[0]="New Game";
     label[1]="Load Game";
     label[2]="Score Board";
     label[3]="About";
     label[4]="Exit";

     int Y_TEMP=50;

     bool select[menunum];
     select[0]=0;
     select[1]=0;
     select[2]=0;
     select[3]=0;
     select[4]=0;

     SDL_Rect buttons[menunum];

     for(int i=0;i<menunum;i++)
     {
         stringColor(renderer,(SCREEN_WIDTH/2)-50,Y_TEMP+(((SCREEN_HEIGHT-100)-((menunum-1)*50))/(menunum*2)),label[i],0xffffffff);

         buttons[i].x=(SCREEN_WIDTH-400)/menunum;
         buttons[i].y=Y_TEMP;
         buttons[i].h=((SCREEN_HEIGHT-100)-((menunum-1)*50))/menunum;
         buttons[i].w=SCREEN_WIDTH/2;

         Y_TEMP+=(buttons[i].h+50);

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
                                 stringColor(renderer,(SCREEN_WIDTH/2)-50,buttons[i].y+(((SCREEN_HEIGHT-100)-((menunum-1)*50))/(menunum*2)),label[i],0xff0000ff);
                             }

                         }
                         else
                         {
                             if (select[i])
                             {
                                 select[i]=0;
                                 stringColor(renderer, (SCREEN_WIDTH/2)-50, buttons[i].y+(((SCREEN_HEIGHT-100)-((menunum-1)*50))/(menunum*2)), label[i], 0xffffffff);
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


//loading picture
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
    //Initializing the window

    for(int i=0;i<1000;i++)
    {
        username[i]='\0';
    }


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




    getusername(sdlRenderer);

    int a=checkusername();


























    for(int i=0;i<30;i++)
    {
        attackcount[i]=0;
    }


    for(int i=0;i<10;i++)
    {
        for(int j=0;j<30;j++)
        {
            do_once[i][j]=0;
        }
    }

for(int i=0;i<playercount;i++)
{
    for (int j=0;j<10;j++)
    {
        attack_status[i][j]=0;
    }
}

    struct potions potion[4];
    for(int i=0;i<4;i++)
    {
            potion[i].is_onplace=0;
            potion[i].is_on=0;

    }

    //Check varables

    int potion_on=0;
    int picturecheck=1;
    int timecheck[30];
    for(int i=0;i<30;i++)
    {
        timecheck[i]=1;
    }
    int check_do_once=0;
    int check_arrow=0;
    int once_pressed=0;

    int DontRecolor[30];
    for(int i=0;i<30;i++)
    {
        DontRecolor[i]=0;
    }
    //Default variables

    time_t time1[30];
    time_t time2[30];
    for(int i=0;i<30;i++)
    {
        time1[i]=time(NULL);
    }

int player_count=1;

    playerscolors[0]=0xff0000ff; //Red
    playerscolors[1]=0x0000ff00; //Blue
    playerscolors[2]=0xffff00ff; //Yellow
    playerscolors[3]=0xff00ffff; //Magenta


    for(int j=0;j<30;j++)
    {
        select_dots[0][j]=0;
        select_dots[1][j]=500;
    }

    Uint32 color;


    for(int i=0;i<30;i++)
    {
        counter[i]=0;
    }


    for(int i=0;i<player_count;i++)
    {
        for(int j=0;j<10;j++)
        {
            for(int k=0;k<10000;k++)
            {
                attack[i][j][k]=0;
            }

        }
    }



    int x_clickstartpoint,y_clickstartpoint;
    int Dotnum=-1;
    int target;



    //MENU

    SDL_Texture *sdlTexture;
    int x,y,w,h;
    int district;
    int name;


    int BEGIN= StartMenu(sdlRenderer);
    switch(BEGIN)
    {
        case 0: //Sets Default information for selected map
            name=MenuDefaultmaps(sdlRenderer);
            switch(name)
            {
                case 0:
                    sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Africa.bmp");
                    x=188;
                    y=14;
                    w=623;
                    h=772;
                    district=15;

                    select_dots[0][12]=1;
                    select_dots[1][12]=0;

                    break;

                case 1:
                    sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Asia.bmp");
                    x=10;
                    y=53;
                    w=1000;
                    h=693;
                    district=14;

                    select_dots[0][13]=1;
                    select_dots[1][13]=0;


                    break;

                case 2:
                    sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Australia.bmp");
                    x=21;
                    y=33;
                    w=957;
                    h=734;
                    district=15;

                    select_dots[0][2]=1;
                    select_dots[1][2]=0;

                    break;

                case 3:
                    RandomMap(&district,8);
                    picturecheck=0;

                    break;
            }
            break;

        case 2:

            break;

        case 3:

            break;

        case 4:
            exit(0);
            break;



    }
    SDL_Rect texture_rect;
    if(picturecheck)
    {
       texture_rect.x=x;
       texture_rect.y=y;
       texture_rect.w=w;
       texture_rect.h=h;
    }









//GAME LOOP

begintime=time(NULL);

    while (shallExit==SDL_FALSE)
        {

            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);

            //Default map
            if(picturecheck)
            {
                SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);
            }
            if(!picturecheck)
            {
                for(int i=0;i<district;i++)
                {int r;

                    switch(tags[i])
                    {
                        case 's':
                            r=30;
                            break;

                        case 'm':
                            r=40;
                            break;

                        case 'l':
                            r=50;
                            break;
                    }
                    filledCircleColor(sdlRenderer,dots[0][i],dots[1][i],r,0xff0000ff);

                }
            }



            if(check_do_once==0&&picturecheck)
            {
                check_do_once++;
                dot_taker(name,x,y,district);
                tag_taker(name,district);
            }

            for(int i=0;i<district;i++)
            {
                if(select_dots[0][i])
                {
                    color=playerscolors[select_dots[1][i]];
                }
                else
                {
                    color=0xffffffff;
                }

                if(DontRecolor[i])
                {
                    color=0xffaa00ff;
                }

                    Draw_Barrack(sdlRenderer,i,dots[0][i],dots[1][i],tags[i],color);



                if(select_dots[0][i])
                {int add=3;
                    sprintf(count,"%d",counter[i]);
                    if(counter[i]>=10)
                    {
                        add=7;
                    }
                    stringColor(sdlRenderer,dots[0][i]-add,dots[1][i]-3,count,0xffffffff);
                    time2[i]=time(NULL);
                    if(counter[i]<soldierlimit[i])
                    {
                        timecheck[i]=1;
                    }
                    if(((time2[i]-time1[i])>=1)&&timecheck[i])
                    {
                        time1[i]=time2[i];
                        counter[i]++;

                        if(counter[i]>=soldierlimit[i])
                        {
                            timecheck[i]=0;
                        }
                    }

                }
                if(!select_dots[0][i])
                {
                    counter[i]=0;
                    sprintf(count,"%d",counter[i]);
                    stringRGBA(sdlRenderer,dots[0][i]-3,dots[1][i]-3,count,0,0,0,255);
                }
            }





           /* int potionYN=ifpotion(potion);
            struct potions temp1=findrandomspot(district);
            if(potionYN&&!potion_on)
            {
                potion_on=1;


                int rand= RandomNumber(0,50);

                potion[potionYN-1].is_onplace=1;
                potion[potionYN-1].x=temp1.x;
                potion[potionYN-1].y=temp1.y;


            }

            for(int i=0;i<4;i++)
            {
                if(potion[i].is_onplace==1)
                {
                    boxColor(sdlRenderer,potion[i].x,potion[i].y,potion[i].x+30,potion[i].y+30,0xA020F0A0);
                }
            }
            */




















            // listen for key events
            SDL_Event sdlEvent;


            if(check_arrow)
            {
                int x_clicksecontpoint,y_clicksecondpoint;
                SDL_GetMouseState(&x_clicksecontpoint,&y_clicksecondpoint);

                lineColor(sdlRenderer,dots[0][Dotnum],dots[1][Dotnum],x_clicksecontpoint,y_clicksecondpoint,0xff0000ff);
            }








            for(int i=0;i<playercount;i++)
            {
                for(int j=0;j<attackcount_mp;j++)
                {
                    if(attack_status[i][j])
                    {
                        checkreset+=attack_function(j,i,sdlRenderer);
                    }
                }
            }




            /*
            if(soldierleft(player_count,temp,attack)||checkattack)
            {
                attack_function(,sdlRenderer);
            }
            if((attackcount[currentattackumber]==9)&&(!(soldierleft(player_count,temp,attack)||checkattack)))
            {
                attackcount[currentattackumber]=0;
            }
            */












            while (SDL_PollEvent(&sdlEvent))
            {


                switch (sdlEvent.type)
                {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;



                    case SDL_MOUSEBUTTONDOWN:
                        x_clickstartpoint=sdlEvent.motion.x;
                        y_clickstartpoint=sdlEvent.motion.y;


                        if(once_pressed)
                        {
                            check_arrow=0;
                            once_pressed=0;
                            playerscolors[0]=0xff0000ff;

                            target=inthecircle('t',x_clickstartpoint,y_clickstartpoint,district,select_dots);
                            if(target)
                            {
                                target--;
                                attack_soldiercount[0][attackcount_mp]=counter[Dotnum];
                                attack_status[0][attackcount_mp]=1;
                                attack_startingpoint[0][attackcount_mp]=Dotnum;
                                attack_endingpoint[0][attackcount_mp]=target;
                                DontRecolor[Dotnum]=0;
                                attackcount_mp++;

                                break;

                                /*checkattack=counter[Dotnum];
                                start=Dotnum;
                                temp[0][attackcount[0]][0]=checkattack;
                                end=target[0][attackcount[0]][0];
                                do_once[attackcount[0]][0]=0;
                                DontRecolor[Dotnum]=0;
                                currentattackumber=0;
                                attackcount[0]++;
                                break;*/


                            }

                        }
                        if(!once_pressed)
                        {

                                Dotnum=inthecircle('s',x_clickstartpoint,y_clickstartpoint,district,select_dots);

                                if(Dotnum)
                                {
                                    Dotnum--;
                                    DontRecolor[Dotnum]=1;
                                    Draw_Barrack(sdlRenderer,Dotnum,dots[0][Dotnum],dots[1][Dotnum],tags[Dotnum],0xffaa00ff);
                                    check_arrow=1;
                                    once_pressed=1;

                                }



                        }

                        break;


                }


            }


            SDL_RenderPresent(sdlRenderer);
            SDL_Delay(1 / FPS);

        }

    return 0;

}