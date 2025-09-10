#include <iostream>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include <thread>
#include "mapGenerator.h"
#include "mapGen.cpp"

 
//credit to stackOverflow and CPP forums

int randi(int lo, int hi)
{
    int n = hi - lo + 1;
    int i = rand() % n;
    if (i < 0) i = -i;
    return lo + i;
}

void screenGoto(int col, int row) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { static_cast<SHORT>(col), static_cast<SHORT>(row) };

    // Ustaw kursor w podanej pozycji
    SetConsoleCursorPosition(hConsole, coord);
}
void remove_scrollbar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}
char getCharAtPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char ch;
    DWORD charsRead;

    // Wczytaj znak z określonej pozycji
    COORD coord = { (SHORT)x, (SHORT)y };
    ReadConsoleOutputCharacterA(hConsole, &ch, 1, coord, &charsRead);

    return ch;  // Zwróć odczytany znak
}
void clearScreen() {
    system("CLS");
}

//end of credit :)



enum RoomType {
    squereRT,
    circleRT,
    end
};

//╔╩╦╠═╬¤



void drawSQRoom(int x, int y) {
    screenGoto(x+3, y+4); std::cout << '\315';
    screenGoto(x+4, y+4); std::cout << '\315';
    screenGoto(x+5, y+4); std::cout << '\315';
    screenGoto(x+6, y+4); std::cout << '\315';
    screenGoto(x+7, y+4); std::cout << '\315';
    screenGoto(x+8, y+4); std::cout << '\315';
    screenGoto(x+9, y+4); std::cout << '\315';
    screenGoto(x+10, y+4); std::cout << '\315';
    screenGoto(x+11, y+4); std::cout << '\315';
    screenGoto(x+12, y+4); std::cout << '\315';
    screenGoto(x+13, y+4); std::cout << '\315';
    screenGoto(x+14, y+4); std::cout << '\315';
    screenGoto(x+15, y+4); std::cout << '\315';
    screenGoto(x+16, y+4); std::cout << '\315';
    screenGoto(x+17, y+4); std::cout << '\315';
    screenGoto(x+18, y+4); std::cout << '\315';
    screenGoto(x+19, y+4); std::cout << '\315';
    screenGoto(x+20, y+4); std::cout << '\315';
    screenGoto(x+21, y+4); std::cout << '\315';
    screenGoto(x+22, y+4); std::cout << '\315';
    screenGoto(x+23, y+4); std::cout << '\315';
    screenGoto(x+24, y+4); std::cout << '\315';

    screenGoto(x+2, y+4); std::cout << '\311';

    screenGoto(x+2, y+5); std::cout << '\272';
    screenGoto(x+2, y+6); std::cout << '\272';
    screenGoto(x+2, y+7); std::cout << '\272';
    screenGoto(x+2, y+8); std::cout << '\272';
    screenGoto(x+2, y+9); std::cout << '\272';
    screenGoto(x+2, y+10); std::cout << '\272';
    screenGoto(x+2, y+11); std::cout << '\272';
    screenGoto(x+2, y+12); std::cout << '\272';
    screenGoto(x+2, y+13); std::cout << '\272';
    screenGoto(x+2, y+14); std::cout << '\272';

    screenGoto(x+2, y+14); std::cout << '\310';

    screenGoto(x+3,y +14); std::cout << '\315';
    screenGoto(x+4,y +14); std::cout << '\315';
    screenGoto(x+5,y +14); std::cout << '\315';
    screenGoto(x+6,y +14); std::cout << '\315';
    screenGoto(x+7,y +14); std::cout << '\315';
    screenGoto(x+8,y +14); std::cout << '\315';
    screenGoto(x+9,y +14); std::cout << '\315';
    screenGoto(x+10,y +14); std::cout << '\315';
    screenGoto(x+11,y +14); std::cout << '\315';
    screenGoto(x+12,y +14); std::cout << '\315';//door
    screenGoto(x+13,y +14); std::cout << '\315';//door
    screenGoto(x+14,y +14); std::cout << '\315';//door
    screenGoto(x+15,y +14); std::cout << '\315';
    screenGoto(x+16,y +14); std::cout << '\315';
    screenGoto(x+17, y+14); std::cout << '\315';
    screenGoto(x+18, y+14); std::cout << '\315';
    screenGoto(x+19, y+14); std::cout << '\315';
    screenGoto(x+20, y+14); std::cout << '\315';
    screenGoto(x+21, y+14); std::cout << '\315';
    screenGoto(x+22, y+14); std::cout << '\315';
    screenGoto(x+23, y+14); std::cout << '\315';
    screenGoto(x+24, y+14); std::cout << '\315';

    screenGoto(x+25, y+4); std::cout << '\273';

    screenGoto(x+25,y +5); std::cout << '\272';
    screenGoto(x+25,y +6); std::cout << '\272';
    screenGoto(x+25,y +7); std::cout << '\272';
    screenGoto(x+25,y +8); std::cout << '\272';
    screenGoto(x+25, y+9); std::cout << '\272';
    screenGoto(x+25, y+10); std::cout << '\272';
    screenGoto(x+25, y+11); std::cout << '\272';
    screenGoto(x+25, y+12); std::cout << '\272';
    screenGoto(x+25, y+13); std::cout << '\272';
    screenGoto(x+25, y+14); std::cout << '\272';

    screenGoto(x+25, y+14); std::cout << '\274';
}

