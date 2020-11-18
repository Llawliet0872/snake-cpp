//########################
//       SNAKE          ##
//########################

#include <iostream>
#include <graphics.h>
#include <time.h>

//COLOR               INT VALUES
//-------------------------------
//BLACK                   0
//BLUE                    1
//GREEN                   2
//CYAN                    3
//RED                     4
//MAGENTA                 5
//BROWN                   6
//LIGHTGRAY               7
//DARKGRAY                8
//LIGHTBLUE               9
//LIGHTGREEN             10
//LIGHTCYAN              11
//LIGHTRED               12
//LIGHTMAGENTA           13
//YELLOW                 14
//WHITE                  15

//PATTERN              INT VALUES
//-------------------------------
//EMPTY_FILL               0
//SOLID_FILL               1
//LINE_FILL                2
//LTSLASH_FILL             3
//SLASH_FILL               4
//BKSLASH_FILL             5
//LTBKSLASH_FILL           6
//HATCH_FILL               7
//XHATCH_FILL              8
//INTERLEAVE_FILL          9
//WIDE_DOT_FILL           10
//CLOSE_DOT_FILL          11
//USER_FILL               12

bool gameOver = false;

void endGame()
{
    gameOver = true;
    cleardevice();
}

int main()
{
    short refRate = 50;
    short speed = 5;
    unsigned short x[200];
    unsigned short y[200];
    x[0] = 200;
    y[0] = 200;
    short length = 1;
    short d;
    short dir;
    short foodX = 200;
    short foodY = 200;
    short score = -1;
    initwindow(800, 600, "Snake");
    srand(time(NULL));

    while(!gameOver){
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, 800, 600); // Screen
        setfillstyle(SOLID_FILL, RED);
        bar(0, 0, 800, 10); // Top bar
        bar(0,0, 10, 600); // Left bar
        bar(0, 600, 800, 600 - 10); // Bottom bar
        bar(790, 10, 800, 600); // Right bar
        // FOOD GENERATOR
        setfillstyle(SOLID_FILL, YELLOW);
        if(x[0] == foodX && y[0] == foodY){
            length += 1;
            score += 1;
            do{
                foodX = (rand() % 780);
                foodY = (1 + rand() % 570);
            }while(getpixel(foodX, foodY)!= 0 && foodX > 20 && foodY > 20);
            foodX = foodX / 10;
            foodX = foodX * 10;
            foodY = foodY / 10;
            foodY = foodY * 10;
            setfillstyle(SOLID_FILL, YELLOW);
        }

        if(foodX < 20)
        {
            foodX += 20;
        }

        if(foodY < 20)
        {
            foodY += 20;
        }

        bar(foodX, foodY, foodX + 10, foodY + 10);

        if(score == 200){
            endGame();
            std::cout << "You Win!" << std::endl;
        }

        switch(score)
        {
            case 10:
                speed = 10;
                break;
        }

        if(GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')){
            d = 1;
        }
        else if(GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')){
            d = 2;
        }
        else if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')){
            d = 3;
        }
        else if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')){
            d = 4;
        }
        else{
            d = 0;
        }
        switch(d){
        case 0:
            if(dir == 1){
                y[0] -= speed;
            }
            if(dir == 2){
                y[0] += speed;
            }
            else if(dir == 3){
                x[0] -= speed;
            }
            else if(dir == 4){
                x[0] += speed;
            }

            break;

        case 1:
            y[0] -= speed;
            dir = 1;
            break;
        case 2:
            y[0] += speed;
            dir = 2;
            break;
        case 3:
            x[0] -= speed;
            dir = 3;
            break;
        case 4:
            x[0] += speed;
            dir = 4;
            break;
        }

        for(int i= 199; i >0;i--){
            x[i] = x[i-1];
            y[i] = y[i -1];
        }

        for(int i = 0; i < length;i++){
            setfillstyle(SOLID_FILL, GREEN);
            bar(x[i], y[i], x[i] + 10, y[i] + 10);
        }

        delay(refRate);
        // Self collision
        for(int i = 2; i < length; i++){
            if(x[0] == x[i] && y[0] == y[i])
            {
                endGame();
                std::cout << "GAME OVER" << std::endl << "Your score is: " << score << std::endl;
            }
        }
        setfillstyle(SOLID_FILL, GREEN);
        bar(x[0], y[0], x[0] + 10, y[0] + 10);

        // Collision against walls
        if(x[0] >= 780/*right*/ || x[0] <= 10 /*left*/|| y[0] <= 10/*top*/ || y[0] >= 580/*bottom*/)
        {
            endGame();
            std::cout << "GAME OVER" << std::endl << "Your score is: " << score << std::endl;
        }
        swapbuffers(); // Prevents buffering
    }
    system("pause");
    return 0;
}
