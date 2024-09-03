#include "DigiSand-portal.h"
static DNSServer _SP_dnsServer;
#ifdef ESP8266
static ESP8266WebServer _SP_server(80);
#else
static WebServer _SP_server(80);
#endif

const char SP_connect_page[] PROGMEM=R"rawliteral(
<!DOCTYPE html>
<html xmlns="//www.w3.org/1999/xhtml">
<head>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
	<meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta charset="Shift_JIS">
	<title>DigiSand control</title>
	<link rel="Website Icon" type="png" href="hourglass.png">
</head>
<body>
  <div class="back" style="height:30px;">
    <p class="center-text">DigiSand control</p>
  </div>
  <div style="padding-bottom:30px;"></div>
<div>

<form action="/connect" method="POST">

<div id="main_div" style="width:100%">
  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
    <input type="time" value="00:01" id="timer" style="scale:1.1; float:right;" name="timer">
  </div>

  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Angle auto</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Angle auto</span>-->
        <input type="checkbox" id="ch_angle_auto" class="checkbox-custom" name="angle_auto">
        <span class="slider"></span>
      </label>
    </div>
    <br>
    <hr style="margin-left:0px; border: solid #b5b5b5 0.3px;">
    <p class="label_for_checkbox">Beep</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Beep</span>-->
        <input type="checkbox" id="ch_beep" class="checkbox-custom" name="beep">
        <span class="slider"></span>
      </label>
    </div>
  </div>

  <div class="slider-container">
    <div class="horizontal-slider">
      <label style="flex-direction: column !important; color:#007aff; font-size: 20px; font-weight:normal;">Brightness</label>
      <input type="range" id="brightness" style="width:100%; display:inline-flex;" min="1" max="16" step="1" orient="vertical" name="brightness">
    </div>
  </div>

  <button class="main_button" value="Submit">Apply</button>
</div>
</form>
<!--
  <div class="footer">
    <a href="https://exch.com.ua/Bio.php" style="text-decoration: none; color: #007aff;">Arsenii's Technologies</a>
  </div>
-->
</div>
</body> 
<style>
  body 
  {
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
    background: linear-gradient(to bottom, #c7eaff, #ffd9a1);
    color: #1c1c1e;
    margin: 0;
    padding: 20px;
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  .back 
  {
    background-color: #a2deae;
    width: 100%;
    position: fixed;
    z-index: 4;
    margin-bottom: 10px;
    top: 0;
    text-align: center;
    height:auto;
  }

  .back a 
  {
    position: absolute;
    left: 10px;
  }

  .back button 
  {
    position: absolute;
    right: 10px;
  }

  .center-text 
  {
    display: inline-block;
    margin: 0 auto;
    font-size: larger;
  }

  .apple-switch input[type="checkbox"]
  {
    display: none;
  }

  .apple-switch .slider
  {
    position: relative;
    display: inline-block;
    width: 50px;
    height: 24px;
    background-color: #d1d1d1;
    border-radius: 34px;
    transition: background-color 0.2s;
    align-items: end;
    cursor:pointer;
  }

  .apple-switch input[type="checkbox"]:checked + .slider
  {
    background-color: #a2deae;
    align-items: end;
  }

  .apple-switch .slider:before
  {
    position: absolute;
    content: "";
    height: 16px;
    width: 16px;
    left: 4px;
    bottom: 4px;
    background-color: #fff;
    border-radius: 50%;
    transition: transform 0.2s;
  }

  .apple-switch input[type="checkbox"]:checked + .slider:before
  {
    transform: translateX(26px);
  }

  .label_for_checkbox 
  {
    display:inline;
    color:#007aff;
    font-size: 20px;
  }
  .item_c label.label_for_checkbox:hover {color:red; text-decoration: underline; cursor: pointer;}

  .checkbox
  {
    background-color: #000000;
    color:red;
    align-items: end !important;
  }

  .checkbox-custom
  {
    align-items: end !important;
    text-align: right;
    float: right;
  }

  .slider_characteristic 
  {
    font-size: 0.8rem;
    color: #6e6e73;
    margin-top: 5px;
  }
  .slider-item 
  {
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  .main_button
  {
    background-color: #007aff;
    color: #fff;
    padding: 15px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 1rem;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
    border: 2px solid #007aff; 
    margin-bottom: 20px;
    width: 100%;
  }
  .main_button:hover 
  {
    background-color: #0057b5;
  }
  .main_button:active 
  {
    outline: none;
    background-color: #3093ff;
  }

  .secondary_button
  {
    background-color: #007aff;
    color: #fff;
    padding: 15px;
    border: none;
    border-radius: 15px;
    cursor: pointer;
    font-size: 1rem;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
    margin-bottom: 20px;
    width:100%; 
    border: 2px solid #007aff; 
    color: black; 
    background:rgb(255, 255, 255, 0);
  }
  .secondary_button:hover 
  {
    background:rgb(255, 255, 255, 0.3) !important;
  }
  .secondary_button:active 
  {
    outline: none;
    background:rgb(255, 255, 255, 0.8) !important;
  }

  .home-container
  {
    display: flex;
    flex-wrap: wrap;
    gap: 20px;
    justify-content: center;
    margin-bottom: 20px;
  }

  .section
  {
    flex: 1;
    max-width: 200px;
    min-width: 150px;
  }

  .section h2
  {
    font-size: 1.2rem;
    margin-bottom: 10px;
  }

  .card
  {
    background: rgba(255, 255, 255, 0.7);
    border-radius: 15px;
    padding: 15px;
    text-align: center;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100px;
  }

  .card .icon
  {
    font-size: 1.5rem;
    margin-bottom: 5px;
  }

  .card .status
  {
    font-size: 0.9rem;
    color: #6e6e73;
  }

  .slider-container
  {
    display: flex;
    gap: 20px;
    margin-bottom: 20px;
  }

  .sliders-row 
  {
    display: flex;
    gap: 15px;
  }

  .vertical-slider, .horizontal-slider 
  {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 15px;
    background: rgba(255, 255, 255, 0.6);
    border-radius: 15px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
    width:100%;
  }

  .vertical-slider label, .horizontal-slider label 
  {
    font-weight: 600;
    color: #007aff;
    margin-bottom: 10px;
  }

  .vertical-slider input[type="range"], .horizontal-slider input[type="range"] 
  {
    -webkit-appearance: none;
    background: #ddd;
    outline: none;
    border-radius: 5px;
  }

  .vertical-slider input[type="range"] 
  {
    writing-mode: bt-lr; /* IE */
    -webkit-appearance: slider-vertical; /* WebKit */
    width: 8px;
    height: 200px;
  }

  .horizontal-slider input[type="range"]
  {
    width: 100px;
    height: 8px;
  }

  input[type="range"]::-webkit-slider-thumb
  {
    -webkit-appearance: none;
    appearance: none;
    width: 15px;
    height: 15px;
    background: #007aff;
    border-radius: 50%;
    cursor: pointer;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
  }

  input[type="range"]::-moz-range-thumb
  {
    width: 24px;
    height: 24px;
    background: #007aff;
    border-radius: 50%;
    cursor: pointer;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
  }

  .dropdown-container
  {
    display: flex;
    flex-direction: column;
    align-items: center;
    padding: 15px;
    background: rgba(255, 255, 255, 0.6);
    border-radius: 15px;
    box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);

    margin-bottom: 20px;
  }

  .dropdown-container label
  {
    font-weight: 600;
    color: #007aff;
    margin-bottom: 10px;
  }

  .dropdown-container select
  {
    width: 100%;
    padding: 10px;
    border: 1px solid #e0e0e0;
    border-radius: 10px;
    background-color: #f9f9f9;
    cursor: pointer;
    margin-bottom: 15px;
    color: #007aff;
    font-size: larger;
  }

  .dropdown-container select:focus
  {
    border-color: #007aff;
    outline: none;
  }

  .apply-button
  {
    background-color: #007aff;
    color: #fff;
    padding: 10px 20px;
    border: none;
    border-radius: 10px;
    cursor: pointer;
    font-size: 1rem;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);
    transition: background-color 0.3s;
  }

  .apply-button:hover
  {
    background-color: #005bb5;
  }

  .apply-button:focus
  {
    outline: none;
    background-color: #005bb5;
  }

  .footer 
  {
    position: fixed;
    bottom: 20px;
    right: 20px;
    font-size: 1rem;
    color: #6e6e73;
    background: rgba(255, 255, 255, 0.7);
    padding: 5px 10px;
    border-radius: 10px;
    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    color: #007aff;
  }

</style>
</html>


)rawliteral";

