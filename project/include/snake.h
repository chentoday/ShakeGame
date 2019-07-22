#ifndef SNAKE_H
#define SNAKE_H
#include <Arduino.h>

class Snake
{
public:
    int snakeLen = 3; // 蛇的长度

    // 蛇身体的位置
    int *snakeLenX = new int[snakeLen];
    int *snakeLenY = new int[snakeLen];

    int hx = 3, hy = 3; // 头部位置
    int tx = 1, ty = 3; // 尾部位置

    bool IsSnakeCollision(int hx, int hy); // 判断蛇是否碰撞
    void updateSnakePosition(bool appleFlag,int tx,int ty);            // 更新蛇的位置
    bool Key_Scan();                       // 扫描按键
    void DirectionAndCount();              // 蛇运动方向判断
    

    // 开局一条蛇的位置
    Snake()
    {
        snakeLenX[0] = 1;
        snakeLenX[1] = 2;
        snakeLenX[2] = 3;
        snakeLenY[0] = 3;
        snakeLenY[1] = 3;
        snakeLenY[2] = 3;
    };

    String keyDirection; // 按键控制的运动方向  分别有："upper" "lower" "right" "left"
    String hdirection;   // 头部朝向 分别有："_A" "_B"
};

#endif