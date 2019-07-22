#ifndef APPLE_H
#define APPLE_H
#include <Arduino.h>

int CreatApple(int *snakeX, int *snakeY, int snakeLen); // 生成苹果
bool IfAppleEat(int hx,int hy,int apple);   // 判断苹果是否被吃

#endif