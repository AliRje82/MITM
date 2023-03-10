// Libery *******************
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//**************************
// Board game****************
int board[9][9];
// flags*****************
bool help = true;
bool exitwindowsreq = false;
bool windowsclose = false;
bool entering = true;
bool CloseGame = false;
bool player1w;
int framecounter;
const char hacked[15]="You Are Hacked";
int cardtemp;
int crack;
//**********************
// Structs***********************
struct ship
{
    int x;
    int y;
    bool play;
    bool win;
};

struct player
{
    int cards[4]; //khone 0 = zarib khone 1 = tass mojadad khone 2 = dar baste khone 3 = mahdodiat
    struct ship ship1;
    struct ship ship2;
    bool close;
} player1, player2;

//*******************************
int fcounter = 0;
float alpha = 0.1;
// Screen Functions
void enter(Texture2D texture)
{
    fcounter++;
    if (fcounter == 7 && alpha != 1)
    {
        fcounter = 0;
        alpha += 0.1;
    }
    ClearBackground(BLACK);
    DrawTexture(texture, 0, 0, WHITE);
    DrawText("Press Enter to Countinue...", 450, 350, 30, Fade(BLUE, alpha));
}
void menu(Texture2D texture)
{
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
}
void Exit(Texture2D texture)
{
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
}
void Help(Texture2D texture)
{
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
    DrawText("1.shoma do ta ship ke hamon mohre bazie darin va bayad berin vasat va ganj ro be dast biarin :D",32,47,17,WHITE);
    DrawText("2.roye jazire ha ke berin beheton card shans mide ke badan mitonin dar moghe morede niaz azash estefade konin ;)",32,70,17,WHITE);
    DrawText("3.age to meh gir kardi az ye jaye dige dar miay ziad tajob nakon tofan to ro ba khodesh borde ye jaye dige ,",32,93,17,WHITE);
    DrawText("rasti onaro hefz kon chon tofan ha hamishe ye enteghal midan =)",32,116,17,WHITE);
    DrawText("4.Ba dokme D ya click roye shekl play mitoni tas bendazi :)",32,139,17,WHITE);
    DrawText("5. vaghti tas ro andakhti ba click roye mohrat mitoni harekat koni :O",32,162,17,WHITE);
}
void Closemenu(Texture2D texture)
{
    DrawTexture(texture, 0, 0, WHITE);
}
void Devinfo(Texture2D texture)
{
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
}
void win(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
    if(player1w){
        DrawText("1",906,487,30,WHITE);
    }else{
        DrawText("2",906,487,30,WHITE);
    }
}
void easter(Texture2D texture){
    ClearBackground(WHITE);
    DrawTexture(texture,0,0,WHITE);
    DrawText(TextSubtext(hacked,0,framecounter/20),431,156,60,RED);
    framecounter++;
}
char str[10];
void Lock(int a){
    itoa(a,str,10);
    for(int i=0;str[i];i++)
        str[i]+=crack;
}

int unlock(char lock[]){
    for(int i=0;lock[i];i++)
        lock[i]-=crack;
    return atoi(str);
}
void choose(int k, Texture2D texture)
{
    if (k == 0)
    {
        return enter(texture);
    }
    else if (k == 1)
    {
        return menu(texture);
    }
    else if (k == 2 && help)
    {
        return Help(texture);
    } /* else if(k==7)
      return MultiPlayer();
      */
    else if (k == 6)
    {
        return Devinfo(texture);
    }else if(k==9){
        return win(texture);
    }else if(k==11){
        return easter(texture);
    }
}
//****************

