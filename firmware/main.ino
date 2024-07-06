#define SAND_TYPE "more_liquid" // normal; more_liquid; more_thick; water 🤪

#include "mini6050.h"
Mini6050 mpu;


// matrix ->
#include <GyverMAX7219.h>
MAX7219<2, 1, 14, 4, 0> mtrx; // . . CS DT CLK



int8_t matrix_width=16;
int8_t matrix_height=16;

int8_t matrix_arr[16][16] = // 1 - particle; 2 - obstacle; 0 - empty
{
  {0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}, 
};

bool forse_lightup[5]={0,0,0,0,0};
// <- matrix



// timers ->
uint32_t angle_update_timer;
uint32_t refresh_frame_timer;
uint32_t move_timer;
uint32_t drop_timer;
// <- timers

// other variables ->
int16_t angle;
int16_t y_angle;
int8_t compensated=0;
bool allow_drop;
uint16_t rebuild_delay_time=500; //1-45deg; 2-225deg
// <- other variables


// functions ->
void set_dot(byte x, byte y, byte state)
{
  if (y>=8) y-=8;
  mtrx.dot(x, y, state);
}

void redraw(int8_t area=10)
{
  if(area==10)
  {
    for(uint8_t x=1; x<=16; x++)
    {
      for(uint8_t y=1; y<=16; y++)
      {
        if(matrix_arr[x-1][y-1]==2) continue;
        else
        {
          set_dot(x-1, y-1, matrix_arr[x-1][y-1]);
        }
      }
    }

    if(angle>=0 && angle<=90)
    {
      if(forse_lightup[1]) set_dot(8-1, 2-1, 1);
      if(forse_lightup[2]) set_dot(8-1, 4-1, 1);
      if(forse_lightup[3]) set_dot(8-1, 6-1, 1);
      if(forse_lightup[4]) set_dot(8-1, 8-1, 1);
    }
    else if(angle>180 && angle<=270)
    {
      if(forse_lightup[1]) set_dot(9-1, 9-1, 1);
      if(forse_lightup[2]) set_dot(9-1, 11-1, 1);
      if(forse_lightup[3]) set_dot(9-1, 13-1, 1);
      if(forse_lightup[4]) set_dot(9-1, 15-1, 1);
    }

    if(SAND_TYPE=="water") rebuild_delay_time=10;
    else if(SAND_TYPE=="normal") rebuild_delay_time=500;
    else if(SAND_TYPE=="more_liquid") rebuild_delay_time=350;
    else if(SAND_TYPE=="more_thick") rebuild_delay_time=1100;
  }
  else if(area==2) //225deg
  {
    for(uint8_t x=1; x<=8; x++)
    {
      for(uint8_t y=1; y<=16; y++)
      {
        if(matrix_arr[x-1][y-1]==2) continue;
        else
        {
          set_dot(x-1, y-1, matrix_arr[x-1][y-1]);
        }
      }
    }

    if(forse_lightup[1]) set_dot(9-1, 9-1, 1);
    if(forse_lightup[2]) set_dot(9-1, 11-1, 1);
    if(forse_lightup[3]) set_dot(9-1, 13-1, 1);
    if(forse_lightup[4]) set_dot(9-1, 15-1, 1);

    if(SAND_TYPE=="water") rebuild_delay_time=10;
    else if(SAND_TYPE=="normal") rebuild_delay_time=500;
    else if(SAND_TYPE=="more_liquid") rebuild_delay_time=350;
    else if(SAND_TYPE=="more_thick") rebuild_delay_time=1100;
  }
  else if(area==1) //45deg
  {
    for(uint8_t x=9; x<=16; x++)
    {
      for(uint8_t y=1; y<=16; y++)
      {
        if(matrix_arr[x-1][y-1]==2) continue;
        else
        {
          set_dot(x-1, y-1, matrix_arr[x-1][y-1]);
        }
      }
    }

    if(forse_lightup[1]) set_dot(8-1, 2-1, 1);
    if(forse_lightup[2]) set_dot(8-1, 4-1, 1);
    if(forse_lightup[3]) set_dot(8-1, 6-1, 1);
    if(forse_lightup[4]) set_dot(8-1, 8-1, 1);

    if(SAND_TYPE=="water") rebuild_delay_time=10;
    else if(SAND_TYPE=="normal") rebuild_delay_time=500;
    else if(SAND_TYPE=="more_liquid") rebuild_delay_time=350;
    else if(SAND_TYPE=="more_thick") rebuild_delay_time=1100;
  }
  mtrx.update();
}
// <- functions 

void setup() 
{
  Serial.begin(115200);
  Serial.setTimeout(5);

  Wire.begin(13, 5);

  mpu.begin();
  mpu.setX({1, -1});
  mpu.setY({2, 1});
  mpu.setZ({0, 1});

  mtrx.begin();
  mtrx.setBright(1);
  set_dot(9-1, 9-1, 1);
  set_dot(9-1, 11-1, 1);
  set_dot(9-1, 13-1, 1);
  set_dot(9-1, 15-1, 1);
mtrx.update();
delay(5000);
}

void loop() 
{
  if(Serial.available()) //debug
  {
    char inp=Serial.read();
    if(inp=='g')
    {
      for(uint8_t x=1; x<=16; x++)
      {
        for(uint8_t y=1; y<=16; y++)
        {
          Serial.print(matrix_arr[x-1][y-1]);
          Serial.print(' ');
        }
        Serial.println();
      }
      Serial.println();
      Serial.println();
      Serial.println();
    }
    else
    {
      int angle_get=Serial.parseInt();
      angle=angle_get;
    }

  }
  if(millis()-angle_update_timer) //angle request
  {
    angle_update_timer=millis();
    angle_pocessing();
  }

  if(millis()-refresh_frame_timer>=60/1000) //60Hz
  {
    refresh_frame_timer=millis();
    redraw();
    move_particles();
  }
}