static bool _SP_started=false;
static byte _SP_status=0;
PortalCfg portalCfg;

void SP_handle_connect()
{
  strcpy(portalCfg.timer, _SP_server.arg("timer").c_str());
  strcpy(portalCfg.brightness, _SP_server.arg("brightness").c_str());
  strcpy(portalCfg.angle_auto, _SP_server.arg("angle_auto").c_str());
  strcpy(portalCfg.beep, _SP_server.arg("beep").c_str());

  portalCfg.mode=WIFI_AP;
  _SP_status=1;
}

void SP_handleAP()
{
  portalCfg.mode=WIFI_AP;
  _SP_status=2;
}

void SP_handle_local()
{
  portalCfg.mode=WIFI_AP;
  _SP_status=3;
}

void SP_handle_exit() { _SP_status=4; }

void portal_start()
{
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  IPAddress apIP(SP_AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SP_AP_NAME);
  _SP_dnsServer.start(53, "*", apIP);

  _SP_server.onNotFound([]() { _SP_server.send(200, "text/html", SP_connect_page); });
  _SP_server.on("/connect", HTTP_POST, SP_handle_connect);
  _SP_server.on("/ap", HTTP_POST, SP_handleAP);
  _SP_server.on("/local", HTTP_POST, SP_handle_local);
  _SP_server.on("/exit", HTTP_POST, SP_handle_exit);
  _SP_server.begin();
  _SP_started=true;
  _SP_status=0;
}

void portal_stop()
{
  WiFi.softAPdisconnect();
  _SP_server.stop();
  _SP_dnsServer.stop();
  _SP_started=false;
}

bool portal_tick()
{
  if (_SP_started)
  {
    _SP_dnsServer.processNextRequest();
    _SP_server.handleClient();
    yield();
    if (_SP_status)
    {
      //portal_stop();
      return 1;
    }
  }
  return 0;
}

void portal_run(uint32_t prd)
{
  uint32_t tmr=millis();
  portal_start();
  while (!portal_tick())
  {
    if (millis() - tmr > prd)
    {
      _SP_status=5;
      portal_stop();
      break;
    }
    yield();
  }
}

void portal_reset()
{
  _SP_status=0;
}

byte portal_status() 
{ 
  return _SP_status; 
}