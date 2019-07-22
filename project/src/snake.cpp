#include "snake.h"

bool Snake::IsSnakeCollision(int hx, int hy)
{
    // 墙壁碰撞
    if (hx > 5 || hx < 1 || hy > 5 || hy < 1)
        return true;

    // 自身碰撞
    for (int t = 0; t < snakeLen-1; t++)
    {
        if (hx == snakeLenX[t])
            for (int i = 0; i < snakeLen-1; i++)
            {
                if (hy == snakeLenY[t])
                    return true;
            }
    }
    return false;
}

// 更新蛇的长度
void Snake::updateSnakePosition(bool appleFlag,int tx,int ty)
{
    if (!appleFlag)
    {
        for (int t = 0; t < snakeLen - 1; t++)
        {
            snakeLenX[t] = snakeLenX[t + 1];
            snakeLenY[t] = snakeLenY[t + 1];
        }
        snakeLenX[snakeLen - 1] = hx;
        snakeLenY[snakeLen - 1] = hy;
    }
    else
    {
        for (int t = (snakeLen - 2); t >0; t--)
        {
            snakeLenX[t] = snakeLenX[t - 1];
            snakeLenY[t] = snakeLenY[t - 1];
        }
        snakeLenX[snakeLen - 1] = hx;
        snakeLenY[snakeLen - 1] = hy;
        snakeLenX[0]=tx;
        snakeLenY[0]=ty;
    }
}

void Snake::DirectionAndCount()
{
    if (hdirection == "right")
    {
        if (keyDirection == "_A")
        {
            hy += 1;
            hdirection = "lower";
        }
        else if (keyDirection == "_B")
        {
            hy -= 1;
            hdirection = "upper";
        }
    }
    else if (hdirection == "left")
    {
        if (keyDirection == "_A")
        {
            hy -= 1;
            hdirection = "upper";
        }
        else if (keyDirection == "_B")
        {
            hy += 1;
            hdirection = "lower";
        }
    }
    else if (hdirection == "upper")
    {
        if (keyDirection == "_A")
        {
            hx += 1;
            hdirection = "right";
        }
        else if (keyDirection == "_B")
        {
            hx -= 1;
            hdirection = "left";
        }
    }
    else if (hdirection == "lower")
    {
        if (keyDirection == "_A")
        {
            hx -= 1;
            hdirection = "left";
        }
        else if (keyDirection == "_B")
        {
            hx += 1;
            hdirection = "right";
        }
    }
}
bool Snake::Key_Scan()
{
    static u_char key_up = 1;
    keyDirection = "_S";
    if (key_up && (digitalRead(BUTTON_A) == LOW || digitalRead(BUTTON_B) == LOW))
    {
        delayMicroseconds(10);
        key_up = 0;
        if (digitalRead(BUTTON_A) == LOW)
        {
            keyDirection = "_A";
        }
        else if (digitalRead(BUTTON_B) == LOW)
        {
            keyDirection = "_B";
        }
        return true;
    }
    else if (digitalRead(BUTTON_A) == HIGH && digitalRead(BUTTON_B) == HIGH)
    {
        key_up = 1;
        return false;
    }
    else
    {
        return false;
    }
}
