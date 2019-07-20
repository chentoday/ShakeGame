#include "shake.h"
#include "apple.h"
#include <NeoPixelBus.h>
#include <Ticker.h>

// 如果 bpibit 板子版本为 v1.2 ，则需要设置（如果是 v1.4，则需删除）
#define ledPower 2
const uint16_t PixelCount = 25; // 面板的像素（即面板的LED为 5*5）
const uint8_t PixelPin = 4;     // 控制 LED 面板的 Pin 脚
Ticker tickerWalk;
#define colorSaturation 20 // 颜色饱和度

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor purple(colorSaturation, 0, colorSaturation);
RgbColor black(0);

Shake shake;

// 将(x,y)变为编号
int Count(int x, int y)
{
  return (x - 1) + (y - 1) * 5;
}

// 自动前进
void AutoWalk()
{
  if (shake.hdirection == "upper")
  {
    shake.hy -= 1;
  }
  else if (shake.hdirection == "lower")
  {
    shake.hy += 1;
  }
  else if (shake.hdirection == "left")
  {
    shake.hx -= 1;
  }
  else if (shake.hdirection == "right")
  {
    shake.hx += 1;
  }
  strip.SetPixelColor(Count(shake.shakeLenX[0], shake.shakeLenY[0]), black);
  shake.updateShakePosition();
  Serial.printf("x=%d\n", shake.hx);
  Serial.printf("y=%d\n", shake.hy);
  Serial.printf("===\n");
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

  // 开局显示一条蛇
  for (int i = 0; i < 3; i++)
  {
    strip.SetPixelColor(Count(shake.shakeLenX[i], shake.shakeLenY[i]), green);
  }

  // 开局蛇的头部和方向

  shake.hdirection = "right";
  shake.keyDirection = "_S";

  strip.SetPixelColor(Count(shake.hx, shake.hy), purple);
  strip.Show();

  tickerWalk.attach_ms(1500, AutoWalk);
}

void loop()
{
  if (shake.IsShakeCollision(shake.hx, shake.hy))
  {
    delete[] shake.shakeLenX;
    delete[] shake.shakeLenY;
    tickerWalk.detach();
    strip.ClearTo(red);
    strip.Show();
    while(1);
    // 失败界面，待补充
  }
  else
  {
    // 显示蛇
    for (int i = 0; i < shake.shakeLen; i++)
    {
      strip.SetPixelColor(Count(shake.shakeLenX[i], shake.shakeLenY[i]), green);
    }
    strip.SetPixelColor(Count(shake.shakeLenX[shake.shakeLen - 1], shake.shakeLenY[shake.shakeLen - 1]), purple);
  }
  strip.Show();

  // 判断是否有按键事件发生
  if (shake.Key_Scan())
  {
    shake.DirectionAndCount();
    strip.SetPixelColor(Count(shake.shakeLenX[0], shake.shakeLenY[0]), black);
    shake.updateShakePosition();
  }
}
