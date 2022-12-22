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
//**********************

//Screen Functions
void enter(){
    ClearBackground(BLACK);
    DrawText("MEET IN THE MIDDLE",300,350,55,WHITE);
    DrawText("Press Enter to Countinue...",450,400,20,GRAY);
}
void menu(){
    ClearBackground(WHITE);
    DrawText("1.offline mode",450,200,50,BROWN);

}
void Exit(){
    DrawRectangle(0,0,1280,800,WHITE);
    DrawText("Are U Sure darling ?! Y/N",110,350,60,BLACK);
            
    if(IsKeyPressed(KEY_N)){
        exitwindowsreq=false; 
    } 
    else if(IsKeyPressed(KEY_Y)){
        windowsclose=true;
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

    }

}
void Closemenu(){

}

void choose(int k){
    if(k==0){
    return enter();
    }else if(k==1){
    return menu();
    }if(k>=2 && k<=4){
        Help(k);
    }
}
//****************

//Game Functions

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
        
}
