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

//Screen Functions
void enter(){
    ClearBackground(BLACK);
    DrawText("MEET IN THE MIDDLE",300,350,55,WHITE);
    DrawText("Press Enter to Countinue...",450,400,20,GRAY);
}
void menu(){
    ClearBackground(WHITE);
    DrawText("MEET IN THE MIDDLE",300,100,75,BROWN);
    DrawText("1.Offline mode",450,300,50,BROWN);
    DrawText("2.Online mode",450,350,50,BROWN);
    DrawText("3.DevInfo",450,400,50,BROWN);

}
void Exit(){
    DrawRectangle(0,0,1280,800,WHITE);
    DrawText("Are U Sure Darling ?! Y/N",110,350,60,BLACK);
            
    if(IsKeyPressed(KEY_N)){
        exitwindowsreq=false; 
    } 
    else if(IsKeyPressed(KEY_Y)){
        windowsclose=true;
        CloseGame=true;
    } 
}
void Help(int k){
    if(k==2){
        ClearBackground(GRAY);
        DrawText("How to play the game",100,100,20,WHITE);
        DrawText("1.Press KEY TO ROLL THE DICE",100,150,20,WHITE);
        DrawText("2.Press KEY TO SHOW YOUR CHANCES CARD",100,200,20,WHITE);
        DrawText("3.Click On your Mohre to move it",100,250,20,WHITE);
        DrawText("Press Enter to exit the Help Menu",100,350,30,WHITE);
    }else if(k==3){
        ClearBackground(GRAY);
        DrawText("How to play the game",100,100,20,WHITE);
        DrawText("asdasdasdasd",100,150,20,WHITE);
        DrawText("2.Press KEY TO SHOW YOUR CHANCES CARD",100,200,20,WHITE);
        DrawText("3.Click On your Mohre to move it",100,250,20,WHITE);
        DrawText("Press Enter to exit the Help Menu",100,350,30,WHITE);

    }else if(k==4){
        ClearBackground(GRAY);
        DrawText("How to play the game",100,100,20,WHITE);
        DrawText("asdasdasdasd",100,150,20,WHITE);
        DrawText("2.Press KEY TO SHOW YOUR CHANCES CARD",100,200,20,WHITE);
        DrawText("4.:/",100,250,20,WHITE);
        DrawText("Press Enter to exit the Help Menu",100,350,30,WHITE);

    }

}
void Closemenu(){
    DrawRectangle(250,250,500,500,BLACK);
    DrawText("Press enter to back to menu",500,150,15,WHITE);
    DrawText("Press SPACE to back to game",500,200,15,WHITE);

}
void Devinfo(){
    ClearBackground(BLACK);
    DrawText("DEV INFO",500,200,60,WHITE);
    DrawText("1.AliRje:",350,300,25,WHITE);
    DrawText("2.AmirrezaKH:",350,350,25,WHITE);
    DrawText("Press esc to back to menu",500,500,15,WHITE);
}

void choose(int k){
    if(k==0){
    return enter();
    }else if(k==1){
    return menu();
    }else if(k>=2 && k<=4 && help){
    return  Help(k);
   }/* else if(k==7)
    return MultiPlayer();
    */else if(k==6){
    return Devinfo();
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
    //Board game
    Texture2D Board=LoadTexture("resources/Board.png");
    //BOAT PLAYER 1
    Texture2D Boat1=LoadTexture("resources/boat1.png");
    //BOAT PLAYER 2
    Texture2D Boat2=LoadTexture("resources/boat2.png");
    //TAPAL HA

    //**********************************************************

    //AUDIO*************************************************
    InitAudioDevice();
    Sound boom=LoadSound("resources/entergame.wav");
    Music game=LoadMusicStream("resources/gamemusic.mp3");
    //******************************************************
    
    while(!windowsclose){
        

        if((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) && k!=6){ //khoroj az safhe
            exitwindowsreq=true;
        }
        if(IsKeyPressed(KEY_ENTER) && (k==0 || (k>=2 && k<=4))){ //rad shodan safhe hayi ke ba enter rad mishavand
            if(k==4) help=false;
            k++;

        }
        //MENU BAZI LOGIC
        if(IsKeyPressed(KEY_ONE) && k==1){
            if(help) k=2;
            else    k=5;
        }else if(IsKeyPressed(KEY_TWO) && k==1){
        //   k=7
        }else if(IsKeyPressed(KEY_THREE) && k==1){
            k=6;
        }
        //*****************************************
        if(k==6){ //Dev info logic
            if(IsKeyPressed(KEY_ESCAPE)) k=1;
        }
        //*****************************************
        BeginDrawing();
        

       if(exitwindowsreq && k!=5){
        Exit();

        }else if(k!=5){
        if(k==0 && entering){ // paksh seda vorodi
            PlaySound(boom);
            entering=false;
        }

        choose(k); // entekhab safhe namayesh
        }
        else if(k==5){
        UpdateMusicStream(game);
        //Music game
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
        DrawTexture(Boat1,0,0,WHITE);
        DrawTexture(Boat2,100,100,WHITE);
         if(exitwindowsreq){ //bargasht be menu az safhe asli
        Closemenu();
        if(IsKeyPressed(KEY_ENTER)){
            exitwindowsreq=false;
            k=1;
        }
        else if(IsKeyPressed(KEY_SPACE)){
            exitwindowsreq=false;
        }
       } 
        //***********************************************
        }
        EndDrawing();
        }
        UnloadTexture(Board);
        UnloadTexture(Boat1);
        UnloadTexture(Boat2);
        UnloadMusicStream(game);
        UnloadSound(boom);
        CloseAudioDevice();
        CloseWindow();
        
}
