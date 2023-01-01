//Libery *******************
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "raylib.h"
//**************************

//flags*****************
bool help=true;
bool exitwindowsreq=false;
bool windowsclose=false;
bool entering=true;
bool CloseGame=false;
//**********************
//Structs***********************
struct ship
{
    int x;
    int y;
};

struct player
{
    int cards[4];
struct ship ship1;
struct ship ship2;
}player1,player2;

//*******************************

//Screen Functions
void enter(Texture2D texture){
    ClearBackground(BLACK);
    DrawTexture(texture,0,0,WHITE);
    DrawText("Press Enter to Countinue...",450,350,30,BLUE);
}
void menu(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture,0,0,WHITE);
}
void Exit(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture,0,0,WHITE);
}
void Help(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture,0,0,WHITE);
}
void Closemenu(Texture2D texture){
    DrawTexture(texture,0,0,WHITE);

}
void Devinfo(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture,0,0,WHITE);
}

void choose(int k,Texture2D texture){
    if(k==0){
    return enter(texture);
    }else if(k==1){
    return menu(texture);
    }else if(k==2 && help){
    return  Help(texture);
   }/* else if(k==7)
    return MultiPlayer();
    */else if(k==6){
    return Devinfo(texture);
    }
}
//****************

//Game Functions
const int dice_num = 1000;
int dice[1000];
void Randomize(){
    srand((unsigned) time(NULL));
}
void dice_maker() {
    int dic;
    for(int i = 0; i < dice_num; i++) {
        dic= rand() % 6;
        switch (dic) {
            case 0:
                dice[i]=-1;
                break;
            case 4:
                dice[i] = -2;
                break;
            case 5:
                dice[i] = -3;
                break;
            default:
                dice[i] = dic;
                break;
        }
    }
}

int roll_dice() {
    int ran_num = rand() % 1000;
    if(dice[ran_num]==0) {
     return roll_dice();
    }
    else{
    int temp = dice[ran_num];
    dice[ran_num] = 0;
    return temp;
    }
}
int chancecard(int arr[]){
    srand((unsigned) time(NULL));
    int card=rand()%4;
    arr[card]++;
    return card;
}


//**************

