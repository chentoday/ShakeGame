#ifndef SHAKE_H
#define SHAKE_H
#include <Arduino.h>

class Shake
{
public:
    int shakeLen = 3; // 蛇的长度

    // 蛇身体的位置
    int *shakeLenX = new int[shakeLen];
    int *shakeLenY = new int[shakeLen];

    int hx = 3, hy = 3; // 头部位置

    bool IsShakeCollision(int hx, int hy); // 判断蛇是否碰撞
    void updateShakePosition();            // 更新蛇的位置
    bool Key_Scan();                       // 扫描按键
    void DirectionAndCount();              // 蛇运动方向判断

    // 开局一条蛇的位置
    Shake()
    {
        shakeLenX[0] = 1;
        shakeLenX[1] = 2;
        shakeLenX[2] = 3;
        shakeLenY[0] = 3;
        shakeLenY[1] = 3;
        shakeLenY[2] = 3;
    };

    String keyDirection; // 按键控制的运动方向  分别有："upper" "lower" "right" "left"
    String hdirection;   // 头部朝向 分别有："_A" "_B"
};

#endif