void drawRoom(int x, int y, int w,int l, RoomType roomType) {
    if (roomType == squereRT) {
        for (int i = 0; i < l; i++) {
            screenGoto(x, y + i); std::cout << '\272';
        }

        for (int i = 0; i < l; i++) {
            screenGoto(x + w, y + i); std::cout << '\272';
        }

        for (int i = 0; i < w; i++) {
            screenGoto(x + i, y); std::cout << '\315';
        }

        for (int i = 0; i < w; i++) {
            screenGoto(x + i, y + l); std::cout << '\315';
        }

        screenGoto(x, y); std::cout << "\311";
        screenGoto(x + w, y); std::cout << "\273";
        screenGoto(x, y + l); std::cout << "\310";
        screenGoto(x + w, y + l); std::cout << "\274";
    }
    else if (roomType == circleRT) {

        for (int i = 0; i < l; i++) { screenGoto(x + w, y + l - i); std::cout << '\272'; }
        for (int i = 0; i < l; i++) { screenGoto(x + w*2, y + l - i); std::cout << '\272'; }
        for (int i = 0; i < l; i++) { screenGoto(x + w*3, y + l*2 - i); std::cout << '\272'; }
        for (int i = 0; i < l; i++) { screenGoto(x + w*2, y + l*3 - i); std::cout << '\272'; }
        for (int i = 0; i < l; i++) { screenGoto(x + w, y + l*3 - i); std::cout << '\272'; }
        for (int i = 0; i < l; i++) { screenGoto(x , y + l*2 - i); std::cout << '\272'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w - i, y + l); std::cout << '\315'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w*3 - i, y + l); std::cout << '\315'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w*3 - i, y + l*2); std::cout << '\315'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w - i, y + l*2); std::cout << '\315'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w+i, y); std::cout << '\315'; }
        for (int i = 0; i < w; i++) { screenGoto(x + w+i, y+l*3); std::cout << '\315'; }

        screenGoto(x + w, y); std::cout << '\311';
        screenGoto(x, y+l); std::cout << '\311';
        screenGoto(x+w, y+l); std::cout << '\274';
        screenGoto(x+w*2, y); std::cout << '\273';
        screenGoto(x+w*3, y+l); std::cout << '\273';
        screenGoto(x+w*2, y+l); std::cout << '\310';
        screenGoto(x+w*3,y+l*2); std::cout << '\274';
        screenGoto(x,y+l*2); std::cout << '\310';
        screenGoto(x+w,y+l*2); std::cout << '\273';
        screenGoto(x+w*2,y+l*2); std::cout << '\311';
        screenGoto(x+w,y+l*3); std::cout << '\310';
        screenGoto(x+w*2,y+l*3); std::cout << '\274';
    }
}