// Game Functions
const int dice_num = 1000;
int dice[1000];
void Randomize()
{
    srand((unsigned)time(NULL));
}
void dice_maker()
{
    int dic;
    for (int i = 0; i < dice_num; i++)
    {
        dic = rand() % 6;
        switch (dic)
        {
        case 0:
            dice[i] = -1;
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

int roll_dice()
{
    int ran_num = rand() % 1000;
    if (dice[ran_num] == 0)
    {
        return roll_dice();
    }
    else
    {
        int temp = dice[ran_num];
        dice[ran_num] = 0;
        return temp;
    }
}
int chancecard(int arr[],Sound chance)
{
    PlaySound(chance);
    int card = rand() % 4;
    arr[card]++;
    
    return card;
}
void corrider(int *x, int *y)
{
    if (*x == 8 || *x == 7)
    {
        if (*x == 7)
        {
            *x = 8;
            *y = 3;
            return;
        }
        else
        {
            *x = 7;
            *y = 6;
            return;
        }
    }
    else if (*x == 0 || *x == 1)
    {
        if (*x == 0)
        {
            *x = 1;
            *y = 3;
            return;
        }
        else
        {
            *x = 0;
            *y = 6;
            return;
        }
    }
    else if (*x == 6 || *x == 2)
    {
        if (*x == 6)
        {
            *x = 2;
            *y = 6;
            return;
        }
        else
        {
            *x = 6;
            *y = 2;
            return;
        }
    }
    else if (*x == 5 || *x == 3)
    {
        if (*x == 5)
        {
            *x = 3;
            *y = 2;
            return;
        }
        else
        {
            *x = 5;
            *y = 6;
            return;
        }
    }
    else if (*x == 4)
    {
        if (*y == 7)
        {
            *y = 1;
            return;
        }
        else
        {
            *y = 7;
            return;
        }
    }
}
int move(int dicetemp, struct ship *ship, int arr[],bool *card ,Sound beep,Sound chance)
{
    if (!(ship->x == 8 && ship->y + dicetemp < 0))
    {
        if (!(ship->x == 0 && ship->y + dicetemp > 8))
        {
            if (ship->x % 2 == 0)
            {
                ship->y += dicetemp;
                if (ship->y > 8)
                {
                    ship->y = 17 - ship->y;
                    ship->x--;
                }
                else if (ship->y < 0)
                {
                    ship->y = -ship->y - 1;
                    ship->x++;
                }
            }
            else
            {
                ship->y -= dicetemp;
                if (ship->y > 8)
                {
                    ship->y = 17 - ship->y;
                    ship->x++;
                }
                else if (ship->y < 0)
                {
                    ship->y = -ship->y - 1;
                    ship->x--;
                }
            }
            if (board[ship->x][ship->y] == 1)
                cardtemp=chancecard(arr,chance);
            if (board[ship->x][ship->y] == 2){
                if(!*card)
                corrider(&ship->x, &ship->y);
                else *card=false;
            }
            if (ship->x == 4 && ship->y == 4)
                ship->win = true;
            return 1;
        }
        else
        {
            ship->play = false;
            PlaySound(beep);
        }
    }
    else
    {
        ship->play = false;
        PlaySound(beep);
    }
    return 0;
}
void hitcheck(struct ship ship, struct ship *ship1, struct ship *ship2, Sound fall)
{
    if ((ship.x == ship1->x && ship.y == ship1->y && !ship1->win) || (ship.x == ship2->x && ship.y == ship2->y && !ship2->win))
    {
        if (ship.x == ship1->x && ship.y == ship1->y)
        {
            ship1->x = 0;
            ship1->y = 8;
            PlaySound(fall);
        }
        else
        {
            ship2->x = 0;
            ship2->y = 8;
            PlaySound(fall);
        }
    }
}

//**************

// Main Function
int main()
{
    // corriders are num 2 and chance home are num 1
    board[8][3] = board[7][6] = board[6][2] = board[5][6] = board[4][1] = board[4][7] = board[3][2] = board[2][6] = board[1][3] = board[0][6] = 2;
    board[1][0] = board[1][7] = board[2][2] = board[3][5] = board[5][3] = board[6][6] = board[7][1] = board[7][8] = 1;
    // Tool va arz safhe menu....
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int k = 0; // Screen button;
    // MUSIC*************
    float musictime = 1.0f;
    bool pausemusic = false;
    float volume = 0.5f;
    //******************

    InitWindow(screenWidth, screenHeight, "MEET IN THE MIDDLE");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    // Images ***************************************************
    
    // Safhe ha
    Texture2D Screan[12];
    Screan[11]=LoadTexture("resources/Easteregg.png");
    //winpage
    Screan[9]=LoadTexture("resources/win.png");
    // closemenu
    Screan[7] = LoadTexture("resources/closemenu.png");
    // exit
    Screan[8] = LoadTexture("resources/exit.png");
    // Menu
    Screan[1] = LoadTexture("resources/menu.png");
    // entering
    Screan[0] = LoadTexture("resources/Entering.png");
    // DEVINFO
    Screan[6] = LoadTexture("resources/devinfo.png");
    // HELP AND RULES
    Screan[2] = LoadTexture("resources/help.png");
    //load
    Screan[10] = LoadTexture("resources/loadsave.png");
    // Board game
    Texture2D Board = LoadTexture("resources/Board.png");
    // BOAT PLAYER 1
    Texture2D Boat1 = LoadTexture("resources/boat1.png");
    // BOAT PLAYER 2
    Texture2D Boat2 = LoadTexture("resources/boat2.png");
    // player section
    Texture2D num1 = LoadTexture("resources/1.png");
    Texture2D num2 = LoadTexture("resources/2.png");
    // Mouse
    struct mouse
    {
        int x;
        int y;
    } mouse;


    // AUDIO*************************************************
    InitAudioDevice();
    Sound select = LoadSound("resources/select.wav");
    Sound boom = LoadSound("resources/entergame.wav");
    Music game = LoadMusicStream("resources/gamemusic.mp3");
    Sound beep = LoadSound("resources/beep.wav");
    Sound fall = LoadSound("resources/fall.wav");
    Sound easter=LoadSound("resources/Hacked.wav");
    Sound chance=LoadSound("resources/chance.wav");
    Music men=LoadMusicStream("resources/Menuu.mp3");
    //******************************************************
    while (!windowsclose)
    {

        if ((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()) && k != 6 && k != 2 && k!=9 && k!=11)
        { // khoroj az safhe
            exitwindowsreq = true;
        }
        if (IsKeyPressed(KEY_ENTER) && k == 0)
        { // rad shodan safhe hayi ke ba enter rad mishavand
            k++;
            PlayMusicStream(men);
        }
        if(k==9 && (IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_ESCAPE))){
            k=1;
        }
        if(k==11 && IsKeyPressed(KEY_A)){
            k=1;
        }
        // MENU BAZI LOGIC
        if (k == 1)
        {
            UpdateMusicStream(men);
            
            if(GetMusicTimePlayed(men)/GetMusicTimeLength(men)==1){
                PlayMusicStream(men);
            }
            if(IsKeyPressed(KEY_S)){
                k=11;
                framecounter =0;
                PlaySound(easter);
            }
            mouse.x = GetMouseX();
            mouse.y = GetMouseY();
            if (923 <= mouse.x && mouse.x <= 1206)
            {

                if (260 <= mouse.y && mouse.y <= 330 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                { // singleplayer
                    k = 10;
                    PlaySound(select);
                }
                else if (mouse.y <= 408 && 338 <= mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                { // Multiplayer
                    //   k=7
                    PlaySound(select);
                }
                else if (417 <= mouse.y && mouse.y <= 487 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                { // Devinfo
                    k = 6;
                    PlaySound(select);
                }
                else if (496 <= mouse.y && mouse.y <= 566 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                { // Help
                    k = 2;
                    PlaySound(select);
                }
            }
            if (mouse.x <= 139 && 11 <= mouse.x && mouse.y <= 712 && 642 <= mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // exit
                exitwindowsreq = true;
        }
        // Help Logic***********************************
        if (k == 2)
        {
            mouse.x = GetMouseX();
            mouse.y = GetMouseY();
            if ((11 <= mouse.x && mouse.x <= 139 && mouse.y <= 712 && 642 <= mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_ESCAPE))
                k = 1;
        }
        //*********************************************
        if (k == 6)
        { // Dev info logic
            mouse.x = GetMouseX();
            mouse.y = GetMouseY();
            if (IsKeyPressed(KEY_ESCAPE) || (mouse.x <= 139 && 11 <= mouse.x && mouse.y <= 712 && 642 <= mouse.y && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
                k = 1;
        }
        //*****************************************
        BeginDrawing();
        if (exitwindowsreq && k != 5)
        {
            Exit(Screan[8]);
            mouse.x = GetMouseX();
            mouse.y = GetMouseY();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 412 <= mouse.x && mouse.x <= 578 && 396 <= mouse.y && mouse.y <= 439)
            {
                exitwindowsreq = false;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 701 <= mouse.x && mouse.x <= 867 && 396 <= mouse.y && mouse.y <= 439)
            {
                windowsclose = true;
                CloseGame = true;
            }
        }
        else if (k != 5 && k!=10)
        {
            if (k == 0 && entering)
            { // paksh seda vorodi
                PlaySound(boom);
                entering = false;
            }
            choose(k, Screan[k]);
        }else if(k==10){
            choose(1, Screan[1]);
            DrawTexture(Screan[10],0,0,WHITE);

        }
        EndDrawing();
        
        if(k==10){
        dice_maker();
        int dicetemp;
        int turn;
        bool roll;
        bool card;
        int tf;
        
//Load Game
        mouse.x=GetMouseX();
        mouse.y=GetMouseY();
        FILE *save;
        save=fopen("save//save.txt","r");
        if(save && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 670<=mouse.x && mouse.x<=840 && 273<=mouse.y && mouse.y<=320 ){
        PlaySound(select);
        FILE *cracked;
        cracked=fopen("save//crack.dat","rb");
        fread(&crack,1,sizeof(int),cracked);
        fclose(cracked);
        //player 1 save
        for(int l=0;l<4;l++){
        fscanf(save,"%s",str);
        player1.cards[l]=unlock(str);
        }
        fscanf(save,"%s",str);
        player1.ship1.x=unlock(str);
        fscanf(save,"%s",str);
        player1.ship1.y=unlock(str);
        fscanf(save,"%s",str);
        player1.ship2.x=unlock(str);
        fscanf(save,"%s",str);
        player1.ship2.y=unlock(str);
        fscanf(save,"%s",str);
        player1.ship1.play=unlock(str);
        fscanf(save,"%s",str);
        player1.ship1.win=unlock(str);
        fscanf(save,"%s",str);
        player1.ship2.play=unlock(str);
        fscanf(save,"%s",str);
        player1.ship2.win=unlock(str);
        fscanf(save,"%s",str);
        player2.close=unlock(str);


        for(int l=0;l<4;l++){
        fscanf(save,"%s",str);
        player2.cards[l]=unlock(str);
        }
        fscanf(save,"%s",str);
        player2.ship1.x=unlock(str);
        fscanf(save,"%s",str);
        player2.ship1.y=unlock(str);
        fscanf(save,"%s",str);
        player2.ship2.x=unlock(str);
        fscanf(save,"%s",str);
        player2.ship2.y=unlock(str);
        fscanf(save,"%s",str);
        player2.ship1.play=unlock(str);
        fscanf(save,"%s",str);
        player2.ship1.win=unlock(str);
        fscanf(save,"%s",str);
        player2.ship2.play=unlock(str);
        fscanf(save,"%s",str);
        player2.ship2.win=unlock(str);
        fscanf(save,"%s",str);
        player2.close=unlock(str);
        
        fscanf(save,"%s",str);
        turn=unlock(str);
        fscanf(save,"%s",str);
        dicetemp=unlock(str);
        fscanf(save,"%s",str);
        cardtemp=unlock(str);
        fscanf(save,"%s",str);
        roll=unlock(str);
        fscanf(save,"%s",str);
        card=unlock(str);


        k=5;
        musictime = 1.0f;
        }else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 482<=mouse.x && mouse.x<=652 && 273<=mouse.y && mouse.y<=320){
//Game data reset *******************************************************************************************
        PlaySound(select);
        player1.ship1.x = player1.ship2.x = 8;
        player1.ship1.y = player1.ship2.y = 0;
        player1.ship1.play = true;
        player1.ship2.play = true;
        player1.ship1.win = player1.ship2.win = false;
        player1.cards[0] =player1.cards[1] =player1.cards[2] = player1.cards[3] = 0;
        
        player1.ship1.play = player2.ship1.play = player2.ship2.play = player1.ship2.play = true;
        player1.close=player2.close=false;

        player2.ship2.win = player2.ship1.win = false;
        player2.ship1.play = true;
        player2.ship2.play = true;
        player2.ship1.x = player2.ship2.x = 0;
        player2.ship1.y = player2.ship2.y = 8;
        player2.cards[0] = player2.cards[1] = player2.cards[2] = player2.cards[3] = 0;
        dicetemp = 0;
        turn = 0;
        roll = true;
        card=false;
        musictime = 1.0f;
        cardtemp=-1;
        k=5;
        }
//************************************************************************************************************
        // Game LOOP
        
        while (k == 5)
        {
            BeginDrawing();
            UpdateMusicStream(game);
            // Music game*****************
            
            if (musictime >= 1.0)
            {
                PlayMusicStream(game);
                musictime = 0.0f;
            }
            musictime = GetMusicTimePlayed(game) / GetMusicTimeLength(game);            
            if (IsKeyPressed(KEY_UP) && volume < 1.0)
            {
                volume += 0.1;
                if (volume <= 1)
                    SetMusicVolume(game, volume);
            }
            if (IsKeyPressed(KEY_DOWN) && volume > 0.0)
            {
                volume -= 0.1;
                if (volume >= 0)
                    SetMusicVolume(game, volume);
            }
            if (IsKeyPressed(KEY_P))
            {
                pausemusic = true;
                if (pausemusic)
                    PauseMusicStream(game);
            }
            if (IsKeyPressed(KEY_R))
            {
                pausemusic = false;
                ResumeMusicStream(game);
            }
            // Board Game Screen
            ClearBackground(GRAY);
            DrawTexture(Board, 0, 0, WHITE);
            //CardTemp
            if(cardtemp==0){
                DrawText("You got A ",40,429,23,WHITE);
                DrawText("2X ",40,459,23,WHITE);
            }else if(cardtemp==1){
                DrawText("You got A tass",40,429,23,WHITE);
                DrawText("mojadad",40,459,23,WHITE);
            }else if(cardtemp==2){
                DrawText("You got A",40,429,23,WHITE);
                DrawText("No corrider ",40,459,23,WHITE);
            }else if(cardtemp==3){
                DrawText("You got A",40,429,23,WHITE);
                DrawText("mahdodiat",40,459,23,WHITE);
            }
            // SHOW TIME********************
            DrawText(TextFormat("%d", dicetemp), 126, 248, 30, WHITE); // DICE
            DrawText(TextFormat("%d", player1.cards[0]), 31, 112, 15, WHITE);
            DrawText(TextFormat("%d", player2.cards[0]), 31, 143, 15, WHITE);
            DrawText(TextFormat("%d", player1.cards[1]), 151, 112, 15, WHITE);
            DrawText(TextFormat("%d", player2.cards[1]), 151, 143, 15, WHITE);
            DrawText(TextFormat("%d", player2.cards[2]), 90, 143, 15, WHITE);
            DrawText(TextFormat("%d", player1.cards[2]), 90, 112, 15, WHITE);
            DrawText(TextFormat("%d", player2.cards[3]), 214, 143, 15, WHITE);
            DrawText(TextFormat("%d", player1.cards[3]), 214, 112, 15, WHITE);
            // PLAYER 1 *********************
            DrawTexture(Boat1, 456 + 77 * player1.ship1.y, 20 + 77 * player1.ship1.x, WHITE); // SHIP 1
            DrawTexture(Boat1, 456 + 77 * player1.ship2.y, 20 + 77 * player1.ship2.x, WHITE); // SHIP 2
            // PLAYER 2 **********************
            DrawTexture(Boat2, 456 + 77 * player2.ship1.y, 20 + 77 * player2.ship1.x, WHITE); // SHIP 1
            DrawTexture(Boat2, 456 + 77 * player2.ship2.y, 20 + 77 * player2.ship2.x, WHITE); // SHIP 2
            //*****************************************************
            if (turn % 2 == 0)
            {
                DrawTexture(num1, 210, 588, WHITE);
            }
            else
            {
                DrawTexture(num2, 210, 588, WHITE);
            }
            // LOGIC GAME*********************************

            mouse.x = GetMouseX();
            mouse.y = GetMouseY();
            if (((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= 82 && 30 <= mouse.x && mouse.y <= 697 && 645 <= mouse.y) || IsKeyPressed(KEY_D)) && roll)
            {
                dicetemp = roll_dice();
                roll = false;
            }
            if (turn % 2 == 0)
            { // player 1 turn
                mouse.x = GetMouseX();
                mouse.y = GetMouseY();
                if(player1.cards[0]>0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 8<=mouse.x && mouse.x<=65 && 6<=mouse.y && mouse.y<=102){
                    player1.cards[0]--;
                    dicetemp=dicetemp*2;
                }
                if(player1.cards[1]>0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 128<=mouse.x && mouse.x<=186 && 6<=mouse.y && mouse.y<=102){
                    player1.cards[1]--;
                    roll=true;
                }
                if(player2.cards[3]>0 && !card && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 191<=mouse.x && mouse.x<=248 && 6<=mouse.y && mouse.y<=102){
                    player2.cards[3]--;
                    card=true;
                }
                if(player1.cards[2]>0 && !player1.close && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 68<=mouse.x && mouse.x<=125 && 6<=mouse.y && mouse.y<=102){
                    player1.close=true;
                    player1.cards[2]--;
                }
                if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player1.ship1.y + 77) && (456 + 77 * player1.ship1.y) <= mouse.x && mouse.y <= (20 + 77 * player1.ship1.x + 77) && (20 + 77 * player1.ship1.x) <= mouse.y) && card){
                    card=false;
                    player1.ship1.play=false;
                }
                if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player1.ship2.y + 77) && (456 + 77 * player1.ship2.y) <= mouse.x && mouse.y <= (20 + 77 * player1.ship2.x + 77) && (20 + 77 * player1.ship2.x) <= mouse.y) && card){
                    card=false;
                    player1.ship2.play=false;
                }


                if ((((((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player1.ship1.y + 77) && (456 + 77 * player1.ship1.y) <= mouse.x && mouse.y <= (20 + 77 * player1.ship1.x + 77) && (20 + 77 * player1.ship1.x) <= mouse.y) && !roll && player1.ship1.play) || (!player1.ship2.play && !player1.ship2.win))&& !card)) && !player1.ship1.win)
                {
                    if (move(dicetemp, &player1.ship1, player1.cards,&player1.close,beep,chance))
                    {
                        hitcheck(player1.ship1, &player2.ship1, &player2.ship2, fall);
                        turn++;
                        roll = true;
                        player1.ship2.play = true;
                    }
                }
                else if ((((((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player1.ship2.y + 77) && (456 + 77 * player1.ship2.y) <= mouse.x && mouse.y <= (20 + 77 * player1.ship2.x + 77) && (20 + 77 * player1.ship2.x) <= mouse.y) && !roll && player1.ship2.play) || (!player1.ship1.play && !player1.ship1.win))&& !card)) && !player1.ship2.win)
                {
                    if (move(dicetemp, &player1.ship2, player1.cards,&player1.close,beep,chance))
                    {
                        hitcheck(player1.ship2, &player2.ship1, &player2.ship2, fall);
                        turn++;
                        roll = true;
                        player1.ship1.play = true;
                    }
                }
                if (!player1.ship1.play && !player1.ship2.play)
                {
                    turn++;
                    roll = true;
                    player1.ship1.play = true;
                    player1.ship2.play = true;
                }
            }
            else
            {

                mouse.x = GetMouseX();
                mouse.y = GetMouseY();
                if(player2.cards[0]>0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 8<=mouse.x && mouse.x<=65 && 6<=mouse.y && mouse.y<=102){
                    player2.cards[0]--;
                    dicetemp=dicetemp*2;
                }
                if(player2.cards[1]>0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 128<=mouse.x && mouse.x<=186 && 6<=mouse.y && mouse.y<=102){
                    player2.cards[1]--;
                    roll=true;
                }
                if(player1.cards[3]>0 && !card && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 191<=mouse.x && mouse.x<=248 && 6<=mouse.y && mouse.y<=102){
                    player1.cards[3]--;
                    card=true;
                }
                if(player2.cards[2]>0 && !player2.close && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 68<=mouse.x && mouse.x<=125 && 6<=mouse.y && mouse.y<=102){
                    player2.close=true;
                    player2.cards[2]--;
                }
                if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player2.ship1.y + 77) && (456 + 77 * player2.ship1.y) <= mouse.x && mouse.y <= (20 + 77 * player2.ship1.x + 77) && (20 + 77 * player2.ship1.x) <= mouse.y) && card){
                    card=false;
                    player2.ship1.play=false;
                }
                if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player2.ship2.y + 77) && (456 + 77 * player2.ship2.y) <= mouse.x && mouse.y <= (20 + 77 * player2.ship2.x + 77) && (20 + 77 * player2.ship2.x) <= mouse.y) && card){
                    card=false;
                    player2.ship2.play=false;
                }
                
                if ((((((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player2.ship1.y + 77) && (456 + 77 * player2.ship1.y) <= mouse.x && mouse.y <= (20 + 77 * player2.ship1.x + 77) && (20 + 77 * player2.ship1.x) <= mouse.y) && !roll && player2.ship1.play) || (!player2.ship2.play && !player2.ship2.win)) && !card)) && !player2.ship1.win)
                {
                    if (move(dicetemp, &player2.ship1, player2.cards,&player2.close,beep,chance))
                    {
                        hitcheck(player2.ship1, &player1.ship1, &player1.ship2, fall);
                        turn++;
                        roll = true;
                        player2.ship2.play = true;
                    }
                }
                else if ((((((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouse.x <= (456 + 77 * player2.ship2.y + 77) && (456 + 77 * player2.ship2.y) <= mouse.x && mouse.y <= (20 + 77 * player2.ship2.x + 77) && (20 + 77 * player2.ship2.x) <= mouse.y) && !roll && player2.ship2.play) || (!player2.ship1.play && !player2.ship1.win))&& !card)) && !player2.ship2.win)
                {
                    if (move(dicetemp, &player2.ship2, player2.cards,&player2.close,beep,chance))
                    {
                        hitcheck(player2.ship2, &player1.ship1, &player1.ship2, fall);
                        turn++;
                        roll = true;
                        player2.ship1.play = true;
                    }
                }
                if (!player2.ship1.play && !player2.ship2.play)
                {
                    turn++;
                    roll = true;
                    player2.ship1.play = true;
                    player2.ship2.play = true;
                }
            }
            //Winner winner chicken dinner*********************************************
            if((player1.ship1.win && player1.ship2.win) || (player2.ship1.win && player2.ship2.win)){
                
                if(player1.ship1.win && player1.ship2.win) player1w=true;
                else player1w=false;
                k=9;
            }
            //*********************************************
            if ((IsKeyPressed(KEY_ESCAPE) || WindowShouldClose()))
            { // khoroj az safhe
                exitwindowsreq = true;
            }
            if (exitwindowsreq)
            { // bargasht be menu az safhe asli
                Closemenu(Screan[7]);
                mouse.x = GetMouseX();
                mouse.y = GetMouseY();
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 472 <= mouse.x && mouse.x <= 808 && 370 <= mouse.y && mouse.y <= 428)
                {
                    //save game
                    FILE *save;
                    save=fopen("save//save.txt","w");
                    FILE *cracked;
                    cracked=fopen("save//crack.dat","wb");
                    crack=rand()%91+10;
                    fwrite(&crack,1,sizeof(int),cracked);
                    fclose(cracked);
                    //player 1 save text
                    for(int l=0;l<4;l++){
                        Lock(player1.cards[l]);
                        fprintf(save,"%s\n",str);
                    }
                    Lock(player1.ship1.x);
                    fprintf(save,"%s\n",str);
                    Lock(player1.ship1.y);
                    fprintf(save,"%s\n",str);
                    Lock(player1.ship2.x);
                    fprintf(save,"%s\n",str);
                    Lock(player1.ship2.y);
                    fprintf(save,"%s\n",str);
                    if(player1.ship1.play) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player1.ship1.win) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player1.ship2.play) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player1.ship2.win) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player1.close) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);


                    for(int l=0;l<4;l++){
                        Lock(player2.cards[l]);
                        fprintf(save,"%s\n",str);
                    }
                    Lock(player2.ship1.x);
                    fprintf(save,"%s\n",str);
                    Lock(player2.ship1.y);
                    fprintf(save,"%s\n",str);
                    Lock(player2.ship2.x);
                    fprintf(save,"%s\n",str);
                    Lock(player2.ship2.y);
                    fprintf(save,"%s\n",str);
                    if(player2.ship1.play) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player2.ship1.win) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player2.ship2.play) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player2.ship2.win) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(player2.close) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);

                    Lock(turn);
                    fprintf(save,"%s\n",str);
                    Lock(dicetemp);
                    fprintf(save,"%s\n",str);
                    Lock(cardtemp);
                    fprintf(save,"%s\n",str);
                    if(roll) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);
                    if(card) tf=1;
                    else tf=0;
                    Lock(tf);
                    fprintf(save,"%s\n",str);

                    fclose(save);
                    exitwindowsreq = false;
                    k = 1;
                }
                else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 472 <= mouse.x && mouse.x <= 808 && 292 <= mouse.y && mouse.y <= 350)
                {
                    exitwindowsreq = false;
                } 
                //******************************************************
            }
            EndDrawing();
        }
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
    UnloadSound(beep);
    UnloadSound(fall);
    UnloadTexture(num1);
    UnloadTexture(num2);
    UnloadTexture(Screan[11]);
    UnloadMusicStream(men);
    UnloadSound(chance);
    CloseAudioDevice();
    CloseWindow();
}
