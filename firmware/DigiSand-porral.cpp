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

<fuorm onsubmit="connect(); return false;">

<div id="main_div" style="width:100%">
  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
    <input type="time" value="00:01" id="timer" style="scale:1.1; float:right;" class="timer" placeholder="timer">
  </div>

  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Angle auto</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Angle auto</span>-->
        <input type="checkbox" id="ch_angle_auto" class="checkbox-custom" placeholder="angle_auto">
        <span class="slider"></span>
      </label>
    </div>
    <br>
    <hr style="margin-left:0px; border: solid #b5b5b5 0.3px;">
    <p class="label_for_checkbox">Beep</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Beep</span>-->
        <input type="checkbox" id="ch_beep" class="checkbox-custom" placeholder="beep">
        <span class="slider"></span>
      </label>
    </div>
  </div>

  <div class="slider-container">
    <div class="horizontal-slider">
      <label style="flex-direction: column !important; color:#007aff; font-size: 20px; font-weight:normal;" class="label_for_checkbox">Brightness</label>
      <input type="range" id="brightness" style="width:100%;" min="-1" max="15" step="1" style="display:inline-flex;" name="vertical-range" orient="vertical" placeholder="brightness">
    </div>
  </div>

  <button class="main_button" id="submit" value="Submit" onclick="connect()">Apply</button>
</div>
</fourm>

  <!--
  <div class="footer">
    <a href="https://exch.com.ua/Bio.php" style="text-decoration: none; color: #007aff;">Arsenii's Technologies</a>
  </div>
  -->
</div>
</body> 