void drawCorridor(int x, int y, int len) {


    for (int i = 0; i < len; i++) {
        screenGoto(x , y); std::cout << " ";
        screenGoto(x+len-1 , y); std::cout << " ";
        screenGoto(x , y); std::cout << "\0";
        screenGoto(x+len-1 , y); std::cout << "\0";
        screenGoto(x + i, y + 1); std::cout << '\315';//coridor char
        screenGoto(x + i, y - 1); std::cout << '\315';//coridor char
        screenGoto(x+i, y); std::cout << '\0';
    }
    screenGoto(x, y + 1); std::cout << '\311';
    screenGoto(x, y - 1); std::cout << '\310';

    screenGoto(x + len-1, y+1); std::cout << '\273';
    screenGoto(x + len-1, y-1); std::cout << '\274';
}

bool isntMapChar(char ch) {
    char mapChars[] = { '\273','\274','\272','\271','\310','\311','\312','\313','\314','\315','\316','\317','\257',
        '\256','\263','='};

    for (int i = 0; i < sizeof(mapChars); i++) {
        if (mapChars[i] == ch) {
            return true;
        }
    }
    return false;

}

void printMapChars() {
    std::cout << '\273' << "  ";
    std::cout << '\274' << "  ";
    std::cout << '\272' << "  ";
    std::cout << '\271' << "  ";
    std::cout << '\310' << "  ";
    std::cout << '\311' << "  ";
    std::cout << '\312' << "  ";
    std::cout << '\313' << "  ";
    std::cout << '\314' << "  ";
    std::cout << '\315' << "  ";
    std::cout << '\316' << "  ";
    std::cout << '\317' << "  ";

    std::cout << '\257' << "  ";
    std::cout << '\256' << "  ";

    std::cout << '\263' << "  ";
}

void dispMap() {
    screenGoto(2, 2);
    
    //printMapChars();
   

    drawSQRoom(4,4);
    drawRoom(30, 10, 30, 6,squereRT);
   
    drawCorridor( 4+25, 13, 2);

    drawRoom(61, 7, 8, 4,circleRT);
    drawCorridor(60, 13, 2);


}

void spawnItems() {
    screenGoto(randi(33,28), 11); std::cout << '\277';
}

//hi

void shoot(char player, int playerX, int playerY)
{
    int ammoX, ammoY;
    int ammoLifetime = 10;
    ammoX = playerX;
    ammoY = playerY;

    if (player == '>') {
        ammoX++;
        bool wallf = true;
        
        ammoLifetime = 10;

        while (wallf)
        {
            
            screenGoto(ammoX= ammoX + 1, ammoY); std::cout << "-";
            ammoLifetime--;
            screenGoto(ammoX - 1, ammoY); std::cout << ' ';
            Sleep(50);

            if (ammoLifetime == 0) {break;}
            if (!getCharAtPosition(ammoX+1, ammoY)==' ') { break; }
            
        }
    }
    else if (player == '<') {
        ammoX--;
        bool wallf = true;

        ammoLifetime = 10;

        while (wallf)
        {

            screenGoto(ammoX = ammoX - 1, ammoY); std::cout << "-";
            ammoLifetime--;
            screenGoto(ammoX + 1, ammoY); std::cout << ' ';
            Sleep(50);
           
            if(ammoLifetime < 7){ screenGoto(ammoX - 1, ammoY); std::cout << ' '; }
            
            if (ammoLifetime == 0) { break; }
            if (!isntMapChar(getCharAtPosition(ammoX -2, ammoY))) { break; }


            
        }
    }
    else if (player == 'v') {
        ammoY++;
        bool wallf = true;

        ammoLifetime = 3;

        while (wallf)
        {
            std::cout << ' ';
            screenGoto(ammoX, ammoY= ammoY +2); std::cout << "|";
            std::cout << ' ';
            ammoLifetime--;
            std::cout << ' ';
            screenGoto(ammoX, ammoY= ammoY -1); std::cout << ' ';
            Sleep(50);
            std::cout << ' ';

            screenGoto(ammoX, ammoY+1); std::cout << ' ';

            if (ammoLifetime == 0) {
                std::cout << ' ';  break;
            }
            if (!isntMapChar(getCharAtPosition(ammoX, ammoY+2))) { break; }

        }

        
    }
    else if (player == '^') {
        ammoY--;
        bool wallf = true;

        ammoLifetime = 3;

        while (wallf)
        {
            screenGoto(ammoX, ammoY = ammoY - 2); std::cout << "|";
            ammoLifetime--;
            screenGoto(ammoX, ammoY = ammoY + 1); std::cout << ' ';
            Sleep(50);
            screenGoto(ammoX, ammoY - 1); std::cout << ' ';
            if (ammoLifetime == 0) { break; std::cout << ' ';
            }

            if (!isntMapChar(getCharAtPosition(ammoX, ammoY-2))) { break; }


        }

    }

}

