I made with an esp32 board and an oled display an oscilloscope that works on small frequencies(0-10 Hz) and low voltages(0-3V).
In the arduino IDE program we need to download the Adafruit_GFX and Adafruit_SSD1306 libraries.

Because the esp32 can't read negative voltages and the maximum voltage we cand read directly is 3,3V we have to insert an offset of 1,5V.

For the connection between the esp32 and the oled display:
GND - GND
VCC - 3V3
SCL - 22
SDA - 21

The cx and cy variables in the code can be different depending on the waveform generator used.