<script>
  document.addEventListener('DOMContentLoaded', () => 
  {
    set_height();
    set_width();
    function set_height()
    {
      let height=window.innerHeight;
      document.body.style.height=height+"px";
    }
    function set_width()
    {
      let width=window.innerWidth;
      if(width>450) width=450;
      document.getElementById("main_div").style.width=width-50+"px";
    }

    set_height();

    window.addEventListener('resize', set_height);
    window.addEventListener('resize', set_width);
  });

  function connect() 
  {
    var timer=document.getElementById("timer").value;
    var angle_auto=document.getElementById("ch_angle_auto").checked;
    var beep=document.getElementById("ch_beep").checked;
    var brightness=document.getElementById("brightness").value;

    if(angle_auto) angle_auto=1;
    else if(!angle_auto) angle_auto=0;
    if(beep) beep=1;
    else if(!beep) beep=0;

    var send_build='timer='+encodeURIComponent(timer)+'&angle_auto='+angle_auto+'&beep='+beep+'&brightness='+encodeURIComponent(brightness);
    console.log(send_build);
    fetch('/connect', 
    {
      method: 'POST',
      headers: 
      {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      body: new URLSearchParams(send_build)
    })
    .then(response => response.text())
    .then(text => 
    {
      //console.log('sent');
    })
    .catch(error => 
    {
      //console.error('Error:', error);
    })
  }
</script>

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

const char SP_login_page[] PROGMEM=R"rawliteral(

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
    <p class="center-text">DigiSand control - Wi-Fi</p>
  </div>
  <div style="padding-bottom:30px;"></div>
<div>

<div id="main_div" style="width:50px;">

  <label class="label_small">SSID:</label>
  <input type="text" class="text_inp" id="ssid_inp" placeholder="SSID">

  <label class="label_small">Password:</label>
  <input type="text" class="text_inp" id="pass_inp" placeholder="Password">

  <button id="submit" class="main_button">Apply</button>
</div>

  <div class="footer">
    <a href="https://exch.com.ua/Bio.php" style="text-decoration: none; color: #007aff;">Arsenii's Technologies</a>
  </div>
</div>
</body> 

<script>
  document.addEventListener('DOMContentLoaded', () => 
  {
    set_height();
    set_width();
    function set_height()
    {
      let height=window.innerHeight;
      document.body.style.height=height+"px";
    }
    function set_width()
    {
      let width=window.innerWidth;
      if(width>450) width=450;
      document.getElementById("main_div").style.width=width-50+"px";
    }

    set_height();

    window.addEventListener('resize', set_height);
    window.addEventListener('resize', set_width);
  });

  document.getElementById('submit').addEventListener('click', function() //apply
  {
    var url='digisand_control.php';

    let ssid=document.getElementById('ssid_inp').value;
    let pass=document.getElementById('pass_inp').value;

    let send_build;
    send_build='apply=123'+'&ssid='+ssid+'&pass='+pass;
    console.log(send_build);

    fetch('/connect_login',  
    {
      method: 'POST',
      headers: 
      {
        'Content-Type': 'application/x-www-form-urlencoded'
      },
      body: new URLSearchParams(send_build)
    })
    .then(response => response.text())
    .then(text => 
    {
      //console.log('sent');
    })
    .catch(error => 
    {
      console.error('Error:', error);
    })
  });
</script>

<style>
  body 
  {
    font-family:-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif !important;
    color:#1a1a1a;
    display:flex;
    flex-direction:column;
    align-items:center;
    background-color:#FFF;
    margin: 0;
    padding: 0;
    height: 100%;
    overflow-y: auto;
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

  button /*for every button*/
  {
    transition: all 0.1s ease-in-out;
  }
  .main_button, .main_button_red, .main_button_green, .secondary_button, .secondary_button_red /*main buttons*/
  {
    padding:14px;
    border:none;
    border-radius:15px;
    cursor:pointer;
    font-size:1rem;
    width:100%;
    margin-bottom:10px;
  }

  .main_button, .main_button_slim /*blue*/
  {
    background-color:#4c8bf5;
    border:2px solid #4c8bf5;
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.10);
    color:#fff;
  } 
  .main_button:hover, .main_button_slim:hover /*blue hover*/
  {
    background-color:#0057b5;
    border-color:#0057b5;
  }
  .main_button:active, .main_button_slim:active /*blue active*/
  {
    outline:none;
    background-color:#3093ff;
    border-color:#3093ff;
  }
  /*-------------*/
  .main_button_red, .main_button_red_slim /*red*/
  {
    background-color:#ff0000;
    border:2px solid #ff0000; 
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.10);
    color:#fff;
  }
  .main_button_red:hover, .main_button_red_slim:hover /*red hover*/
  {
    background-color:#be0000;
    border-color:#be0000;
  }
  .main_button_red:active, .main_button_red_slim:active /*red active*/
  {
    outline:none;
    background-color:#ff4a4a;
    border-color:#ff4a4a;
  }
  /*-------------*/
  .main_button_green, .main_button_green_slim /*green*/
  {
    background-color:#a2deae;
    border:2px solid #a2deae; 
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.10);
    color:#000000;
  }
  .main_button_green:hover, .main_button_green_slim:hover /*green hover*/
  {
    background-color:#88b991;
    border-color:#88b991;
  }
  .main_button_green:active, .main_button_green_slim:active /*green active*/
  {
    outline:none;
    background-color:#badfc1;
    border-color:#badfc1;
  }
  /*-------------*/

  .secondary_button
  {
    color:#fff;
    border:2px solid #4c8bf5; 
    color:black; 
    background:rgb(255, 255, 255, 0);
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.10);
  }
  .secondary_button:hover 
  {
    background-color:#4c8bf5;
    color:#fff;
  }
  .secondary_button:active 
  {
    background:rgb(255, 255, 255, 0);
    color:#000;
  }

  .secondary_button_red
  {
    color:#fff;
    border:2px solid #ff0000; 
    color:black; 
    background:rgb(255, 255, 255, 0);
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.10);
  }
  .secondary_button_red:hover 
  {
    background-color:#ff0000;
    color:#fff;
  }
  .secondary_button_red:active 
  {
    background:rgb(255, 255, 255, 0);
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

  .dropdown_container
  { 
    display:flex;
    flex-direction:column;
    align-items:center;
    padding:10px;
    border-radius:15px;
    background-color: rgba(0, 0, 0, 0.04);

    margin-bottom:15px;

    /*background: linear-gradient(45deg, rgba(245, 24, 189, 0.2), rgba(20, 222, 245, 0.2));*/
  }

  .dropdown_container label
  {
    font-weight:600;
    color:#007aff;
    margin-bottom:10px;
    font-size:20px;
  }

  .dropdown_container .label_small
  {
    font-weight:600;
    color:#007aff;
    margin-bottom:10px;
    font-size:16px;
    text-align:left;
    align-self:flex-start;
    margin-bottom:5px;
    margin-left:5px;  
  }

  .dropdown_container select
  {
    width:100%;
    padding:5px;
    border:1px solid #e0e0e0;
    border-radius:5px;
    background-color:rgba(255,255,255,0.6);
    cursor:pointer;
    margin-bottom:5px;
    color:#4c8bf5;
    font-size:larger;
  }

  .dropdown_container select:focus
  {
    border-color:#4c8bf5;
    outline:none;
  }

  .text_inp
  {
    font-size:1rem;
    width:100%;
    border-radius:15px;
    padding:15px;
    border-width:1px;
    background:#FFF;
    border:1px solid #e0e0e0;
    box-sizing:border-box; /*to make real width*/
    /*box-shadow:0 2px 5px rgba(0, 0, 0, 0.05);*/
  }

  .number_inp 
  {
    font-family:Arial, sans-serif;
    font-size:1rem;
    color:#000;
    border:1px solid #ccc;
    border-radius:5px;
    padding:5px;
    width:100%;
    max-width:100%;
    box-sizing:border-box;
    /*box-shadow:0 2px 5px rgba(0, 0, 0, 0.05);*/
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

void SP_login_handle_connect()
{
  strcpy(portalCfg.ssid, _SP_server.arg("ssid").c_str());
  strcpy(portalCfg.pass, _SP_server.arg("pass").c_str());

  portalCfg.mode=WIFI_AP;
  _SP_status=10;
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
  _SP_server.begin();
  _SP_started=true;
  _SP_status=0;
}

void login_portal_start()
{
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  IPAddress apIP(SP_AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SP_LOGIN_AP_NAME);
  
  _SP_dnsServer.start(53, "*", apIP);

  _SP_server.onNotFound([]() { _SP_server.send(200, "text/html", SP_login_page); });
  _SP_server.on("/connect_login", HTTP_POST, SP_login_handle_connect);
  _SP_server.begin();
  _SP_started=true;
  _SP_status=0;
}

void portal_stop()
{
  //WiFi.softAPdisconnect();
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
    if (_SP_status==1)
    {
      //portal_stop();
      return 1;
    }
    else if(_SP_status==10)
    {
      return 10;
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