void papaj() {
    std::cout << R"(
-=++========-------:::.......................................:-===================-------=
::-=========-------::........... ...........................::------===========++====+====
:::----=---------::.............               ..............:::-----:---====+++++++++===+
::::::::::::::-::............                   ..........:::::.:::::----=====++++++++++++
::::::::::::................                      .........:::::::::-----==========-------
::::::::::..............                           ......::::::::::::::---==+=-----::-----
:::::::.............                                .......::::::..::::::---------::------
::::............            .::---:::.....          ...............::::::-------::::------
:::............           :=======---:::::...         ............::::::--:::::::::-------
-::::.........          -++***#***++==----:----:.             ....:::::--::::::::---------
-::::.......          :*#*##***++=+==----::::---=:.       ... ....:::---::::::::::--------
:::::......          =#####****+++====-------------:       .......::::--:::::::::::--:::--
::::......         .*%%#####***+++==-=--::--:::---:::.      .......::::::::::::------::::-
:::......          =%%%%%#%##***++=---------::::------.     ...........::::::--------:::--
.........          +%%%%%%%####**+==-----------------=-      .....::::::::::----------:---
........         . *%%%%%%%####**+========-----------=-      .....:::::-------========----
:.....          +%%#%%%%%%%#******+==--===--------====.       .....::::------===========--
:.....          #%%%%%%%%%%%#####***+==+====-------==-        .....::::------=============
......          =%#%%%%%%%#%%%###%%%#+++***++===------        .....:::------==========+===
......           ##%%%%%%#***#*+**###=-+#####**=---=--        .....:::-----===============
......           =%%%%%%%#**+++++*##*---=+++====---=-.        ....::::-----======--=======
:......          .#%%%%%%##**+==+#%#+--====---------:         ....:::------=====-----=====
:::....           :++%%%%%##*****#%*=--=+++==------:         ....::::------=====-------===
:::.....           .+%%%%%###***#%%#*+===+**+==--=-         .....::::-----=======-----====
::::....       .-=+%%%%%%%#**#######*+---=+**+==-          .....:::::-----====------======
::::....     :#%%%%%%%%%%%#*+######**++===+====-           .....:::::----=======-----=--==
:::::...    :#%%%%%%%%%%%%%#**####*+====--====-           .....:::::----=========----::---
:::::.... .+%%%%%%%#%%%%%%%%#*****++=====-===:           .....:::::-----========----------
:::::...-*%%%%%%%%%%%%%%%%%%%##****===-=====-          ......::::--------=====-=---=------ 
:::::=*%%%%%%%%%%%%%%%%%%%%%####***++++==+=-#=.        ......::::--------======--==-------
::=*%#%#%##%%%%%%%%%%%%%%%##########**=---.-%#**+-............:::--------=====---===----==
*%%%#%%#%*######%%%#*%%%%%%***+++===-:..::..=#####**+=-....::::---------=-------=======---
%%%%%%%%%%%####%%%#*##%%%%#+--------.........-###**+#+*=::::--------=====-----=--=======--
%%%%%%%%#%%%##%%%#*######*=:.........::...=-..:*##*******=----------====---------========-
%%%%%#####%%##%%%#%%##**=--:.........::   ..:...=####++*##+---------===-----------=======-
            )";
}

