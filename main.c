#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#define TERMINAL_CLEAR "cls"
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define SLEEP(ms) usleep(ms * 1000)
#define TERMINAL_CLEAR "clear"
#endif

int i, j, height = 20, width = 20;
int x, y, fruitx, fruity, flag, gameover, score, delay = 100;

#ifdef __unix__
// Linux (POSIX) equivalent functions
int _kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char _getch(void)
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

void draw()
{
    system(TERMINAL_CLEAR);
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
        case 'A':
            flag = 1;
            break;
        case 's':
        case 'S':
            flag = 2;
            break;
        case 'd':
        case 'D':
            flag = 3;
            break;
        case 'w':
        case 'W':
            flag = 4;
            break;
        case 'x':
        case 'X':
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
    SLEEP(delay);
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

        if (score % 50 == 0)
        {
            // Increase the speed of the snake
            if (delay >= 70)
            {
                delay--;
            }

            // Decrease the size of area
            if (score >= 1500 && height >= 10 && width >= 10)
            {
                height--;
                width--;
            }
        }

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
