#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void desen(){
  display.clearDisplay();
  display.drawFastHLine(0, 39, 128, SSD1306_WHITE);
  display.drawFastVLine(13, 16, 63, SSD1306_WHITE);
  for(int i=19; i<=59; i=i+8)
  {
    display.drawFastHLine(11, i, 2, SSD1306_WHITE);
    display.drawFastHLine(9, i+4, 4, SSD1306_WHITE);

  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 4);
  display.println("U=");
  display.setCursor(53, 4);
      display.println("F=");
  display.display();
}


void setup() {
   Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(3, 25);
  display.println("OSCILOSCOP");
  display.display();
  delay(3000);
  desen();
}

float cx = 0.1 ,cy = 195, val =1700, U=0, timp1, timp2, timptot, nrT, F;
int x=13, xt1 = 13, yt1, maxim = 39, i=0, prag = 39, k=0, y2 = 39;

void loop() {
  if(i == 0)
  {
    timp1 = millis();
    i++;
  }
  yt1= 39 - val/cy+9;
  val = analogRead(4);
  if( (y2<prag && yt1>=prag) || (y2>prag && yt1<=prag) )
  {
    k++;
  }
  y2 = yt1;
  if(yt1 < maxim)
  {
    maxim = yt1;
    U = (39 - yt1 +1) * 0.125 ;
  }
display.drawPixel(x, 39-val/cy +9 , WHITE);
 display.drawLine(xt1, yt1, x, 39 - val/cy +9, SSD1306_WHITE  );
 display.display();
  xt1=x;
  x++;
  if(x == 128)
  {
    timp2 = millis();
    timptot = (timp2 - timp1)/1000;
    nrT = k/2;
    F = nrT/timptot;
    x=13;
    xt1=13;
    desen();
    display.setTextSize(1);
    display.setTextColor(WHITE);
      display.setCursor(12, 4);
      display.println(U);
      display.setCursor(37, 4);
      display.println('V');
      display.setCursor(65, 4);
      display.println(F);
      display.setCursor(90, 4);
      display.println("Hz");
      display.display();
    maxim = 39;
    i=0;
    k=0;
  }
  delayMicroseconds(cx);
}