void renderTooltips() {
    screenGoto(1, 1); std::cout << "1-Controls";
}

void spawnEnemy(int x,int y, char type, bool canShoot,char enemyChar,int lifetime,int moveRange, int hp) {

    /*
    ENEMY TYPES:
    U - moves up and down
    L - moves left and right

    LIFETIME:
    0 -> until shoot
    1-1000 -> time in seconds
    */

    int enemyX = x;
    int enemyY = y;

    int eHp = hp;


    int movesLeft=0;
    while (eHp > 0){
        if (type == 'U' &&lifetime==0)
        {
            
            movesLeft = moveRange;
            while (movesLeft !=0)
            {
                
                y--;
                screenGoto(x, y + 1);std::cout << " ";
                screenGoto(x, y);
                std::cout << enemyChar;
                movesLeft--;
                Sleep(1000);

            }
            movesLeft = moveRange;
            while (movesLeft != 0) {
                y++;
                screenGoto(x, y - 1);std::cout << " ";
                screenGoto(x, y);
                std::cout << enemyChar;
                movesLeft--;
                Sleep(1000);

                
            }

        }
    }
    
   

}

void clearPlayerBack(char player,int playerPosY,int playerPosX) {
    if (player == '>') { screenGoto(playerPosX-1, playerPosY); std::cout << " "; }
    if (player == '<') { screenGoto(playerPosX+1, playerPosY); std::cout << " "; }
    if (player == '^') { screenGoto(playerPosX, playerPosY+1); std::cout << " "; }
    if (player == 'v') { screenGoto(playerPosX, playerPosY-1); std::cout << " "; }
}

bool isPlayerPathFree(int playerPosX, int playerPosY, char player) {
    if (player == '>') { return !isntMapChar(getCharAtPosition(playerPosX+1, playerPosY)); }
    if (player == '<') { return !isntMapChar(getCharAtPosition(playerPosX - 1, playerPosY)); }
    if (player == '^') { return !isntMapChar(getCharAtPosition(playerPosX,  playerPosY-1)); }
    if (player == 'v') { return !isntMapChar(getCharAtPosition(playerPosX, playerPosY+1)); }
}



