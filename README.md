# Digital Sand Clock
**Stunning** sand sprinkling thant reacts on an angle (0-360). Follows real physic's laws of a gravity, friction. <br>
There are 4 modes, which are density of e-sand: normal; more liquid; water (really fast moving like water). They are changed automatically:
```cpp
uint16_t to_seconds=(minute*60)+second; //total timer's seconds 
if(to_seconds<=15) sand_type="water";
else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
else if(to_seconds>40) sand_type="normal";
```
<br>
For best accuracy hardware timer is used.

<br><br>
The device itself is 2x 8x8 matrixes (MAX7219 modules) positioned diagonaly. Everything except electronics and screws is 3D printed. 
<br><br>
## How to use 
Slide the power switch to turn it on, you'll see the timer started with your last period (the default is 10sec). 

Click on both buttons - reset sand position (it will appear in the top position)

Settings:
- Timer's time (1)
- Brightness (2)
- Angle auto (3)

To enter settings "choose settings" menu - press any button. You'll see letter 's' and a number 1 or 2. 1 - timer's time; 2 - brightness. To enter setting, you chose, press both buttons.

Timer's time (1): minutes, seconds. You can change values with clicks or hold needed button to do it faster. If you do click-hold (fast) it will control directly minutes (without touching the seconds). Press both buttons to return to sand. 

Brightness (2): brightness value (1-16). You can change values with clicks or hold needed button to do it faster. Press both buttons to return to sand.

Angle auto (3): Automaticaly set angle, just to look good (On/Off). When enabled, hourglass will ignore real angle and generate a random one. Used to move an static position, to show it's posibilities and coolness.
<br> <br>
## Web
Online simulation is available <a href="https://exch.com.ua/e-sand_clock/e-sand_clock.html">here</a> (doesn't have delays to control the density on e-sand. Operates with max speed. In some cases may blink. In final device all the problems were fixed)

## Functionalities
- Angle reaction
- Realistic sprinkling
- **Amazing look :-)**
- Set timer with buttons
- Set brightness with buttons
- Saving data to eeprom (all the settings)
- (TODO) Beeping sound when timer ends
- (TODO) Set timer from app (PWA)
- (TODO) Make any changes from app
- (TODO) Receive notification when timer ends (app)

## Changelog
- v1.0 - Release


<br><br>
<p align="right"><strong>Arsenii's Technologies</strong></p>
