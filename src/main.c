#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#ifdef main
#undef main
#endif

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "Functions.h"
struct potions potion[4];
//Niki Sepasian
//400105003

int main()
{


    srand(time(0));



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











    for(int i=0;i<playercount;i++)
    {
        using[i]=0;
        usingwhat[i]=-1;
    }

    for(int i=0;i<1000;i++)
    {
        username[i]='\0';
    }


    for(int i=0;i<playercount;i++)
    {
        attackcount_all[i]=0;
    }


    getusername(sdlRenderer);

    int a=checkusername();


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

    for(int i=0;i<4;i++)
    {
            potion[i].is_onplace=0;
            potion[i].is_on=0;

    }


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

    time_t time1[30];
    time_t time2[30];

    for(int i=0;i<30;i++)
    {
        time1[i]=time(NULL);
    }

int player_count=1;

    playerscolors[0]=0xff0000ff; //Red
    playerscolors[1]=0xffff0000; //Blue
    playerscolors[2]=0xff203201; //Dark Green
    playerscolors[3]=0xff33D61A; //Light Green


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


    int x_clickstartpoint,y_clickstartpoint;
    int Dotnum=-1;
    int target;


    SDL_Texture *sdlTexture;
    int x,y,w,h;
    int district;
    int name;
int checklate=0;

    int BEGIN= StartMenu(sdlRenderer,a);
    switch(BEGIN)
    {
        case 0: //Sets Default information for selected map//FILE *scoreptr;
            //FILE *userptr;
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

                    select_dots[0][0]=1;
                    select_dots[1][0]=1;

                    select_dots[0][5]=1;
                    select_dots[1][5]=2;

                    select_dots[0][2]=1;
                    select_dots[1][2]=3;

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

                    select_dots[0][1]=1;
                    select_dots[1][1]=1;

                    select_dots[0][6]=1;
                    select_dots[1][6]=2;

                    select_dots[0][9]=1;
                    select_dots[1][9]=3;

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

                    select_dots[0][9]=1;
                    select_dots[1][9]=1;

                    select_dots[0][6]=1;
                    select_dots[1][6]=2;

                    select_dots[0][14]=1;
                    select_dots[1][14]=3;

                    break;

                case 3:
                    sdlTexture = getImageTexture(sdlRenderer, "defaultmaps/Asia.bmp");
                    x=10;
                    y=53;
                    w=1000;
                    h=693;
                    district=14;

                    for(int i=0;i<district;i++)
                    {
                        select_dots[0][i]=1;
                        select_dots[1][i]=0;
                    }


                    select_dots[0][1]=1;
                    select_dots[1][1]=1;


                    break;
            }
            break;

        case 1:
            ScoreB();
            scoremenu(sdlRenderer);
            break;

        case 2:
            exit(0);
            break;



    }
    SDL_Rect texture_rect;


       texture_rect.x=x;
       texture_rect.y=y;
       texture_rect.w=w;
       texture_rect.h=h;










//GAME LOOP