void mainGame() {
    bool canPlayerShoot = true;
    clearScreen();

    remove_scrollbar();
    clearScreen();
    spawnItems();
    renderTooltips();

    
    std::string inp = " ";

    //eq.dispAllEQ();
    //std::cout << eq.eqItems[0].id;
    int playerPosX = 10, playerPosY = 10;

    char player = '>';

    dispMap();


    while (true) {

       

        std::cout << ' ';

        

        screenGoto(playerPosX, playerPosY); std::cout << player;
        
        screenGoto(2, 2);
        Sleep(50);
        inp = getch();
        

        screenGoto(2, 2);
        std::cout << getCharAtPosition(playerPosX, playerPosY);//debug

        //if(isntMapChar(getCharAtPosition(playerPosX, playerPosY))) { playerPosX = 10; playerPosY = 10; }
       
           
        
        

        if (true) {

            

            if (inp == "D" || inp == "d")
            {

                playerPosX = playerPosX + 1;
                player = '>';
                clearPlayerBack(player, playerPosY, playerPosX);
            }
            else if (inp == "W" || inp == "w")
            {
                playerPosY = playerPosY - 1;
                player = '^'; 
                clearPlayerBack(player, playerPosY, playerPosX);
            }
            else if (inp == "S" || inp == "s")
            {
                playerPosY = playerPosY + 1;
                player = 'v';

                clearPlayerBack(player, playerPosY, playerPosX);
            }
            else if (inp == "A" || inp == "a")
            {
                playerPosX = playerPosX - 1; 
                player = '<';
                clearPlayerBack(player, playerPosY, playerPosX);
            }
            else if (inp == "O" || inp == "o")
            {
                if (canPlayerShoot)
                {
                    std::thread(shoot,player, playerPosX, playerPosY).join();

                }
            }
            else if (inp == "`") {

                screenGoto(1, 1); std::cout << "CONSOLE IS NOT DONE YET";
                            
            }     
            else if (inp == "12") //FIX
            {
                clearScreen();
                std::cout << "KEY SETTINGS:\n";
                std::cout << "w,a,s,d - movement\n";
                std::cout << "o - shoot\n";
                std::cout << "1 - displays this menu\n";
                std::cout << "exit - exits the game\n";

                std::cout << "This menu vanishes in 5 sec \n";
                Sleep(5 * 1000);
                clearScreen();

            }
            else if (inp == "2137") { papaj(); Sleep(1000); break; }
            if (inp == "EXIT" || inp == "exit") { clearScreen(); break; }
            
            if (!isPlayerPathFree(playerPosX, playerPosY, player)) { playerPosX = 10; playerPosY = 10; }

            
        }

        

    }
}


void logo() {
    screenGoto(1, 1); std::cout << "      :::::::::   :::::::::::       ::::::: ";
    screenGoto(1, 2); std::cout << "     :+:    :+:  :+:     :+:      :+:   :+: ";
    screenGoto(1, 3); std::cout << "    +:+    +:+         +:+       +:+   +:+  ";
    screenGoto(1, 4); std::cout << "   +#++:++#+         +#+        +#+   +:+   ";
    screenGoto(1, 5); std::cout << "  +#+              +#+         +#+   +#+  ";
    screenGoto(1, 6); std::cout << " #+#             #+#          #+#   #+# ";
    screenGoto(1, 7); std::cout << "###             ###           ####### ";
}
void numRainfall(int a,int b) {
    for (int i = 0; i < b; i++) {
        screenGoto(1, 1 + a); std::cout << rand() << "\n";
        screenGoto(5, 1 + a); std::cout << rand() << "\n";
        screenGoto(10, 1 + a); std::cout << rand() << "\n";
        screenGoto(15, 1 + a); std::cout << rand() << "\n";
        screenGoto(20, 1 + a); std::cout << rand() << "\n";
        screenGoto(25, 1 + a); std::cout << rand() << "\n";
        screenGoto(30, 1 + a); std::cout << rand() << "\n";
        screenGoto(35, 1 + a); std::cout << rand() << "\n";
        screenGoto(40, 1 + a); std::cout << rand() << "\n";
        screenGoto(45, 1 + a); std::cout << rand() << "\n";
    }
    
}

