#include "snake.h"
#include "apple.h"
#include <NeoPixelBus.h>
// #include <Ticker.h>
#include "time.h"

// 如果 bpibit 板子版本为 v1.2 ，则需要设置（如果是 v1.4，则需删除）
#define ledPower 2
const uint16_t PixelCount = 25; // 面板的像素（即面板的LED为 5*5）
const uint8_t PixelPin = 4;     // 控制 LED 面板的 Pin 脚
#define colorSaturation 20      // 颜色饱和度

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor purple(colorSaturation, 0, colorSaturation);
RgbColor black(0);

Snake snake;

int apple = 0;
bool appleFlag = false;
int it = 1;

long beforeTime; //  记录之前的时间

// 将(x,y)变为编号
int Count(int x, int y)
{
  return (x - 1) + (y - 1) * 5;
}

// 自动前进
void AutoWalk()
{
  if (snake.hdirection == "upper")
  {
    snake.hy -= 1;
  }
  else if (snake.hdirection == "lower")
  {
    snake.hy += 1;
  }
  else if (snake.hdirection == "left")
  {
    snake.hx -= 1;
  }
  else if (snake.hdirection == "right")
  {
    snake.hx += 1;
  }
}

void DisplaySnake()
{
  for (int i = 0; i < snake.snakeLen; i++)
  {
    strip.SetPixelColor(Count(snake.snakeLenX[i], snake.snakeLenY[i]), green);
  }
  // strip.SetPixelColor(Count(snake.snakeLenX[snake.snakeLen - 2], snake.snakeLenY[snake.snakeLen - 2]), green);
  strip.SetPixelColor(Count(snake.snakeLenX[snake.snakeLen - 1], snake.snakeLenY[snake.snakeLen - 1]), purple);
  strip.Show();
}

void setup()
{
  Serial.begin(9600);
  Serial.printf("OK!");
  Serial.println();

  // 重置所有 Neopixels 对象为关闭状态
  strip.Begin();
  strip.Show();

  //初始化 BUTTON_A / BUTTON_B
  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);

  // 如果 bpibit 板子版本为 v1.2 ，则需要设置（如果是 v1.4，则需删除）
  pinMode(ledPower, OUTPUT);
  digitalWrite(ledPower, HIGH);

  // 开局显示一条蛇和苹果

  snake.hdirection = "right";
  snake.keyDirection = "_S";

  for (int i = 0; i < 3; i++)
  {
    strip.SetPixelColor(Count(snake.snakeLenX[i], snake.snakeLenY[i]), green);
  }
  strip.SetPixelColor(Count(snake.hx, snake.hy), purple);

  apple = (CreatApple(snake.snakeLenX, snake.snakeLenY, snake.snakeLen));
  strip.SetPixelColor(apple, red);

  strip.Show();

  beforeTime = clock();
}

void loop()
{
  // // 碰撞判断
  if (snake.IsSnakeCollision(snake.hx, snake.hy))
  {
    strip.ClearTo(red);
    strip.Show();
    while (1)
      ;
  }
  // 当蛇的长度为 8 时成功
  else if(snake.snakeLen==8)
  {
    strip.ClearTo(green);
    strip.Show();
    while (1)
      ;
  }
  else
  {
    DisplaySnake();
    if (snake.Key_Scan())
    {
      snake.DirectionAndCount();

      strip.SetPixelColor(Count(snake.snakeLenX[0], snake.snakeLenY[0]), black);
      snake.tx = snake.snakeLenX[0];
      snake.ty = snake.snakeLenY[0];
      snake.updateSnakePosition(false, snake.tx, snake.ty);
      beforeTime = clock();
    }
    // 当时间间隔大于 2300 ms时，前进一格
    if ((clock() - beforeTime) >= 2300)
    {
      AutoWalk();

      strip.SetPixelColor(Count(snake.snakeLenX[0], snake.snakeLenY[0]), black);
      snake.tx = snake.snakeLenX[0];
      snake.ty = snake.snakeLenY[0];

      snake.updateSnakePosition(false, snake.tx, snake.ty);

      beforeTime = clock();
    }

    // 显示苹果
    if (IfAppleEat(snake.hx, snake.hy, apple))
    {
      snake.snakeLen++;

      strip.SetPixelColor(apple, black);
      snake.updateSnakePosition(true, snake.tx, snake.ty);
      apple = (CreatApple(snake.snakeLenX, snake.snakeLenY, snake.snakeLen));
      strip.SetPixelColor(apple, red);
      beforeTime = clock();
    }
  }
}
