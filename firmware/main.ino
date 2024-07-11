extern "C" 
{
  #include "user_interface.h"
}

String sand_type="more_liquid"; // normal; more_liquid; more_thick; water 🤪 

/* loop_timer:
water=13ms;
normal=140ms;
more_thick=290ms;
more_liquid=97ms;
*/

#include <EEPROM.h>

// buttons ->
#define EB_NO_FOR
#define EB_NO_CALLBACK
#define EB_NO_COUNTER
#define EB_NO_BUFFER

#include <EncButton.h>
Button up(14);
Button down(12);
VirtButton both;

IRAM_ATTR void up_isr() 
{
  up.pressISR();
}
IRAM_ATTR void down_isr() 
{
  down.pressISR();
}
// <- buttons

#include "mini6050.h"
Mini6050 mpu;


// matrix ->
#include <GyverMAX7219.h>
MAX7219<2, 1, 2, 4, 0> mtrx; // . . CS DT CLK



int8_t matrix_width=16;
int8_t matrix_height=16;

int8_t matrix_arr[16][16] = // 1 - particle; 2 - obstacle; 0 - empty
{
  {0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}, 
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

static const uint8_t letters[][5] PROGMEM = 
{
  { //s
    0b00000,
    0b10111,
    0b10101,
    0b10101,
    0b11101,
  },
  { //m rotated
    0b00000,
    0b10111,
    0b10101,
    0b10101,
    0b11101,
  },
};
// <- matrix



// variables ->

  // timers ->
  os_timer_t drop_timer;

  uint32_t angle_update_timer;
  uint32_t refresh_frame_timer;
  uint32_t move_timer;
  //uint32_t drop_timer=200000;

  uint32_t loop_timer; //debug
  uint32_t prev_millis_timer[16];
  // <- timers

int16_t angle=45;
int16_t y_angle=15;
int8_t compensated=0;
bool allow_drop=false;
uint16_t rebuild_delay_time=500;
uint8_t curr_action=1; //1-main (sand); 2-timer set; 3-brightness set;
int8_t mode_select_tmp=2;
//int16_t active_corrector=0;

struct 
{
  int8_t minute=0;
  int8_t second=10;

  int8_t brightness;
} ee_data;
// <- variables


// functions ->
void ICACHE_RAM_ATTR drop_timer_isr() 
{
  allow_drop=true;

  if(angle>=180 && angle<=360)
  {
    if(matrix_arr[8-1][8-1]==2) matrix_arr[8-1][8-1]=0;
    if(matrix_arr[9-1][9-1]==2) matrix_arr[9-1][9-1]=0;
  }
  if(angle>=0 && angle<180)
  {
    if(matrix_arr[8-1][8-1]==2) matrix_arr[8-1][8-1]=0;
    if(matrix_arr[9-1][9-1]==2) matrix_arr[9-1][9-1]=0;
  }
}

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
  }

  mtrx.update();
}
// <- functions 


#define EEPROM_KEY 3
void setup() 
{
  EEPROM.begin(10);
  if (EEPROM[0]!=EEPROM_KEY)
  {
    for (int id = 1; id < 8; id++)
    {
      EEPROM.put(id, 0);
    }
    EEPROM[0] = EEPROM_KEY;
    EEPROM.commit();
  }
  EEPROM.get(2, ee_data);

  os_timer_disarm(&drop_timer);
  os_timer_setfn(&drop_timer, (os_timer_func_t *)drop_timer_isr, NULL);
  os_timer_arm(&drop_timer, 1000, true);

  //buttons settings ->
  up.setHoldTimeout(500);
  down.setHoldTimeout(500);
  up.setStepTimeout(100);
  down.setStepTimeout(100);
  //<- buttons settings


  Serial.begin(115200);
  Serial.setTimeout(5);

  Wire.begin(13, 5);

  mpu.begin();
  mpu.setX({1, -1});
  mpu.setY({2, 1});
  mpu.setZ({0, 1});

  mtrx.begin();
  mtrx.setBright(ee_data.brightness);
  while(false) //debug-check print_num function; true to enable 
  {
    Serial.println("grgr");

    mtrx.clear();
    print_num(8, 1); //number, matrix id
    mtrx.update();
    delay(1000);

    mtrx.clear();
    print_num(30, 1);
    mtrx.update();
    delay(1000);

    mtrx.clear();
    print_num(80, 2);
    mtrx.update();
    delay(1000);

    mtrx.clear();
    print_num(0, 2);
    mtrx.update();
    delay(1000);
  }
  attachInterrupt(14, up_isr, FALLING);
  attachInterrupt(12, down_isr, FALLING);

  // timer set ->
  uint16_t to_seconds=(ee_data.minute*60)+ee_data.second; //total timer's seconds 
  if(to_seconds<=15) sand_type="water";
  else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
  else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
  else if(to_seconds>120) sand_type="more_thick";


  uint16_t drop_timer_value= to_seconds*1000/61;

  os_timer_disarm(&drop_timer);
  os_timer_arm(&drop_timer, drop_timer_value, true);
  // <- timer set
}

