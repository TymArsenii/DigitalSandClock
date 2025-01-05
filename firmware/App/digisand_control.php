<!DOCTYPE html>
<html xmlns="//www.w3.org/1999/xhtml">
<head>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
	<meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta name="theme-color" content="#a2deae">
  <meta name="author" content="Arsenii Tymoshenko">
  <meta charset="Shift_JIS">
	<title>DigiSand control</title>
	<link rel="Website Icon" type="png" href="hourglass.png">

  <script src="https://unpkg.com/mqtt/dist/mqtt.min.js"></script>
</head>
<body onload="check_cookie()">
  <div class="back" style="height:30px;">
    <a style="text-align:left;" href="/">&nbsp; ←Menu</a>
    <!-- <button id="log_out" class="main_button" style="border-radius:10px; width:auto; padding:3px; margin-left:50px; margin-bottom:0;">Log out</button> -->
    <p class="center-text" style="margin-left:63px;">DigiSand control</p>
    <img src="offline_indicator.svg" id="device_state_img" style="width:63px; height:28px; float:right; margin-right:5px;">
  </div>
  <div style="padding-bottom:25px;"></div>
<div>

<div id="main_div" style="width:50px;">
  <div class="dropdown-container">
    <label style="display:flex; flex-direction:column !important; color:#007aff; font-size:20px; font-weight:600; text-align:center!important;">Mode</label>
    <select name="mode" id="mode" onchange="mode_change()">
      <option value="1">Sand (Timer)</option>
      <option value="2">Standby Clock</option>
      <!--<option value="3">Stopwatch</option>-->
    </select>
  </div>

  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius:15px; box-shadow:0 2px 5px rgba(0, 0, 0, 0.1);">
    <label style="display:flex; flex-direction:column !important; color:#007aff; font-size:20px; font-weight:600; text-align:center!important;">Controls</label>

    <div id="timer_items" style="margin:0;">
      <!--
      <div style="margin-bottom:8px; display:inline;">
        <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
        <input type="time" value="00:01" id="timer" style="scale:1.1; float:right;">
      </div>
      <br>
      -->

      <div style="margin:8px;"></div>
      <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
      <div class="time_picker" style="float:right;">
        <select id="t_hours">
          <script>
            for (let i=0; i<24; i++) 
            {
              document.write(`<option value="${i}">${String(i).padStart(2, '0')}</option>`);
            }
          </script>
        </select>
        <span>:</span>
        <select id="t_minutes">
          <script>
            for (let i=0; i<60; i++) 
            {
              document.write(`<option value="${i}">${String(i).padStart(2, '0')}</option>`);
            }
          </script>
        </select>
        <span>:</span>
        <select id="t_seconds">
          <script>
            for (let i=0; i<60; i++) 
            {
              document.write(`<option value="${i}">${String(i).padStart(2, '0')}</option>`);
            }
          </script>
        </select>
      </div>
      <div style="margin:12px;"></div>

      <hr style="margin-left:0px; border:solid #b5b5b5 0.3px; width:100%;">
      <p class="label_for_checkbox">Demo</p>
      <div style="margin-bottom:8px; display:inline; float:right;">
        <label class="apple-switch">
          <!--<span class="label_for_checkbox">Angle auto</span>-->
          <input type="checkbox" id="ch_angle_auto" class="checkbox-custom">
          <span class="slider"></span>
        </label>
      </div>
      <div style="margin:8px;"></div>
      <hr style="margin-left:0px; border:solid #b5b5b5 0.3px; width:100%;">
      <p class="label_for_checkbox">Beep</p>
      <div style="margin-bottom:8px; display:inline; float:right;">
        <label class="apple-switch">
          <!--<span class="label_for_checkbox">Beep</span>-->
          <input type="checkbox" id="ch_beep" class="checkbox-custom">
          <span class="slider"></span>
        </label>
      </div> 
    </div>

    <div id="clock_items" style="margin-bottom:0;">
      <p class="label_for_checkbox">Time Zone &nbsp;&nbsp;&nbsp;</p>
      <div class="time_picker" style="float:right;">
        <select id="time_zone">
          <script>
            for (let i=-12; i<=14; i++) 
            {
              let disp_value;
              if(i<0) disp_value=i;
              else disp_value='+'+i;
              document.write(`<option value="${i}">${disp_value}</option>`);
            }
          </script>
        </select>
      </div>
      <div style="display:none;">
        <div style="margin:12px;"></div>
        <hr style="margin-left:0px; border:solid #b5b5b5 0.3px; width:100%;">
        <div style="display:inline; margin-bottom:0;">
          <div style="display:flex; align-items:center; width:100%; margin:0;">
            <p class="label_for_checkbox" style="line-height:80%;">NTP server</p>
            <input type="text" id="ntp_url" value="pool.ntp.org" style="padding-left:8px; font-size:1rem; height:30px; width:100%; flex:1; border-radius:7px; border-width:1px; margin-right:5px; margin-left:5px; background:rgba(255, 255, 255, 0.6); border:1px solid #e0e0e0;">
            <button id="def_ntp" onclick="def_ntp()" class="main_button" style="flex-shrink:0; width:auto; padding:7px; margin:0; border:#007aff, solid, 1px; border-radius:8px;">default</button>
          </div>
        </div>
      </div>
    </div>

    <div id="stopwatch_items">
      <div style="margin-bottom:8px; display:inline;">
        <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
        <input type="time" value="00:01" id="timer" style="scale:1.1; float:right;">
      </div>
      <br>
      <hr style="margin-left:0px; border:solid #b5b5b5 0.3px; width:100%;">
    </div>

    <hr style="margin-left:0px; border:solid #b5b5b5 0.3px; width:100%;">
    <div class="horizontal-slider" style="width:100%; display:flex; align-items:center; padding:0; margin-top:16px; margin-bottom:8px;">
      <p class="label_for_checkbox" style="line-height:1; margin:0 10px 0 0;">Brightness</p>
      <input type="range" id="brightness" min="-1" max="15" step="1" style="flex-grow:1; padding:0;">
    </div>


  </div>

  

  <button id="submit" class="main_button">Apply</button>
