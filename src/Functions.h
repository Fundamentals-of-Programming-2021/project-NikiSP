#define playercount 5

//DEFAULT VARIABLES


int key1=0;
time_t begintime;
time_t startpotion;
time_t endpotion;

int potion_on=0;

int do_once[playercount][10000];
int attack_soldiercount[playercount][10000];
bool attack_status[playercount][10000];
int attackcount_all[playercount];
int attack_startingpoint[playercount][10000];
int attack_endingpoint[playercount][10000];
double soldiers_coordinates[playercount][1000][2][10000];
int startdraw[playercount][10000];
int eliminatefurthur[playercount][10000];
double tan1[playercount][10000];
double change[playercount][10000];
double sign[playercount][10000];



int number=0;

long long int score=0;
char name_board[1000];
int high;
char username[1000];
char record[1000];


const int FPS = 60;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;


Uint32 playerscolors[1000];
int dots[2][30];
char tags[30];
int soldierlimit[30];
int select_dots[2][30];
char count[5000];
int counter[30];

int start=-1;
int end=-1;






struct potions
{               //playersnum
    bool is_on;
    bool is_onplace;

    double x;
    double y;

    Uint32 color;


};

struct potions potion[4];



struct potionuser
{
    int playernum;

};


struct potionuser potionusers[4];

void ScoreB()
{
    FILE *ptr=fopen("txtfiles/ScoreBoard/UserScore.txt","r");
    char x[1000];
    int max=0;
    int flag;

    while(fscanf(ptr,"%[^\n]s",x)==1)
    {
        fscanf(ptr," %d ",&flag);
        if(max<=flag)
        {
            strcpy(name_board,x);
            high=flag;
            max=flag;
        }
    }

    fclose(ptr);
}


void scoremenu(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
SDL_Event event;
    while(true)
    {
        stringColor(renderer,SCREEN_WIDTH/2-100,50,"High Score",0xffffffff);
        ScoreB();
        stringColor(renderer,SCREEN_WIDTH/4,SCREEN_HEIGHT/2,name_board,0xffffffff);
        sprintf(record,"%d",high);
        stringColor(renderer,SCREEN_WIDTH*3/4,SCREEN_HEIGHT/2,record,0xff0000ff);

        while(SDL_PollEvent(&event))
        {


            switch(event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;


            }
        }

        SDL_RenderPresent(renderer);
    }


}





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
//adding score
void end_of_game()
{
    FILE *ptr= fopen("txtfiles/ScoreBoard/UserScore.txt","r");
    FILE *makenew= fopen("txtfiles/ScoreBoard/UserScore2.txt","w");

    char x[1000];
    int flag;

    while(fscanf(ptr, "%[^\n]s",x)==1)
    {
        fscanf(ptr," %d ",&flag);
        if(strcmp(username,x)==0)
        {
            flag+=score;

        }
        fprintf(makenew,"%s\n%d\n",x,flag);
    }

    fclose(ptr);
    fclose(makenew);
    remove("txtfiles/ScoreBoard/UserScore.txt");
    rename("txtfiles/ScoreBoard/UserScore2.txt","txtfiles/ScoreBoard/UserScore.txt");
}


//looks for the given username in the txt file
int checkusername()
{
    FILE *ptr= fopen("txtfiles/ScoreBoard/UserScore.txt","a+");
    if(ptr==NULL)
    {
        return 0;
    }

    char x[1000];
    int temp5;


    while (fscanf(ptr, "%[^\n]s", x)==1)
    {
        fscanf(ptr," %d ",&temp5);
        if(strcmp(username,x)==0)
        {
            fclose(ptr);
            return 1;
        }

    }
    fputs(username,ptr);
    fprintf(ptr,"\n%d\n",0);
    fclose(ptr);
    return 0;


}
//Geting username
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
int using[playercount];
int usingwhat[playercount];

// target handling
void check_destination(int end, int playernum)
{


    if(counter[end]==0)
    {
        select_dots[0][end]=1;
        select_dots[1][end]=playernum;

    }

        if(select_dots[1][end]==playernum)
        {

            counter[end]++;

        }
        else
        {
            if(using[playernum]&&usingwhat[playernum]==1)
            {
                if(counter[end]==1)
                {
                    counter[end]--;
                }
                else
                {
                    counter[end]-=2;
                }

            }
            else
            {
                counter[end]--;
            }

        }




}


//pause menu