void loop() 
{
  loop_timer=millis();
  if(((ee_data.minute*60)+ee_data.second)<=0) ee_data.second=1;
  if(Serial.available() && 1==2) //debug-print matrix, set angle manually; to use, set 1==1 in condition; to set angle manually in angle_processing set 1==2 in condition
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

  // buttons processing ->
  up.tick();
  down.tick();
  both.tick(up, down);

  if(up.click())
  {
    if(curr_action==0) //choose setting
    {
      mode_select_tmp++;
      if(mode_select_tmp>3) mode_select_tmp=2;
    }
    else if(curr_action==2) //set timer
    {
      if(ee_data.second>=59 && ee_data.minute>=99) {;}
      else ee_data.second++;

      if(ee_data.second>59) 
      {
        ee_data.minute++;
        ee_data.second=0;
      }
    }
    else if(curr_action==3) //change brightness 
    {
      ee_data.brightness++;
      if(ee_data.brightness>15) ee_data.brightness=0;
    }
    else if(curr_action==1) curr_action=0;
  }
  if(up.step(0))
  {
    if(curr_action==2) //set timer
    {
      if(ee_data.second>=49 && ee_data.minute>=99) 
      {
        if(ee_data.second>=59 && ee_data.minute>=99) {;}
        else ee_data.second++;
      }
      else ee_data.second+=10;
      if(ee_data.second>59) 
      {
        ee_data.minute++;
        ee_data.second-=59;
      }
    }
    else if(curr_action==3) //change brightness
    {
      ee_data.brightness+=1;
      if(ee_data.brightness<0) ee_data.brightness=15;
    }
  }
  if(up.step(1))
  {
    if(curr_action==2) //set timer
    {
      ee_data.minute+=1;
      if(ee_data.minute>99) ee_data.minute=99;
    }
  }



  if(down.click())
  {
    if(curr_action==0) //choose setting
    {
      mode_select_tmp--;
      if(mode_select_tmp<2) mode_select_tmp=3;
    }
    else if(curr_action==2) //set timer
    {
      if(ee_data.second<=0 && ee_data.minute<=0) {;}
      else ee_data.second--;
      if(ee_data.second<0) 
      {
        ee_data.minute--;
        ee_data.second=59;
      }
    }
    else if(curr_action==3) //change brightness
    {
      ee_data.brightness--;
      if(ee_data.brightness<0) ee_data.brightness=15;
    }
    else if(curr_action==1) curr_action=0;
  }
  if(down.step(0))
  {
    if(curr_action==2) //set timer
    {
      if(ee_data.second<=10 && ee_data.minute<=0) 
      {
        if(ee_data.second<=0 && ee_data.minute<=0) {;}
        else ee_data.second--;
      }
      else ee_data.second-=10;
      if(ee_data.second<0) 
      {
        ee_data.minute--;
        ee_data.second=59;
      }
    }
    else if(curr_action==3) //change brightness
    {
      ee_data.brightness-=1;
      if(ee_data.brightness<0) ee_data.brightness=15;
    }
  }
  if(down.step(1))
  {
    if(curr_action==2) //set timer
    {
      ee_data.minute-=1;
      if(ee_data.minute<0) ee_data.minute=0;
    }
  }



  if(both.click())
  {
    if(curr_action==0 && curr_action!=2)
    {
      curr_action=mode_select_tmp;
      mode_select_tmp=2;
    }
    else if(curr_action==2)
    {
      uint16_t to_seconds=(ee_data.minute*60)+ee_data.second; //total timer's seconds 
      if(to_seconds<=15) sand_type="water";
      else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
      else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
      else if(to_seconds>120) sand_type="more_thick";


      uint16_t drop_timer_value= to_seconds*1000/61;

      os_timer_disarm(&drop_timer);
      os_timer_arm(&drop_timer, drop_timer_value, true);

      curr_action=1;
      mode_select_tmp=2;
    }
    else
    {
      EEPROM.put(2, ee_data);
      EEPROM.commit();

      curr_action=1;
      mode_select_tmp=2;
    }
  }
  // <- buttons processing

  if(millis()-angle_update_timer) //angle request
  {
    angle_update_timer=millis();
    angle_pocessing();
  }
  if(millis()-refresh_frame_timer>=60/1000) //60Hz
  {
    refresh_frame_timer=millis();
    mtrx.clear();

    if(curr_action==1) //sand
    {
      redraw();
      move_particles();
    }
    else if(curr_action==0) //choose setting
    { 
      if(angle>=0 && angle<=180)
      {
        for (uint8_t x=1; x<=5; x++) 
        {
          uint8_t col=pgm_read_byte(&letters[1-1][x-1]);
          for (uint8_t y=1; y<=5; y++) 
          {
            if(bitRead(col, 5-y))
            {
              set_dot(y, x, 1);
            }
          }
        }
      }
      else
      {
        for (uint8_t x=1; x<=5; x++) 
        {
          uint8_t col=pgm_read_byte(&letters[2-1][x-1]);
          for (uint8_t y=1; y<=5; y++) 
          {
            if(bitRead(col, 5-y))
            {
              set_dot(y, x, 1);
            }
          }
        }
      }

      print_num(mode_select_tmp-1, 2);
    }
    else if(curr_action==2) //set timer
    {
      print_num(ee_data.minute, 1); //number, matrix id
      print_num(ee_data.second, 2);

      Serial.print(ee_data.minute);
      Serial.print(':');
      Serial.println(ee_data.second);
    }
    else if(curr_action==3) //set brightness
    {
      print_num(ee_data.brightness+1, 1); //number, matrix id

      mtrx.setBright(ee_data.brightness);
      for(uint8_t x=9; x<=16; x++)
      {
        for(uint8_t y=9; y<=16; y++)
        {
          set_dot(x-1, y-1, 1);
        }
      }
    }

    if(curr_action!=1) mtrx.update();
  }
  //Serial.println(millis()-loop_timer);
}
