# Digital Sand Clock
**Stunning** sand sprinkling thant reacts on an angle (0-360). Follows real physic's laws of a gravity, friction. <br>
There are 4 modes, which are density of e-sand: more_thick; normal; more liquid; water (really fast moving like water). They are changed automatically:
```cpp
uint16_t to_seconds=(minute*60)+second; //total timer's seconds 
if(to_seconds<=15) sand_type="water";
else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
else if(to_seconds>120) sand_type="more_thick";
```
<br>
For best accuracy hardware timer is used.

<br><br>
The device itself is 2x 8x8 matrixes (MAX7219 modules) positioned diagonaly. Everything except electronics and screws is 3D printed. 

<br> <br>
Online simulation is available <a href="https://exch.com.ua/e-sand_clock/e-sand_clock.html">here</a> (doesn't have delays to control the density on e-sand. Operates with max speed. In some cases may blink. In final device all the problems were fixed)

## Functionalities
- Angle reaction
- Realistic sprinkling
- **Amazing look :-)**
- Set timer with buttons
- Set brightness with buttons
- (TODO) Beeping sound when timer ends
- (TODO) Set timer from app
- (TODO) Receive notification when timer ends (app)

## Changelog
- v1.0 - Release


<br><br>
<p align="right"><strong>Arsenii's Technologies</strong></p>
