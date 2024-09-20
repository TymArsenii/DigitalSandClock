extern "C" 
{
  #include "user_interface.h"
}

#include <Ticker.h>
Ticker ticker;

String sand_type="more_liquid"; // normal; more_liquid; more_thick; water 🤪 ;;; changes automatically

#include <ESP8266WiFi.h>
#include <GSON.h>
#include <EEPROM.h>
#include "DigiSand-portal.h"
#include <PubSubClient.h>

const char *mqtt_server="test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

#define SSID "i20"
#define PASS "yanatarsnazsof5"

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
MAX7219<2, 1, 2, 4, 0> mtrx; // ROWS COLS CS DT CLK



int8_t matrix_width=16;
int8_t matrix_height=16;

int8_t matrix_arr[16][16] = // 1 - particle; 2 - obstacle; 0 - empty
{
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
  {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 
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
  bool view_log=false;

  

  // timers ->
  os_timer_t drop_timer;

  uint32_t angle_update_timer;
  uint32_t refresh_frame_timer;
  uint32_t move_timer;
  //uint32_t drop_timer=200000;

  uint32_t loop_timer; //debug
  uint32_t prev_millis_timer[16];

  uint32_t angle_auto_timer;

  uint32_t wifi_connection_timer;
  uint32_t wifi_check_timer;
  uint32_t wifi_request_timer;
  uint32_t wifi_freq_timer;
  uint32_t beep_melody_timer;
  uint32_t beep_stop_timer;
  uint32_t mqtt_reconnect_timer;
  // <- timers

int16_t angle=45;
int16_t y_angle=15;
int8_t compensated=0;
bool allow_drop=false;
uint16_t rebuild_delay_time=500;
uint8_t curr_action=1; //1-main (sand); 2-timer set; 3-brightness set; 4-angle auto; 5-beep; 6-ap_mode
int8_t mode_select_tmp=2;
int16_t angle_auto_period;
int16_t auto_angle_values[]={45, 225, 135, 315};
bool wifi_connected;
bool beeping;
uint8_t beep_reset;
bool removed=false; //kostyl
bool led_off=false;
//int16_t active_corrector=0;

struct 
{
  int8_t minute=0;
  int8_t second=10;

  int8_t brightness=5;

  bool angle_auto=false;

  bool beep=false;

  bool ap_mode=false; //true - ap; false - local network
} ee_data;

struct
{
  char ssid[32]="";
  char pass[64]="";
} wifi_credentials;
// <- variables


// functions ->
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

  if(!led_off) mtrx.update();
}

void drop_timer_isr() 
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

  //Serial.println("|");
}

void reset_sand_up()
{
  int8_t matrix_arr_tmp[16][16]= 
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
    {2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  

  memcpy(matrix_arr, matrix_arr_tmp, sizeof(matrix_arr));
}

void reset_sand_down()
{
  int8_t matrix_arr_tmp[16][16]= 
  {
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0}
  };

  memcpy(matrix_arr, matrix_arr_tmp, sizeof(matrix_arr));
}

void set_dot(byte x, byte y, byte state)
{
  if (y>=8) y-=8;
  mtrx.dot(x, y, state);
}

void beep_radar()
{
  if(ee_data.beep && millis()-beep_stop_timer<=5000)
  {
    if(millis()-beep_melody_timer>=30) 
    {
      beep_melody_timer=millis();
      digitalWrite(15, !digitalRead(15));
    }
  }
  else digitalWrite(15, 0);
}
// <- functions 


