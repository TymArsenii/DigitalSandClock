#define SP_AP_NAME "DigiSand control" // AP name
#define SP_AP_IP 192,168,6,9 // IP AP

#ifndef _SimplePortal_h
#define _SimplePortal_h
#include <DNSServer.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#define SP_ERROR 0
#define SP_SUBMIT 1
#define SP_SWITCH_AP 2
#define SP_SWITCH_LOCAL 3
#define SP_EXIT 4
#define SP_TIMEOUT 5

struct PortalCfg 
{
  char timer[7]="";
  char brightness[4]="";
  char angle_auto[5]="";
  char beep[5]="";
  uint8_t mode=WIFI_AP; //(1 - WIFI_STA, 2 - WIFI_AP)
};
extern PortalCfg portalCfg;

void portal_start(); //launch portal
void portal_reset(); //reset portal state
void portal_stop(); //stop portal
bool portal_tick(); //call in loop
void portal_run(uint32_t prd=60000); // delay like
byte portal_status(); // status: 1 - connect, 2 - ap, 3 - local, 4 - exit, 5 - timeout

void SP_handle_connect();
void SP_handleAP();
void SP_handle_local();
void SP_handle_exit();
#endif
