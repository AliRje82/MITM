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
        DrawText("3.CsadasdadOn your Mohre to move it",100,250,20,WHITE);
        DrawText("Press Enter to exit the Help Menu",100,350,30,WHITE);
        help=false;

    }

}
void Closemenu(){
    DrawRectangle(320,200,100,200,BLACK);

}

void choose(int k){
    if(k==0){
    return enter();
    }else if(k==1){
    return menu();
    }else if(k>=2 && k<=4 && help){
    return  Help(k);
   }/* else if(k==5)
    return MultiPlayer();
    else if(k==6){
    return Devinfo()
    }*/
}
//****************

//Game Functions
const int dice_num = 1000;
int dice[dice_num];
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

int main() {
    dice_maker();
    for(int i = 0; i < 100; i++) {
        int k = roll_dice();
        printf("%d\n", k);
    }
}

//**************

//Main Function
int main()
{
    //Tool va arz safhe menu....
    const int screenWidth = 1280; 
    const int screenHeight = 800;
    int k=0; //Screen button;

    InitWindow(screenWidth, screenHeight, "MEET IN THE MIDDLE");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    //Board game ***********************************************

    //**********************************************************

    //AUDIO*************************************************
    InitAudioDevice();
    Sound boom=LoadSound("resources/entergame.wav");

    //******************************************************
    
    while(!windowsclose){
        

        if(IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()){ //khoroj az safhe
            exitwindowsreq=true;
        }
        if(IsKeyPressed(KEY_ENTER) && (k==0 || (k>=2 && k<=4))){ //rad shodan safhe hayi ke ba enter rad mishavand
            k++;
        }
        if(IsKeyPressed(KEY_ONE) && k==1){ //safhe menu bazi
            k=2;
        }else if(IsKeyPressed(KEY_TWO) && k==1){
        //   k=5
        }else if(IsKeyPressed(KEY_THREE) && k==1){
        //    k=6
        }
        BeginDrawing();
        
       if(exitwindowsreq){
        Exit(exitwindowsreq,windowsclose);

        }else{

        if(k==0 && entering){ // paksh seda vorodi
            PlaySound(boom);
            entering=false;
        }

        choose(k); // entekhab safhe namayesh
        }
        EndDrawing();
        }
        //Payan safhe avalie :D
        UnloadSound(boom);
        CloseAudioDevice();
        CloseWindow();
        //Shoro safhe bazi
        if(!CloseGame){
        //Flags*********************
        bool exitwindowsreq=false;
        bool windowsclose=false;
        //**************************
        InitWindow(screenWidth,screenHeight,"Meet in the middle");
        //Sound Game************************
        InitAudioDevice();
        Sound game=LoadSound("resources/");
        //**********************************
        while(!windowsclose){
        if(IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()){ //khoroj az safhe
            exitwindowsreq=true;
        }
            BeginDrawing();
            if(exitwindowsreq) //Menu Khoroji
                Closemenu();
            else{//Game Screen
                ClearBackground(WHITE);

                
            }
            EndDrawing();
            
        }
    }
        
}