</div>

  <div class="footer">
    <a href="https://exch.com.ua/Bio.php" style="text-decoration:none; color:#007aff;">Arsenii’s Technologies</a>
  </div>
</div>
</body> 

<script>
  var user=get_cookie("device_id");
  let offline_timer;
  let device_curr_state;
  let apply_timeout;

  const client=mqtt.connect('wss://test.mosquitto.org:8081/mqtt');

  client.on('connect', () => { //When connected
    console.log('Connected to test.mosquitto.org');
  
    const topic='digi_sand_local_Ars';
    client.subscribe(topic, (err) => 
    {
      if (!err) 
      {
        //console.log(`Subscribed to ${topic}`);
        console.log('subscribed');
      } 
      else 
      {
        console.error('Subscription error:', err);
      }
    });
  });

  // When a message is received
  client.on('message', (topic, message) => 
  {
    //console.log(`Message received on ${topic}:${message.toString()}`);
    let incomming_message=message.toString();
    console.log(`Message received:${incomming_message}`);

    const queryString=incomming_message;
    const params=new URLSearchParams(queryString);

    const device_id_send=params.get("device_id");
    const status_send=params.get("status");

    console.log("Device ID:", device_id_send);
    console.log("Status:", status_send);

    if(device_id_send==user && status_send=="online-ok")
    {
      device_state(1);
      clearTimeout(offline_timer);
      offline_timer=setTimeout(device_state, 3000);
    }

    if(device_id_send==user && status_send=="reseaved")
    {
      console.log("reveig");
      clearTimeout(apply_timeout);
      reset_button_color();
    }


    let send_build;
    send_build='status='+status_send+'&device_id='+device_id_send;
    console.log('AJAX_send:'+send_build);

    //status:online;

    var url='digisand_control.php';
    fetch(url, 
    {
      method:'POST',
      headers:
      {
        'Content-Type':'application/x-www-form-urlencoded'
      },
      body:new URLSearchParams(send_build)
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

  client.on('error', (err) => 
  {
    console.error('MQTT Error:', err);
  });

  
  function device_state(state=0)
  {
    if(state==0) document.getElementById("device_state_img").src="offline_indicator.svg";
    else if(state==1) document.getElementById("device_state_img").src="online_indicator.svg";

    device_curr_state=state;
  }
  function timed_out()
  {
    document.getElementById("submit").innerHTML='Timed out';
    document.getElementById("submit").style.backgroundColor='#fcba03';
    document.getElementById("submit").style.borderColor='#fcba03';

    setTimeout(reset_button_color, 800);
  }
  function reset_button_color()
  {
    document.getElementById("submit").innerHTML='Apply';
    document.getElementById("submit").style.backgroundColor='#007aff';
    document.getElementById("submit").style.borderColor='#007aff';
  }

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
      document.getElementById("main_div").style.width=width-25+"px";
    }

    set_height();

    window.addEventListener('resize', set_height);
    window.addEventListener('resize', set_width);

    //-----------------------------------------------------------------------------------------------

    let send_build;
    send_build='request=hey_you_give_me_the_data'+'&device_id='+user;
    //console.log(send_build);

    var url='digisand_control.php';
    fetch(url, 
    {
      method:'POST',
      headers:
      {
        'Content-Type':'application/x-www-form-urlencoded'
      },
      body:new URLSearchParams(send_build)
    })
    .then(response => response.text())
    .then(text => 
    {
      text=text.trim();
      console.log(text);

      let decoded_text_tmp;
      decoded_text_tmp=JSON.parse(text);

      // {"id":"1","device_id":"1","selected":"1","importance":"0","mode":"3","brightness":"255","hue":"84","sat":"255","smooth":"14","br1":"0","br2":"255","speed":"9","freq":"297"}

      let mode=decoded_text_tmp.mode;
      let timer=decoded_text_tmp.timer;
      let brightness=decoded_text_tmp.brightness;
      let angle_auto=decoded_text_tmp.angle_auto ? true :false;
      let beep=decoded_text_tmp.beep;
      let time_zone=decoded_text_tmp.time_zone;
      let ntp_url=decoded_text_tmp.ntp_url;

      if(angle_auto==0) angle_auto=false;
      else if(angle_auto==1) angle_auto=true;

      if(beep==0) beep=false;
      else if(beep==1) beep=true;
      
      document.getElementById('mode').value=mode;

      let [t_hours, t_minutes, t_seconds]=timer.split(':');
      t_hours=parseInt(t_hours, 10);
      t_minutes=parseInt(t_minutes, 10);
      t_seconds=parseInt(t_seconds, 10);

      document.getElementById('t_hours').value=t_hours;
      document.getElementById('t_minutes').value=t_minutes;
      document.getElementById('t_seconds').value=t_seconds;

      document.getElementById('brightness').value=brightness;
      document.getElementById('ch_angle_auto').checked=angle_auto;
      document.getElementById('ch_beep').checked=beep;
      document.getElementById('time_zone').value=time_zone;
      document.getElementById('ntp_url').value=ntp_url;

      mode_change();
      setTimeout(device_state, 1000);
    })
    .catch(error => 
    {
      //console.error('Error:', error);
    })
  });

  function def_ntp()
  {
    document.getElementById("ntp_url").value="pool.ntp.org";
  }

  function adjustBodyHeight() 
  {
    const body=document.body;
    const html=document.documentElement;

    const bodyHeight=Math.max(body.scrollHeight, body.offsetHeight, html.clientHeight, html.scrollHeight, html.offsetHeight);

    if (bodyHeight>window.innerHeight) 
    {
      body.style.height=`${bodyHeight}px`;
    } 
    else 
    {
      body.style.height='100vh';
    }
  }

  window.addEventListener('load', adjustBodyHeight);
  window.addEventListener('resize', adjustBodyHeight);

  document.getElementById('submit').addEventListener('click', function() // apply
  {
    if(device_curr_state==1) 
    {
      document.getElementById("submit").innerHTML='Apply <div class="loader" style="clear:both; display:inline-block;"></div>';
      document.getElementById("submit").style.backgroundColor='#007aff';
      document.getElementById("submit").style.borderColor='#007aff';

      apply_timeout=setTimeout(timed_out, 2250);
    }
    else if(device_curr_state==0) 
    {
      document.getElementById("submit").innerHTML='Device is offline';
      document.getElementById("submit").style.backgroundColor='red';
      document.getElementById("submit").style.borderColor='red';

      setTimeout(reset_button_color, 800);
    }
    var url='digisand_control.php';

    let mode=document.getElementById("mode").value;
    let brightness=document.getElementById('brightness').value;
    let timer=document.getElementById('timer').value;
    let timer_hours=document.getElementById("t_hours").value;
    let timer_minutes=document.getElementById("t_minutes").value;
    let timer_seconds=document.getElementById("t_seconds").value;
    let angle_auto=document.getElementById('ch_angle_auto').checked;
    let beep=document.getElementById('ch_beep').checked;
    let ntp_url=document.getElementById("ntp_url").value;
    let time_zone=document.getElementById("time_zone").value;

    let total_time=parseInt(timer_hours*3600)+parseInt(timer_minutes*60)+parseInt(timer_seconds);
    if(total_time<=0)
    {
      timer_seconds=1;
      document.getElementById("t_seconds").value=1;
    }
    console.log(total_time);

    timer=timer.split(':').slice(0, 2).join(':');
    timer=timer_hours+':'+timer_minutes+':'+timer_seconds;

    if(angle_auto) angle_auto=1;
    else if(!angle_auto) angle_auto=0;
    if(beep) beep=1;
    else if(!beep) beep=0;

    let send_build;
    send_build='apply=123'+'&device_id='+user+'&mode='+mode+'&brightness='+brightness+'&timer='+timer+'&angle_auto='+angle_auto+'&beep='+beep+'&time_zone='+time_zone+'&ntp_url='+ntp_url;
    console.log(send_build);

    fetch(url, 
    {
      method:'POST',
      headers:
      {
        'Content-Type':'application/x-www-form-urlencoded'
      },
      body:new URLSearchParams(send_build)
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

  function mode_change()
  {
    document.getElementById('timer_items').style.display="none";
    document.getElementById('clock_items').style.display="none";
    document.getElementById('stopwatch_items').style.display="none";

    let mode_value=document.getElementById('mode').value;
    console.log(mode_value);

    if(mode_value==1)
    {
      document.getElementById('timer_items').style.display="block";
    }
    else if(mode_value==2)
    {
      document.getElementById('clock_items').style.display="block";
    }
    else if(mode_value==3)
    {
      document.getElementById('stopwatch_items').style.display="block";
    }
  }
  
  //-------------------------------------------------------------------------------------------------------------------------------

  //cookies ->

  document.getElementById('log_out').addEventListener('click', function()
  {
    user="";
    set_cookie("device_id", user, 30);
    check_cookie();
  });

  function set_cookie(cname, cvalue, exdays) 
  {
    const d=new Date();
    d.setTime(d.getTime()+(exdays*24*60*60*1000));
    let expires="expires=" + d.toUTCString();
    document.cookie=cname + "=" + cvalue + ";" + expires + ";path=/";
  }

  function get_cookie(cname) 
  {
    let name=cname+"=";
    let decodedCookie=decodeURIComponent(document.cookie);
    let ca=decodedCookie.split(';');
    for(let i=0; i < ca.length; i++) 
    {
      let c=ca[i];
      while (c.charAt(0) == ' ')
      {
        c=c.substring(1);
      }
      if (c.indexOf(name) == 0)
      {
        return c.substring(name.length, c.length);
      }
    }
    return "";
  }

  function check_cookie() 
  {
    if (user!="") 
    {
      //alert("I use cookies and I won't ask the permision😆 "+"\r\n"+"(cookies are not dangerous. at ALL)");
    } 
    else 
    {
      user=prompt("Enter your device id:","");
      if (user!=""&&user!=null) 
      {
        set_cookie("device_id", user, 30);
      }
    }
  }
</script>

<style>
  body 
  {
    font-family:-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
    background:linear-gradient(to bottom, #c7eaff, #ffd9a1);
    color:#1c1c1e;
    margin:0;
    padding:20px;
    display:flex;
    flex-direction:column;
    align-items:center;
  }

  .back 
  {
    background-color:#a2deae;
    width:100%;
    position:fixed;
    z-index:4;
    margin-bottom:10px;
    top:0;
    text-align:center;
    height:auto;
  }

  .loader 
  {
    border: 4px solid #f3f3f3;
    border-radius: 50%;
    border-top: 4px solid #3498db;
    width: 10px;
    height: 10px;
    -webkit-animation: spin 1s linear infinite;
    animation: spin 1s linear infinite;
  }

  @-webkit-keyframes spin 
  {
    0% { -webkit-transform: rotate(0deg); }
    100% { -webkit-transform: rotate(360deg); }
  }

  @keyframes spin 
  {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }

  .back a 
  {
    position:absolute;
    left:10px;
  }

  .back button 
  {
    position:absolute;
    right:10px;
  }

  .center-text 
  {
    display:inline-block;
    margin:0 auto;
    font-size:larger;
  }

  .apple-switch input[type="checkbox"]
  {
    display:none;
  }

  .apple-switch .slider
  {
    position:relative;
    display:inline-block;
    width:50px;
    height:24px;
    background-color:#d1d1d1;
    border-radius:34px;
    transition:background-color 0.2s;
    align-items:end;
    cursor:pointer;
  }

  .time_picker 
  {
    display:flex;
    gap:5px;
    align-items:center;
    font-family:Arial, sans-serif;
  }

  .time_picker select 
  {
    padding:5px;
    font-size:1rem;
    color:#007aff;
    border:1px solid #ccc;
    border-radius:5px;
  }

  .apple-switch input[type="checkbox"]:checked + .slider
  {
    background-color:#a2deae;
    align-items:end;
  }

  .apple-switch .slider:before
  {
    position:absolute;
    content:"";
    height:16px;
    width:16px;
    left:4px;
    bottom:4px;
    background-color:#fff;
    border-radius:50%;
    transition:transform 0.2s;
  }

  .apple-switch input[type="checkbox"]:checked + .slider:before
  {
    transform:translateX(26px);
  }

  .label_for_checkbox 
  {
    display:inline;
    color:#007aff;
    font-size:20px;
  }
  .item_c label.label_for_checkbox:hover {color:red; text-decoration:underline; cursor:pointer;}

  .checkbox
  {
    background-color:#000000;
    color:red;
    align-items:end !important;
  }

  .checkbox-custom
  {
    align-items:end !important;
    text-align:right;
    float:right;
  }

  .slider_characteristic 
  {
    font-size:0.8rem;
    color:#6e6e73;
    margin-top:5px;
  }
  .slider-item 
  {
    display:flex;
    flex-direction:column;
    align-items:center;
  }

  .main_button
  {
    background-color:#007aff;
    color:#fff;
    padding:15px;
    border:none;
    border-radius:15px;
    cursor:pointer;
    font-size:1rem;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.2);
    border:2px solid #007aff; 
    /*margin-bottom:20px;*/
    width:100%;
  }
  .main_button:hover 
  {
    background-color:#0057b5;
  }
  .main_button:active 
  {
    outline:none;
    background-color:#3093ff;
  }

  .secondary_button
  {
    background-color:#007aff;
    color:#fff;
    padding:15px;
    border:none;
    border-radius:15px;
    cursor:pointer;
    font-size:1rem;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.2);
    margin-bottom:20px;
    width:100%; 
    border:2px solid #007aff; 
    color:black; 
    background:rgb(255, 255, 255, 0);
  }
  .secondary_button:hover 
  {
    background:rgb(255, 255, 255, 0.3) !important;
  }
  .secondary_button:active 
  {
    outline:none;
    background:rgb(255, 255, 255, 0.8) !important;
  }

  .home-container
  {
    display:flex;
    flex-wrap:wrap;
    gap:20px;
    justify-content:center;
    margin-bottom:20px;
  }

  .section
  {
    flex:1;
    max-width:200px;
    min-width:150px;
  }

  .section h2
  {
    font-size:1.2rem;
    margin-bottom:10px;
  }

  .card
  {
    background:rgba(255, 255, 255, 0.7);
    border-radius:15px;
    padding:15px;
    text-align:center;
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.1);
    display:flex;
    flex-direction:column;
    align-items:center;
    justify-content:center;
    height:100px;
  }

  .card .icon
  {
    font-size:1.5rem;
    margin-bottom:5px;
  }

  .card .status
  {
    font-size:0.9rem;
    color:#6e6e73;
  }

  .slider-container
  {
    display:flex;
    gap:20px;
    margin-bottom:20px;
  }

  .sliders-row 
  {
    display:flex;
    gap:15px;
  }

  .vertical-slider, .horizontal-slider 
  {
    /*background:rgba(255, 255, 255, 0.6);
    border-radius:15px;
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.1);
    width:100%;*/
  }

  .vertical-slider label, .horizontal-slider label 
  {
    font-weight:600;
    color:#007aff;
    margin-bottom:10px;
  }

  .vertical-slider input[type="range"], .horizontal-slider input[type="range"] 
  {
    -webkit-appearance:none;
    background:#ddd;
    outline:none;
    border-radius:5px;
  }

  .vertical-slider input[type="range"] 
  {
    writing-mode:bt-lr; /* IE */
    -webkit-appearance:slider-vertical; /* WebKit */
    width:8px;
    height:200px;
  }

  .horizontal-slider input[type="range"]
  {
    width:100px;
    height:8px;
  }

  input[type="range"]::-webkit-slider-thumb
  {
    -webkit-appearance:none;
    appearance:none;
    width:15px;
    height:15px;
    background:#007aff;
    border-radius:50%;
    cursor:pointer;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.2);
  }

  input[type="range"]::-moz-range-thumb
  {
    width:24px;
    height:24px;
    background:#007aff;
    border-radius:50%;
    cursor:pointer;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.2);
  }

  .label_h1
  {
    font-weight:600;
    color:#007aff;
    margin-bottom:10px;
  }

  .dropdown-container
  {
    display:flex;
    flex-direction:column;
    align-items:center;
    padding:10px;
    background:rgba(255, 255, 255, 0.6);
    border-radius:15px;
    box-shadow:0 2px 5px rgba(0, 0, 0, 0.1);

    margin-bottom:15px;
  }

  .dropdown-container label
  {
    font-weight:600;
    color:#007aff;
    margin-bottom:10px;
  }

  .dropdown-container select
  {
    width:100%;
    padding:5px;
    border:1px solid #e0e0e0;
    border-radius:5px;
    background-color:#f9f9f9;
    cursor:pointer;
    margin-bottom:5px;
    color:#007aff;
    font-size:larger;
  }

  .dropdown-container select:focus
  {
    border-color:#007aff;
    outline:none;
  }

  .apply-button
  {
    background-color:#007aff;
    color:#fff;
    padding:10px 20px;
    border:none;
    border-radius:10px;
    cursor:pointer;
    font-size:1rem;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.2);
    transition:background-color 0.3s;
  }

  .apply-button:hover
  {
    background-color:#005bb5;
  }

  .apply-button:focus
  {
    outline:none;
    background-color:#005bb5;
  }

  .footer 
  {
    position:fixed;
    bottom:20px;
    right:20px;
    font-size:1rem;
    color:#6e6e73;
    background:rgba(255, 255, 255, 0.7);
    padding:5px 10px;
    border-radius:10px;
    box-shadow:0 2px 4px rgba(0, 0, 0, 0.1);
    color:#007aff;
  }

</style>
</html>