#define EEPROM_KEY 2
void setup() 
{
  Serial.begin(115200);
  Serial.setTimeout(5);


  EEPROM.begin(200);
  if (EEPROM[0]!=EEPROM_KEY)
  {
    for (int id = 1; id < 80; id++)
    {
      EEPROM.put(id, 0);
    }
    EEPROM[0]=EEPROM_KEY;
    EEPROM.commit();
  }
  EEPROM.get(2, ee_data);

  EEPROM.get(15, wifi_credentials);

  Serial.println();
  Serial.print("SSID: ");
  Serial.println(wifi_credentials.ssid);
  Serial.print("pass: ");
  Serial.println(wifi_credentials.pass);

  //os_timer_disarm(&drop_timer);
  //os_timer_setfn(&drop_timer, (os_timer_func_t *)drop_timer_isr, NULL);
  //os_timer_arm(&drop_timer, 1000, true);

  ticker.attach_ms(1000, drop_timer_isr);

  //buttons settings ->
  up.setHoldTimeout(500);
  down.setHoldTimeout(500);
  up.setStepTimeout(100);
  down.setStepTimeout(100);
  //<- buttons settings

  Wire.begin(13, 5);

  mpu.begin();
  mpu.setX({1, -1});
  mpu.setY({2, 1});
  mpu.setZ({0, 1});

  mtrx.begin();
  mtrx.setBright(ee_data.brightness);
  while(false) //debug-check print_num function; true to enable 
  {
    if(view_log) Serial.println("grgr");

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

  ticker.detach();
  ticker.attach_ms(drop_timer_value, drop_timer_isr);
  // <- timer set

  randomSeed(ESP.getVcc());

  WiFi.mode(WIFI_AP);
  //WiFi.begin(SSID, PASS);

  wifi_connection_timer=9000;

  pinMode(15, OUTPUT);
  
  //client.setInsecure();

  /*http.onResponse
  (
    [](ghttp::Client::Response &resp)
    {
      //Serial.println(resp.body().readString());
      String payload;
      payload="";
      payload=resp.body().readStringUntil('');
      if(view_log || 1==1) Serial.print("Answer: ");
      if(view_log || 1==1) Serial.print(payload);
      if(view_log || 1==1) Serial.println(";");

      gson::Parser p(20);
      if (p.parse(payload))
      {
        ee_data.brightness=p["br"];
        mtrx.setBright(ee_data.brightness-1);      

        if(p["a"]=="0") ee_data.angle_auto=false;
        else if(p["a"]=="1") ee_data.angle_auto=true;

        if(p["b"]=="0") ee_data.beep=false;
        else if(p["b"]=="1") ee_data.beep=true;

        int total_seconds=p["t"];
        ee_data.minute=total_seconds/60;
        ee_data.second=total_seconds%60;

        if(view_log) Serial.print(ee_data.minute);
        if(view_log) Serial.print(':');
        if(view_log) Serial.print(ee_data.second);

        if(total_seconds<=15) sand_type="water";
        else if(total_seconds>15 && total_seconds<=40) sand_type="more_liquid";
        else if(total_seconds>40 && total_seconds<=120) sand_type="normal";
        else if(total_seconds>120) sand_type="more_liquid";

        uint16_t drop_timer_value=total_seconds*1000/61;

        ticker.detach();
        ticker.attach_ms(drop_timer_value, drop_timer_isr);
      }

      if(view_log) Serial.println();
      if(view_log) Serial.println();

      wifi_request_timer=millis();
    }
  );*/

  if(ee_data.ap_mode)
  {
    portal_start();
  }
  if(!ee_data.ap_mode)
  {
    //portal_start();
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_credentials.ssid, wifi_credentials.pass);
  
    int retries=0;
    while (WiFi.status()!=WL_CONNECTED && retries<30) 
    {
      delay(500);
      retries++;
    }
  }

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  Serial.println(WiFi.localIP());
  Serial.println("start");
}

