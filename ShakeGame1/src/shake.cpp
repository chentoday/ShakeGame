#include "shake.h"

bool Shake::IsShakeCollision(int hx, int hy)
{
    if (hx > 5 || hx < 1 || hy > 5 || hy < 1)
        return true;
    // for (int t = 0; t < shakeLen; t++)
    // {
    //     if (hx == shakeLenX[t])
    //         for (int i = 0; i < shakeLen; i++)
    //         {
    //             if (hy == shakeLenY[t])
    //                 return true;
    //         }
    // }
    return false;
}

// 更新蛇的长度
void Shake::updateShakePosition()
{
    for (int t = 0; t < shakeLen - 1; t++)
    {
        shakeLenX[t] = shakeLenX[t + 1];
        shakeLenY[t] = shakeLenY[t + 1];
    }
    shakeLenX[shakeLen - 1] = hx;
    shakeLenY[shakeLen - 1] = hy;
}

void Shake::DirectionAndCount()
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
bool Shake::Key_Scan()
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
    }else
    {
       return false;
    }
    
}