begintime=time(NULL);

    while (shallExit==SDL_FALSE)
        {

            SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(sdlRenderer);

            //Default map


                SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &texture_rect);





            if(check_do_once==0)
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
                        if(using[select_dots[1][i]]==1&&usingwhat[select_dots[1][i]]==3)
                        {
                            counter[i]+=2;
                        }
                        else
                        {
                            counter[i]++;
                        }


                        if(counter[i]>=soldierlimit[i])
                        {
                            if(usingwhat[select_dots[1][i]]!=2)
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



            endpotion=time(NULL);
            if(endpotion-startpotion>10)
            {
                for(int i=0;i<playercount;i++)
                {
                    if(using[i])
                    {
                        using[i]=0;
                        potion[usingwhat[i]].is_onplace=0;
                        potion[usingwhat[i]].is_on=0;

                    }
                }
            }


            int potionYN=ifpotion(potion);
            struct potions temp1=findrandomspot(district);
            if(potionYN&&!potion_on)
            {
                potion_on=1;


                potion[potionYN-1].is_onplace=1;
                potion[potionYN-1].x=temp1.x;
                potion[potionYN-1].y=temp1.y;


            }
            potion[0].color= 0xff0000ff; //light blue
            potion[1].color= 0xffffffff; //light red
            potion[2].color= 0xff000000; //light purple/pink
            potion[3].color= 0xffaa00ff; //darker blue
            for(int i=0;i<4;i++)
            {
                if(potion[i].is_onplace==1)
                {
                    Uint32  color1;
                    switch(i)
                    {
                        case 0:
                            color1= 0xfff9ff69; //light blue
                            break;

                        case 1:
                            color1= 0xff6969ff; //light red
                            break;

                        case 2:
                            color1= 0xffd669ff; //light purple/pink
                            break;

                        case 3:
                            color1= 0xfff98c86; //darker blue
                            break;
                    }





                    boxColor(sdlRenderer,potion[i].x,potion[i].y,potion[i].x+30,potion[i].y+30,color1);
                }
            }



            for(int i=0;i<4;i++)
            {
                Uint32  color1;
                switch(i)
                {
                    case 0:
                        color1= 0xfff9ff69; //light blue
                        break;

                    case 1:
                        color1= 0xff6969ff; //light red
                        break;

                    case 2:
                        color1= 0xffd669ff; //light purple/pink
                        break;

                    case 3:
                        color1= 0xfff98c86; //darker blue
                        break;
                if(usingwhat[0]==i&&using[0]==1)
                {
                    boxColor(sdlRenderer,50,50,80,80,potion[potionYN].color);
                }
                }
            }












            if(check_arrow)
            {
                int x_clicksecontpoint,y_clicksecondpoint;
                SDL_GetMouseState(&x_clicksecontpoint,&y_clicksecondpoint);

                lineColor(sdlRenderer,dots[0][Dotnum],dots[1][Dotnum],x_clicksecontpoint,y_clicksecondpoint,0xff0000ff);
            }










            int ran1= RandomNumber(0,700);
            if(ran1%200==0)
            {
                int Now=ran1%3+1;

                int startchoices[20];
                int endchoices[20];
                int l=0;
                int k=0;
                for(int j=0;j<district;j++)
                {
                    if(select_dots[0][j]&&select_dots[1][j]==Now)
                    {
                        startchoices[k]=j;
                        k++;
                    }

                }

                if(k==0)
                {
                    continue;
                }

                int rand=RandomNumber(0,k-1);


                for(int j=0;j<district;j++)
                {
                    if(counter[j]<counter[startchoices[rand]])
                    {
                        endchoices[l]=j;
                        l++;
                    }
                }

                if(l<=0)
                {
                    continue;
                }

                int rand1= RandomNumber(0,l-1);

                attack_startingpoint[Now][attackcount_all[Now]]=startchoices[rand];
                attack_soldiercount[Now][attackcount_all[Now]]=counter[startchoices[rand]];
                attack_status[Now][attackcount_all[Now]]=1;
                attack_endingpoint[Now][attackcount_all[Now]]=endchoices[rand1];


                attackcount_all[Now]++;

            }






            for(int i=0;i<playercount;i++)
            {
                for(int j=0;j<attackcount_all[i];j++)
                {
                    if(attack_status[i][j])
                    {
                        attack_function(j,i,sdlRenderer);
                    }
                }
            }




            int sum=0;
            for(int i=0;i<playercount;i++)
            {
                sum=0;
                for(int j=0;j<attackcount_all[i];j++)
                {
                    if(attack_status[i][j]==0)
                    {
                        sum++;
                    }
                }
                if(sum==attackcount_all[i])
                {
                    attackcount_all[i]=0;
                }
            }



            int checkend=0;
            for(int i=0;i<district;i++)
            {
                if(select_dots[0][i]&&select_dots[1][i]==0)
                {
                    checkend++;
                }

            }
            if(checkend==0&&attackcount_all[0]==0)
            {
                score-=50;
                end_of_game();
                break;
            }

            int checkend1=0;
            for(int i=0;i<district;i++)
            {
                if(select_dots[0][i]&&select_dots[1][i]!=0)
                {
                    checkend1++;
                }
            }



            if(checkend1==0)
            {
                score+=100;
                end_of_game();
                break;
            }


            SDL_Event sdlEvent;
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
                            DontRecolor[Dotnum]=0;
                            target=inthecircle('t',x_clickstartpoint,y_clickstartpoint,district,select_dots);
                            if(target)
                            {

                                target--;
                                if(attack_status[0][attackcount_all[0]-1]==1&&(attackcount_all[0]!=0)&&attack_startingpoint[0][attackcount_all[0]]==attack_startingpoint[0][attackcount_all[0]-1])
                                {
                                    attack_soldiercount[0][attackcount_all[0]]=counter[Dotnum]-attack_soldiercount[0][attackcount_all[0]-1];
                                }
                                else
                                {
                                    attack_soldiercount[0][attackcount_all[0]]=counter[Dotnum];
                                }

                                attack_status[0][attackcount_all[0]]=1;
                                attack_startingpoint[0][attackcount_all[0]]=Dotnum;
                                attack_endingpoint[0][attackcount_all[0]]=target;
                                DontRecolor[Dotnum]=0;
                                attackcount_all[0]++;

                                break;


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

                    case SDL_KEYDOWN:

                        if(sdlEvent.key.keysym.sym==SDLK_ESCAPE)
                        {
                            switch(middle_game_menu(sdlRenderer))
                            {
                                case 0:
                                    break;


                                case 1:
                                    exit(0);
                                    break;

                            }
                        }


                }



            }


            SDL_RenderPresent(sdlRenderer);
            SDL_Delay(1 / FPS);

                if(key1)
                {
                    break;
                }

        }

        SDL_DestroyTexture(sdlTexture);
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);


    return 0;

}