void loop() 
{
  loop_timer=millis();
  //Serial.println(WiFi.localIP());
  //http.tick();
  wifi_stuff();
  //yield();

  if(portal_tick())
  {
    Serial.println(portal_status());
    if(portal_status()==SP_SUBMIT)
    {
      Serial.print("timer:");
      Serial.println(portalCfg.timer);
      Serial.print("angle_auto:");
      Serial.println(portalCfg.angle_auto);
      Serial.print("beep:");
      Serial.println(portalCfg.beep);
      Serial.print("brightness:");
      Serial.println(portalCfg.brightness);
      Serial.println();

      sscanf(portalCfg.timer, "%2hhd:%2hhd", &ee_data.minute, &ee_data.second);
      ee_data.brightness=atoi(portalCfg.brightness);
      if(ee_data.brightness==0) led_off=true;
      else led_off=false;

      ee_data.brightness=map(ee_data.brightness, 0, 16, 1, 16);
      ee_data.angle_auto=atoi(portalCfg.angle_auto);
      ee_data.beep=atoi(portalCfg.beep);


      //apply ->
      if(!led_off) mtrx.setBright(ee_data.brightness-1);

      uint16_t to_seconds=(ee_data.minute*60)+ee_data.second; //total timer's seconds 
      if(to_seconds<=15) sand_type="water";
      else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
      else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
      else if(to_seconds>120) sand_type="more_thick";

      uint16_t drop_timer_value= to_seconds*1000/61;
      ticker.detach();
      ticker.attach_ms(drop_timer_value, drop_timer_isr);
      // <- apply


      portal_reset();
    }
    else if(portal_status()==SP_SUBMIT_LOGIN)
    {
      Serial.print("SSID:");
      Serial.println(portalCfg.ssid);
      Serial.print("pass:");
      Serial.println(portalCfg.pass);
      Serial.println();

      strcpy(wifi_credentials.ssid, portalCfg.ssid);
      strcpy(wifi_credentials.pass, portalCfg.pass);


      Serial.print("wifi settings:  ");
      Serial.print(wifi_credentials.ssid);
      Serial.print(" : ");
      Serial.print(wifi_credentials.pass);
      Serial.println("  saving...  ");
      EEPROM.put(15, wifi_credentials);
      EEPROM.commit();
      Serial.println("saved");

      EEPROM.get(15, wifi_credentials);

      Serial.println();
      Serial.print("after SSID: ");
      Serial.println(wifi_credentials.ssid);
      Serial.print("after pass: ");
      Serial.println(wifi_credentials.pass);

      portal_reset();

      ee_data.ap_mode=false;
      if(!ee_data.ap_mode)
      {
        WiFi.softAPdisconnect();
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);
        WiFi.begin(wifi_credentials.ssid, wifi_credentials.pass);
      
        int retries=0;
        while (WiFi.status()!=WL_CONNECTED && retries<20) 
        {
          delay(500);
          retries++;
        }
      }
      curr_action=1;
    }
  }


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
    else if(inp=='p')
    {
      Serial.print("Local IP: ");
      Serial.println(WiFi.localIP());
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
      if(mode_select_tmp>6) mode_select_tmp=2;
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
    else if(curr_action==4) //auto?
    {
      ee_data.angle_auto=!ee_data.angle_auto;
    }
    else if(curr_action==5) //beep?
    {
      ee_data.beep=!ee_data.beep;
    }
    else if(curr_action==6) //ap_mode?
    {
      ee_data.ap_mode=!ee_data.ap_mode;
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
    else if(curr_action==4) //auto?
    {
      ee_data.angle_auto=!ee_data.angle_auto;
    }
    else if(curr_action==5) //beep?
    {
      ee_data.beep=!ee_data.beep;
    }
    else if(curr_action==6) //ap_mode?
    {
      ee_data.ap_mode=!ee_data.ap_mode;
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
      if(mode_select_tmp<2) mode_select_tmp=6;
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
    else if(curr_action==4) //auto?
    {
      ee_data.angle_auto=!ee_data.angle_auto;
    }
    else if(curr_action==5) //beep?
    {
      ee_data.beep=!ee_data.beep;
    }
    else if(curr_action==6) //ap_mode?
    {
      ee_data.ap_mode=!ee_data.ap_mode;
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
    else if(curr_action==4) //auto?
    {
      ee_data.angle_auto=!ee_data.angle_auto;
    }
    else if(curr_action==5) //beep?
    {
      ee_data.beep=!ee_data.beep;
    }
    else if(curr_action==6) //ap_mode?
    {
      ee_data.ap_mode=!ee_data.ap_mode;
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

  if(up.hold())
  {
    if(curr_action==6)
    {
      wifi_connected=false;
      ee_data.ap_mode=true;
      login_portal_start();

      Serial.println("login portal started");
    } 
  }

  if(down.hold())
  {
    if(curr_action==6)
    {
      wifi_connected=false;
      ee_data.ap_mode=true;
      login_portal_start();

      Serial.println("login portal started");
    } 
  }

  if(both.click())
  {
    if(curr_action>=2)
    {
      /*
      String request_build="apply=123&device_id=1&brightness=";
      request_build+=ee_data.brightness;
      request_build+="&timer=";
      request_build+=ee_data.minute;
      request_build+=":";
      request_build+=ee_data.second;
      request_build+="&angle_auto=";
      request_build+=ee_data.angle_auto ? "1" : "0";
      request_build+="&beep=";
      request_build+=ee_data.beep ? "1" : "0";

      Text headers="Content-Type: application/x-www-form-urlencoded\r\n";
      http.request("/e-sand_clock/digisand_control.php", "POST", headers, request_build);

      Serial.println(request_build);
      */
    }

    if(curr_action==1)
    {
      if(angle>135 && angle<=325) reset_sand_down();
      else reset_sand_up();
    }
    else if(curr_action==0 && curr_action!=2)
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

      //os_timer_disarm(&drop_timer);
      //os_timer_arm(&drop_timer, drop_timer_value, true);
      ticker.detach();
      ticker.attach_ms(drop_timer_value, drop_timer_isr);

      EEPROM.put(2, ee_data);
      EEPROM.commit();

      curr_action=1;
      mode_select_tmp=2;
    }
    else if(curr_action==6)
    {
      WiFiMode_t current_mode=WiFi.getMode();

      if (current_mode==WIFI_STA) 
      {
        if(ee_data.ap_mode)
        {
          wifi_connected=false;
          portal_start();
        }
      } 
      else if (current_mode==WIFI_AP) 
      {
        if(!ee_data.ap_mode)
        {
          WiFi.softAPdisconnect();
          WiFi.disconnect();
          WiFi.mode(WIFI_STA);
          WiFi.begin(wifi_credentials.ssid, wifi_credentials.pass);
        
          int retries=0;
          while (WiFi.status()!=WL_CONNECTED && retries<20) 
          {
            delay(500);
            retries++;
          }
        }
      }
      
      EEPROM.put(2, ee_data);
      EEPROM.commit();
      
      curr_action=1;
      mode_select_tmp=2;
    }
    else
    {
      if(curr_action==3) led_off=false;
      EEPROM.put(2, ee_data);
      EEPROM.commit();
      
      curr_action=1;
      mode_select_tmp=2;
    }
  }
  // <- buttons processing

  if(millis()-angle_update_timer>=20) //angle request
  {
    angle_update_timer=millis();
    angle_pocessing();

    if((angle>=115 && angle<=145) || (angle>=295 && angle<=338)) // KOSTYL!!!
    {
      if(!removed)
      {
        for(uint8_t x=1; x<=matrix_width; x++)
        {
          for(uint8_t y=1; y<=matrix_height; y++)
          {
            if(matrix_arr[x][y]==1) 
            {
              matrix_arr[x][y]=0;
              removed=true;
            }

            if(removed) break;
          }
          if(removed) break;
        }
      }
    }
    else 
    {
      if(removed)
      {
        for(uint8_t x=1; x<=matrix_width; x++)
        {
          for(uint8_t y=1; y<=matrix_height; y++)
          {
            if(matrix_arr[x][y]==0) 
            {
              matrix_arr[x][y]=1;
              removed=false;
            }

            if(!removed) break;
          }
          if(!removed) break;
        }
      }
    }
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

      if(view_log) Serial.print(ee_data.minute);
      if(view_log) Serial.print(':');
      if(view_log) Serial.println(ee_data.second);
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
    else if(curr_action==4) //angle_auto
    {
      print_num(ee_data.angle_auto ? 1 : 0, 1); //number, matrix id
    }
    else if(curr_action==5) //beep
    {
      print_num(ee_data.beep ? 1 : 0, 1); //number, matrix id
    }
    else if(curr_action==6) //ap_mode
    {
      print_num(ee_data.ap_mode ? 1 : 0, 1); //number, matrix id
    }
    //Serial.println(curr_action);

    if(curr_action!=1) mtrx.update();
    else 
    {
      if(led_off) 
      {
        for(int x=1; x<=16; x++)
        {
          for(int y=1; y<=16; y++)
          {
            set_dot(x-1, y-1, 0);
          }
        }
        mtrx.update();
      }
    }
  }
  //Serial.println(millis()-loop_timer);
}