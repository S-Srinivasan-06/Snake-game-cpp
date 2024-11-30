#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int gameSpeed = 120;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    gameSpeed = 120;
}

void Draw()
{
    system("cls");

    // Top border
    for (int i = 0; i < width + 4; i++)
        cout << "=";
    cout << endl;

    // Board with snake and fruit
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "||";  // Left border

            if (i == y && j == x)
                cout << "O";  // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "c";  // Fruit
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "S";  // Snake tail
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "||";  // Right border
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 4; i++)
        cout << "=";
    cout << endl;
    cout << "Score: " << score << " Game Speed: "<< (120-gameSpeed)/10 << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Wrap-around if out of bounds
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Check if the snake hits its tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Check if the snake eats the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nTail++;
        if (score % 30 == 0 && gameSpeed > 20) { // Minimum speed limit of 20 ms
            gameSpeed -= 10; // Increase speed by decreasing delay
        }

        // Generate new fruit position, ensuring it doesn't spawn on the snake
        do {
            fruitX = rand() % width;
            fruitY = rand() % height;
            bool isOnTail = false;
            for (int i = 0; i < nTail; i++)
            {
                if (tailX[i] == fruitX && tailY[i] == fruitY)
                {
                    isOnTail = true;
                    break;
                }
            }
            if (!isOnTail) break;
        } while (true);
    }
}
void RestartPrompt() {
    cout << "\nPress any key to restart. To exit the game, press '0'." << endl;
    char choice = _getch();
    if (choice == '0')
        exit(0);
}

int main()
{
    while (true)
    {
        Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(gameSpeed);
        }
        cout << "Game Over! Final Score: " << score << endl;
         for (int z = 0; z<=5; z++){
            cout <<"Cooldown:::===:::"<<5-z<<":::===:::"<<endl;
            _sleep(1000);
         }
        _sleep(500);
        RestartPrompt();
    }
    return 0;
}