void mainMenu() {
    std::string input;

    
    std::cout <<"\n" << "CONSOLE GAME\n";
    std::cout << "1-play 2-credits 3-settings 4-exit \n\n";

    std::cin >> input;
    if (input == "1")
    {

        std::thread enemyT(spawnEnemy, 45, 14, 'U', true, 'X', 0, 2, 100);
        std::thread gameT(mainGame);

        gameT.join();
        enemyT.join();

    }
    else if(input == "2") {
        clearScreen();
        screenGoto(1, 1); std::cout << " ::::::::  :::::::::  :::::::::: :::::::::  ::::::::::: :::::::::::  ::::::::  ";
        screenGoto(2, 2); std::cout << ":+:    :+: :+:    :+: :+:        :+:    :+:     :+:         :+:     :+:    :+: ";
        screenGoto(3, 3); std::cout << "+:+        +:+    +:+ +:+        +:+    +:+     +:+         +:+     +:+        ";
        screenGoto(4, 4); std::cout << "+#+        +#++:++#:  +#++:++#   +#+    +:+     +#+         +#+     +#++:++#++ ";
        screenGoto(5, 5); std::cout << "+#+        +#+    +#+ +#+        +#+    +#+     +#+         +#+            +#+ ";
        screenGoto(6, 6); std::cout << "#+#    #+# #+#    #+# #+#        #+#    #+#     #+#         #+#     #+#    #+# ";
        screenGoto(7, 7); std::cout << " ########  ###    ### ########## #########  ###########     ###      ########  ";

        std::cout << "\n\nMAIN PROGRAMMER - MATEUSZ WITCZAK  (@pozdro70 - TIKTOK) \n";
        std::cout << "GAME IDEA - BARTOSZ PILECKI (Revan - STEAM) \n";

        std::cout << "\n 'enter' to go back \n";

        if(getch() == '1'){}
        clearScreen();
        
        logo();
        std::cout << "\n";
        mainMenu();
    }
    else if (input == "3") {
        clearScreen();
        int i = 8, a = 0;
        while (i > 0) {
            numRainfall(a,1); numRainfall(a, 1);

            
            Sleep(50);
            i--;
            a++;
        }
        screenGoto(1, 1); std::cout << "::::::::  :::::::::: ::::::::::: ::::::::::: ::::::::::: ::::    :::  ::::::::   ::::::::  ";        Sleep(50);
        screenGoto(1, 2); std::cout << ":+:    :+: :+:            :+:         :+:         :+:     :+:+:   :+: :+:    :+: :+:    :+: ";        Sleep(50);
        screenGoto(1, 3); std::cout << "+:+        +:+            +:+         +:+         +:+     :+:+:+  +:+ +:+        +:+        ";        Sleep(50);
        screenGoto(1, 4); std::cout << "+#++:++#++ +#++:++#       +#+         +#+         +#+     +#+ +:+ +#+ :#:        +#++:++#++ ";        Sleep(50);
        screenGoto(1, 5); std::cout << "       +#+ +#+            +#+         +#+         +#+     +#+  +#+#+# +#+   +#+#        +#+ ";        Sleep(50);
        screenGoto(1, 6); std::cout << "#+#    #+# #+#            #+#         #+#         #+#     #+#   #+#+# #+#    #+# #+#    #+# ";        Sleep(50);
        screenGoto(1, 7); std::cout << " ########  ##########     ###         ###     ########### ###    ####  ########   ########  ";        Sleep(50);
        screenGoto(1, 8); std::cout << "                                                                                            ";        Sleep(50);
        Sleep(50);
        std::cout << "\n\n 'enter' to go back \n";

        if (getch() == '1') {}
        clearScreen();

        logo();
        std::cout << "\n";
        mainMenu();
    }

}




void dispMenu()
{
    
    int i = 8, a = 0;
    while (i > 0) {
        numRainfall(a,1);

        Sleep(50);



        i--;
        a++;
    }

    screenGoto(1, 1); std::cout << "                                                          "; Sleep(50);
    screenGoto(1, 2); std::cout << "      :::::::::   :::::::::::       :::::::                "; Sleep(50);
    screenGoto(1, 3); std::cout << "     :+:    :+:  :+:     :+:      :+:   :+:                "; Sleep(50);
    screenGoto(1, 4); std::cout << "    +:+    +:+         +:+       +:+   +:+                 "; Sleep(50);
    screenGoto(1, 5); std::cout << "   +#++:++#+         +#+        +#+   +:+                  "; Sleep(50);
    screenGoto(1, 6); std::cout << "  +#+              +#+         +#+   +#+                   "; Sleep(50);
    screenGoto(1, 7); std::cout << " #+#             #+#          #+#   #+#                    "; Sleep(50);
    screenGoto(1, 8); std::cout << "###             ###           #######                      "; Sleep(50);
    screenGoto(35, 9); std::cout << "                                                           "; Sleep(50);
    Sleep(50);
    mainMenu();
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    dispMenu();

}
