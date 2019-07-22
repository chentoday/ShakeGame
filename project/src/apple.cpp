#include "apple.h"

int CreatApple(int *snakeX, int *snakeY, int snakeLen)
{
    int posx;
    int posy;
    int f=1;
    do
    {
        f=1;
        posx = random(1, 6);
        posy = random(1, 6);
        for (int i = 0; i < snakeLen; i++)
        {
            if (posx == snakeX[i])
            {
                for (i = 0; i < snakeLen; i++)
                {
                    if (posy == snakeY[i])
                    {
                        f=0;
                    }
                }
            }
        }
    } while (!f);
    return (posx-1)+(posy-1)*5;
}

bool IfAppleEat(int hx,int hy,int apple)
{
    int hxy=(hx-1)+(hy-1)*5;
    if (hxy==apple)
    {
        return true;
    }
    return false;
}