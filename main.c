#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep(ms * 1000)
#endif

int i, j, height = 20, width = 20;
int x, y, fruitx, fruity, flag, gameover, score;

void draw()
{
    system("cls");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                {
                    printf("O");
                }
                else if (i == fruitx && j == fruity)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    printf("Press 'x' to quit the game.\n");
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    // Move the snake
    SLEEP(100);
    switch (flag)
    {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    // Check for collision with walls
    if (x <= 0 || x >= height - 1 || y <= 0 || y >= width - 1)
    {
        gameover = 1;
    }

    // Check if snake has eaten the fruit
    if (x == fruitx && y == fruity)
    {
        score += 10;
        // Generate new fruit position
        fruitx = rand() % (height - 2) + 1;
        fruity = rand() % (width - 2) + 1;
    }
}

void setup()
{
    gameover = 0;
    x = height / 2;
    y = width / 2;

    fruitx = rand() % (height - 2) + 1;
    fruity = rand() % (width - 2) + 1;

    score = 0;
    flag = 0;
}

int main()
{
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
    }
    printf("Game over.");
    _getch();
    return 0;
}
