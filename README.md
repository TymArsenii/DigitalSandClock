# Digital Sand Clock
**Stunning** sand sprinkling that reacts on an angle (0-360). Follows real physic's laws of a gravity, friction. <br>
There are 3 modes, which are density of e-sand: normal; more liquid; water (really fast moving like water). They are changed automatically:
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

Click on both buttons - reset sand position (it will appear on top)

Settings:
- Timer's time (1)
- Brightness (2)
- Angle auto (3)
- Beep (4)
- AP/STA mode (5)
  
To enter settings "choose settings" menu - press any button. You'll see letter 's' and a number 1 or 2. 1 - timer's time; 2 - brightness... To enter setting, you chose, press both buttons.

Timer's time (1): minutes, seconds. You can change values with clicks or hold needed button to do it faster. If you do click-hold (fast) it will control directly minutes (without touching the seconds). Press both buttons to return to sand. 

Brightness (2): brightness value (1-16). You can change values with clicks or hold needed button to do it faster. Press both buttons to return to sand.

Angle auto (3): Automaticaly set angle, just to look good (On/Off). When enabled, hourglass will ignore real angle and generate a random one. Used to move an static position, to show it's posibilities and coolness.

Beep (4): Beeping sound, when timer ends (On/Off). When enabled, hourglass will beep, when all sand is in bottom position.

AP/STA mode (5): Work as an access point or connect to Wi-Fi network (On/Off). When enabled, sand clock will open an access point. Connect to it, go to 192.168.6.9 and have the same control panel, as when connecting directly to Wi-Fi.
  
&nbsp; &nbsp; When in 5th setting press and hold any button to generate access point to enter your Wi-Fi credentials.
  
<br> <br>
## Web
Online simulation is available <a href="https://exch.com.ua/e-sand_clock/e-sand_clock.html">here</a> (doesn't have delays to control the density of sand. Operates with max speed. In some cases may blink. In final device all the problems were fixed)

## Possibilities
- Angle reaction
- Realistic sprinkling
- Adaptive sand density
- **Amazing look :-)**
- Set timer
- Change brightness brightness
- Angle auto mode
- Beeping sound when timer ends (optional)
- Saving all the settings to eeprom (power independent memory)
- Change any possible setting from app, local webserver, AP mode
- Set SSID, password (AP mode)
- Standby Clock (NTP server)
- Full online expirience

## Changelog
- v1.0 - Release
- v1.1 - Major improvements, fixes
- v1.2 - Full Wi-Fi capability, fixes
- v1.3 - New app expirience, standby clock, fixes


<br><br>
<p align="right"><strong>Arsenii's Technologies</strong></p>