int middle_game_menu(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    const menunum=2;

    char *label[menunum];

    label[0]="Resume";

    label[1]="Exit";


    int Y_TEMP=50;

    bool select[menunum];
    select[0]=0;
    select[1]=0;



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


//Decides whether it's the right time to draw the next soldier
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

            soldiers_coordinates[attackernum][attacknum][0][i]=(double )dots[0][attack_startingpoint[attackernum][attacknum]];
            soldiers_coordinates[attackernum][attacknum][1][i]=(double) dots[1][attack_startingpoint[attackernum][attacknum]];

        }

        eliminatefurthur[attackernum][attacknum]=0;
        startdraw[attackernum][attacknum]=1;

    }

    int i;
    for(i=eliminatefurthur[attackernum][attacknum];i<startdraw[attackernum][attacknum];i++)
    {

        if(isitthere(attack_endingpoint[attackernum][attacknum],soldiers_coordinates[attackernum][attacknum][0][i],soldiers_coordinates[attackernum][attacknum][1][i]))
        {
            check_destination(attack_endingpoint[attackernum][attacknum],attackernum);

            eliminatefurthur[attackernum][attacknum]++;
        }


        for(int j=0;j<4;j++)
        {

            if((soldiers_coordinates[attackernum][attacknum][0][i]>=potion[j].x)&&(soldiers_coordinates[attackernum][attacknum][0][i]<=(potion[j].x+30))&&(soldiers_coordinates[attackernum][attacknum][1][i]>=potion[j].y)&&(soldiers_coordinates[attackernum][attacknum][1][i]<=(potion[j].y+30)))
            {

                if(!using[attackernum])
                {
                    startpotion=time(NULL);

                    using[attackernum]=1;
                    potion[j].is_onplace=0;
                    usingwhat[attackernum]=j;
                    potion_on=0;

                }


            }
        }

        filledCircleColor(sdlRenderer, soldiers_coordinates[attackernum][attacknum][0][i],soldiers_coordinates[attackernum][attacknum][1][i],5, playerscolors[attackernum]);



        if(dots[0][attack_startingpoint[attackernum][attacknum]]!=dots[0][attack_endingpoint[attackernum][attacknum]])
        {

            if(using[attackernum]&&usingwhat[attacknum]==0)
            {
                soldiers_coordinates[attackernum][attacknum][0][i]+=(change[attackernum][attacknum])*2;
                soldiers_coordinates[attackernum][attacknum][1][i]+=((double)(sign[attackernum][attacknum]*2*change[attackernum][attacknum]*tan1[attackernum][attacknum]));
            }
            else
            {
                soldiers_coordinates[attackernum][attacknum][0][i]+=change[attackernum][attacknum];
                soldiers_coordinates[attackernum][attacknum][1][i]+=((double)(sign[attackernum][attacknum]*change[attackernum][attacknum]*tan1[attackernum][attacknum]));
            }

        }

        else
        {
            if(dots[1][attack_startingpoint[attackernum][attacknum]]>dots[1][attack_endingpoint[attackernum][attacknum]])
            {
                if(using[attackernum]&&usingwhat[attacknum]==0)
                {
                    soldiers_coordinates[attackernum][attacknum][1][i]-=4;
                }
                else
                {
                    soldiers_coordinates[attackernum][attacknum][1][i]-=2;
                }

            }
            else
            {

                if(using[attackernum]&&usingwhat[attacknum]==0)
                {
                    soldiers_coordinates[attackernum][attacknum][1][i]+=4;
                }
                else
                {
                    soldiers_coordinates[attackernum][attacknum][1][i]+=4;
                }

            }

        }

    }

    i--;

    if((counter[attack_startingpoint[attackernum][attacknum]]&&startdraw[attackernum][attacknum]<attack_soldiercount[attackernum][attacknum])&&next_soldier(soldiers_coordinates[attackernum][attacknum][0][i],soldiers_coordinates[attackernum][attacknum][1][i],attack_startingpoint[attackernum][attacknum]))
    {
        startdraw[attackernum][attacknum]++;
        counter[attack_startingpoint[attackernum][attacknum]]--;
    }


    return 0;

}




//Generating random number
int RandomNumber(int start, int end)
{


    return ((rand()%(end-start+1))+start);

}


//creatin new potions

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

    if((Random%100==0)||((now-begintime)>20))
    {
        begintime=time(NULL);
        Random= RandomNumber(11,14);
        switch(Random)
        {
            case 12:
                return 1;
                break;

            case 11:
                return 2;
                break;

            case 13:
                return 3;
                break;

            case 14:
                return 4;
                break;
        }
    }

    return 0;
}


//Finds random spots for potions

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




    temp.x=(dots[0][a]+dots[0][b])/2;
    temp.y=(dots[1][a]+dots[1][b])/2;



    return temp;

}







//Creating random map


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
    //Random

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

        case 3:
            dotfile = fopen("txtfiles/Dots/Asia_dot-set-list.txt", "r");
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
        case 3:
            tagfile=fopen("txtfiles/Tags/Asia.txt","r");
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
    label[3]="Test Map";

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
//        1-->Score Board
//        2-->Exit

int StartMenu(SDL_Renderer *renderer, int a)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    const menunum=3;

    char *label[menunum];

    label[0]="New Game";

    label[1]="Score Board";

    label[2]="Exit";

    int Y_TEMP=50;

    bool select[menunum];
    select[0]=0;
    select[1]=0;
    select[2]=0;

    if(a)
    {
        stringColor(renderer,SCREEN_WIDTH/4+100,50,"welcome back ",0xffffffff);
    }
    else
    {
        stringColor(renderer,SCREEN_WIDTH/4+100,50,"welcome ",0xffffffff);
    }
    stringColor(renderer,3*SCREEN_WIDTH/4-200,50,username,0xff0000ff);
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