//Main Function
int main()
{
    //Tool va arz safhe menu....
    const int screenWidth = 1280; 
    const int screenHeight = 720;
    int k=0; //Screen button;
    //MUSIC*************
    float musictime=1.0f;
    bool pausemusic=false;
    float volume=0.5f;
    //******************

    InitWindow(screenWidth, screenHeight, "MEET IN THE MIDDLE");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    //Images ***************************************************
    //Safhe ha
    Texture2D Screan[8];
    //closemenu
    Screan[7]=LoadTexture("resources/closemenu.png");
    //exit
    Screan[8]=LoadTexture("resources/exit.png");
    //Menu
    Screan[1]=LoadTexture("resources/menu.png");
    //entering
    Screan[0]=LoadTexture("resources/Entering.png");
    //DEVINFO
    Screan[6]=LoadTexture("resources/devinfo.png");
    //HELP AND RULES
    Screan[2]=LoadTexture("resources/help.png");
    //Board game
    Texture2D Board=LoadTexture("resources/Board.png");
    //BOAT PLAYER 1
    Texture2D Boat1=LoadTexture("resources/boat1.png");
    //BOAT PLAYER 2
    Texture2D Boat2=LoadTexture("resources/boat2.png");
    //Mouse
    struct mouse
    {
        int x;
        int y;
    }mouse;
    
    //**********************************************************

    //AUDIO*************************************************
    InitAudioDevice();
    Sound select=LoadSound("resources/select.wav");
    Sound boom=LoadSound("resources/entergame.wav");
    Music game=LoadMusicStream("resources/gamemusic.mp3");
    //******************************************************
    
    while(!windowsclose){

        if((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) && k!=6 && k!=2){ //khoroj az safhe
            exitwindowsreq=true;
        }
        if(IsKeyPressed(KEY_ENTER) && k==0){ //rad shodan safhe hayi ke ba enter rad mishavand
            k++;
        }
        //MENU BAZI LOGIC
        if(k==1){
        mouse.x=GetMouseX();
        mouse.y=GetMouseY();
        if(923<=mouse.x && mouse.x<=1206){
        if(260<=mouse.y && mouse.y<=330 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//singleplayer
            k=5;
            PlaySound(select);
        }else if(mouse.y<=408 && 338<=mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Multiplayer
        //   k=7
        PlaySound(select);
        }else if(417<=mouse.y && mouse.y<=487 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Devinfo
            k=6;
            PlaySound(select);
        }else if(496<=mouse.y && mouse.y<=566 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){//Help
            k=2;
            PlaySound(select);
        }
        }
        if(mouse.x<=139 && 11<=mouse.x && mouse.y<=712 && 642<=mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))//exit
            exitwindowsreq=true;
        }
        //Help Logic***********************************
        if(k==2){
        mouse.x=GetMouseX();
        mouse.y=GetMouseY();
        if((11<=mouse.x && mouse.x<=139 && mouse.y<=712 && 642<=mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))|| IsKeyPressed(KEY_ESCAPE))
            k=1;
        }
        //*********************************************
        if(k==6){ //Dev info logic
            mouse.x=GetMouseX();
            mouse.y=GetMouseY();
            if(IsKeyPressed(KEY_ESCAPE) ||(mouse.x<=139 && 11<=mouse.x && mouse.y<=712 && 642<=mouse.y &&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) 
            k=1;
        }
        //*****************************************
        BeginDrawing();
        

       if(exitwindowsreq && k!=5){
        Exit(Screan[8]);
        mouse.x=GetMouseX();
        mouse.y=GetMouseY();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 412<=mouse.x && mouse.x<=578 && 396<=mouse.y && mouse.y<=439){
        exitwindowsreq=false; 
        } 
        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 701<=mouse.x && mouse.x<=867 && 396<=mouse.y && mouse.y<=439){
        windowsclose=true;
        CloseGame=true;
        }

        }else if(k!=5){
        if(k==0 && entering){ // paksh seda vorodi
            PlaySound(boom);
            entering=false;
        }
        choose(k,Screan[k]);
        }
        EndDrawing();

        //Game LOOP
        while(k==5){ 
        BeginDrawing();
        UpdateMusicStream(game);
        //Music game*****************
        if(musictime>=1.0){
            PlayMusicStream(game);
            musictime=0.0f;
        }
        musictime=GetMusicTimePlayed(game)/GetMusicTimeLength(game);
        if(IsKeyPressed(KEY_UP) && volume!=1.0f) {
            volume+=0.1f;
            SetMusicVolume(game,volume);
        }
        if(IsKeyPressed(KEY_DOWN) && volume!=0.0f){
            volume-=0.1f;
            SetMusicVolume(game,volume);
        }
        if(IsKeyPressed(KEY_P)){
            pausemusic=true;
            if(pausemusic) PauseMusicStream(game);
        }
        if(IsKeyPressed(KEY_R)){
            pausemusic=false;
            ResumeMusicStream(game);
        }
        //***************************************
        //Board Game Screen
        ClearBackground(GRAY);
        DrawTexture(Board,0,0,WHITE);
        //**************************

        DrawTexture(Boat1,457,634,WHITE);
        DrawTexture(Boat1,457,634,WHITE);
        //******************************
        DrawTexture(Boat2,1071,20,WHITE);
        DrawTexture(Boat2,1071,20,WHITE);
        //*****************************************************
        if((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose())){ //khoroj az safhe
            exitwindowsreq=true;
        }
         if(exitwindowsreq){ //bargasht be menu az safhe asli
        Closemenu(Screan[7]);
        mouse.x=GetMouseX();
        mouse.y=GetMouseY();
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 472<=mouse.x && mouse.x<=808 && 370<=mouse.y && mouse.y<=428){
            exitwindowsreq=false;
            k=1;
        }
        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 472<=mouse.x && mouse.x<=808 && 292<=mouse.y && mouse.y<=350){
            exitwindowsreq=false;
        }//******************************************************
        }
        EndDrawing();
       } 
        //***********************************************
        }
        UnloadTexture(Screan[7]);
        UnloadTexture(Screan[8]);
        UnloadTexture(Screan[0]);
        UnloadTexture(Screan[2]);
        UnloadTexture(Screan[1]);
        UnloadTexture(Screan[6]);
        UnloadTexture(Board);
        UnloadTexture(Boat1);
        UnloadTexture(Boat2);
        UnloadMusicStream(game);
        UnloadSound(boom);
        UnloadSound(select);
        CloseAudioDevice();
        CloseWindow();
        
}
