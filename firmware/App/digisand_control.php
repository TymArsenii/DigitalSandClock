<!DOCTYPE html>
<html xmlns="//www.w3.org/1999/xhtml">
<head>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
	<meta name="viewport" content="width=device-width, initial-scale=1" />
  <link rel="stylesheet" type="text/css" href="/general_style.css">
  <meta name="theme-color" content="#a2deae">
  <meta name="author" content="Arsenii Tymoshenko">
  
  <meta charset="Shift_JIS">
	<title>DigiSand control</title>
	<link rel="Website Icon" type="png" href="hourglass.png">

  <script src="https://unpkg.com/mqtt/dist/mqtt.min.js"></script>
</head>
<body>
  <div class="opacity" id="opacity"></div>

  <div class="back" id="top_bar">
    <a style="text-align:left;" href="/">&nbsp; ←Menu</a>
    <!--<button id="log_out" class="main_button" style="border-radius:10px; width:auto; padding:3px; margin-right:65px; float:right;">Log out</button>-->
    <h1>DigiSand control</h1>
  </div>
  <div style="padding-bottom:25px;"></div>

<div class="tab_bar" style="display:none;">
  <div class="tab active" onclick="set_active_tool(this)">Controls</div>
  <div class="tab" onclick="set_active_tool(this)">Device manager</div>
</div>

<div>

<div id="main_div" style="width:50px;">
  <p style="color:gray; font-size:large; text-align:center;" id="global_loading">Loading...</p>
  <div id="devices" style="display:none;">
    <p style='color:gray; text-align:center;' id="devices_loading">Loading...</p>
    <div class="dropdown_container" id="digisand">
      <label class="dropdown_label">DigiSand Control devices</label>

      <table class="devices_table" id="digisand_devices">
        <tr>
          <td style="padding-right:0;"><input type="text" class="number_inp id_field" placeholder="ID"></td>
          <td>—</td>
          <td style="padding-left:3px;"><input type="text" class="number_inp name_field" placeholder="Device Name"></td>
          <td style="padding-right:5px;"><button class='square_main_button_red' onclick='delete_row_click(this)'>–</button></td>
        </tr>
      </table>
      <div style="display:flex; justify-content:flex-end; width:100%; position:relative; right:5px; margin:5px;"><button class="square_main_button" onclick='add_field_digisand()' id="add_field_digisand_button">+</button></div>

      <button class="main_button_slim" id="digisand_apply">Apply</button>
      <p id="digisand_success" style="color:green; display:none;"></p>
      <p id="digisand_info" style="color:gray; display:none;"></p>
      <p id="digisand_error" style="color:red; display:none;"></p>
    </div>
    <button class="secondary_button" onclick="back_to_controls()">Back to Controls</button>
    <p style="text-align:center;">After pressing Apply button, all fields with ID left empty will be automatically deleted.</p>
  </div>

  <div id='controls' class="controls_flex">
    <div class='dropdown_container' id='device_container' style="margin-bottom:0px;">
      <div style="display:block; width:100%; text-align:center; margin-bottom:2px; position:relative;">
        <label style="display:inline-block; cursor:pointer;" onclick="manage_devices_click()">Device</label>
        <img src="/image/settings.png" id="manage_devices_button" onclick="manage_devices_click()" role="button" alt="manage" style="width:18px; height:18px; cursor:pointer;">
        <img src="offline_indicator.svg" id="device_state_img" style="width:63px; height:28px; margin-right:5px; position:absolute; right:0; top:45%; transform:translateY(-50%);">
      </div>

      <select name="device_select" id="device_select" onchange="change_device()"></select>
    </div>
    <div class="dropdown_container" id="mode_container" style="margin-bottom:0px;">
      <label class="dropdown_label">Mode</label>
      <select name="mode" id="mode" onchange="mode_change()">
        <option value="1">Sand (Timer)</option>
        <option value="2">Standby Clock</option>
        <!--<option value="3">Stopwatch</option>-->
      </select>
    </div>

    <div class="dropdown_container" style="display:block; margin-bottom:0px;" id="controls_container">
      <label style="display:block; text-align:center;">Controls</label>

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

      <div id="clock_items" style="margin-bottom:0; display:none;">
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
              <button id="def_ntp" onclick="def_ntp()" class="main_button" style="flex-shrink:0; width:auto; padding:7px; margin:0; border:, solid, 1px; border-radius:8px;">default</button>
            </div>
          </div>
        </div>
      </div>

      <div id="stopwatch_items" style="display:none;">
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

    <button id="submit" class="main_button" style="width:inherit; margin-top:0px;">Apply</button>  
  </div>

  <div class="notification_container" style="display:none;" id="notification_delete_row">
    <label>Are you sure?</label>
    <div style="text-align:left;">
      <p>One row will be deleted</p>

      <div style="display:flex; flex-direction:row; gap:10px;">
        <button class="secondary_button" style="flex:1;" id='cancel_delete_row'>Cancel</button>
        <button class="main_button_red" style="flex:1;" id='yes_delete_row'>Yes, delete</button>
      </div>

      <p style="font-style:italic; margin:0; color:#696969;">Tip: refreshing the page before pressing "Apply" will cancel all the changes.</p>
    </div>
  </div>
  <div class="notification_container" style="display:none;" id="notification_go_back">
    <label>Are you sure?</label>
    <div style="text-align:left;">
      <p>Unsaved changes will be deleted</p>

      <div style="display:flex; flex-direction:row; gap:10px;">
        <button class="secondary_button" style="flex:1;" id='cancel_go_back'>Cancel</button>
        <button class="main_button_red" style="flex:1;" id='yes_go_back'>Yes, go back</button>
      </div>
    </div>
  </div>
</div>

<input type="hidden" name="user_advanced" id="user_advanced" value="0">
</div>
<div class="footer">
	<a href="https://exch.com.ua/Bio.php" style="text-decoration:none; color:#007aff;">Arsenii’s Technologies</a>
</div>
</body> 

<script>
  let selected_tab='controls';
  let user_advanced=false;

  let offline_timer;
  let device_curr_state;
  let apply_timeout;

  const client=mqtt.connect('wss://test.mosquitto.org:8081/mqtt');

  client.on('connect', () => //When connected
  {
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

    //console.log("Device ID:", device_id_send);
    //console.log("Status:", status_send);

    let current_device_id=document.getElementById('device_select').value;
    if(device_id_send==current_device_id && status_send=="online-ok")
    {
      device_state(1);
      clearTimeout(offline_timer);
      offline_timer=setTimeout(device_state, 3000);
    }

    if(device_id_send==current_device_id && status_send=="reseaved")
    {
      //console.log("reveig");
      clearTimeout(apply_timeout);
      reset_button_color();
    }


    let send_build;
    send_build='status='+status_send+'&device_id='+device_id_send;
    //console.log('AJAX_send:'+send_build);

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
    if(state==0) 
    {
      document.getElementById("device_state_img").src="offline_indicator.svg"; 
      
      document.getElementById('device_container').style.backgroundColor='rgba(244, 171, 159, 0.4)';
    }
    else if(state==1) 
    {
      document.getElementById("device_state_img").src="online_indicator.svg"; 

      document.getElementById('device_container').style.backgroundColor='rgba(123, 183, 129, 0.2)';
    }

    /*
    let select = document.getElementById('dropdown_select');
    let selected_option = select.options[select.selectedIndex];

    let old_text = selected_option.text.trim();
    let words = old_text.split(/\s+/);
    let words_to_remove = [' — online', ' — offline'];

    let updated_words = words.filter(word => !words_to_remove.includes(word));

    updated_words.push('NewWord');
    selected_option.text = updated_words.join(' ');
    */

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
    document.getElementById("submit").style.backgroundColor='';
    document.getElementById("submit").style.borderColor='';
  }

  document.addEventListener('DOMContentLoaded', () => 
  {
    document.getElementById("global_loading").style.display='block';

    set_height();
    set_width();
    function set_height()
    {
      let height=window.innerHeight;
      //document.body.style.height=height+"px";
    }
    function set_width()
    {
      //let width=window.innerWidth;
      //if(width>450) width=450;
      //document.getElementById("main_div").style.width=width-25+"px";

      let width=window.innerWidth;
      if(selected_tab.toLocaleLowerCase()=="controls")
      {
        if(width>1100) width=1100;
        document.getElementById("main_div").style.width=width-25+"px";
      }
      else if(selected_tab.toLocaleLowerCase()=="device manager")
      {
        if(width>500) 
        {
          document.getElementById("main_div").style.width=100+"%";
        }
        else document.getElementById("main_div").style.width=width-25+"px";
      }
    }

    set_height();

    window.addEventListener('resize', set_height);
    window.addEventListener('resize', set_width);

      <? session_start(); ?>
      <?
      if(isset($_SESSION['user_authorized_name']) && isset($_SESSION['user_authorized']))
      {
        if($_SESSION['user_authorized'])
        {?>
          console.log('user is authorized -- ok');
          <?
        }
        else
        {?>
          console.log('user is not authorized');
          window.location.replace("https://exch.com.ua/logging/login.php");
          <?
        }
      }
      else
      {?>
        console.log('user is not authorized');
        window.location.replace("https://exch.com.ua/logging/login.php");
        <?
      }
      ?>

    <?
    if(!isset($_SESSION['user_authorized_name']) || !isset($_SESSION['user_authorized']) || !$_SESSION['user_authorized'])
    {?>
      window.location.replace("https://exch.com.ua/logging/login.php");
    <?
    }?>

    let user_authorized=false;
    <? 
    if(isset($_SESSION['user_authorized_login'])) 
    {?>
      let user='<? echo $_SESSION['user_authorized_login']; ?>';
      user_authorized=true;
  <?}
    else
    {?>
      user_authorized=false;
  <?}
    ?>

    if(user_authorized)
    {
      let send_build='get_user_name=1&user_login='+user;
      console.log(send_build);

      var url='/personal.php';

      fetch(url, 
      {
        method:'POST',
        headers:
        {
          'Content-Type':'application/x-www-form-urlencoded' //application/x-www-form-urlencoded
        },
        body:new URLSearchParams(send_build)
      })
      .then(response => response.text())
      .then(text => 
      {
        console.log('sent');
        console.log(text);
        let json_data=JSON.parse(text);
        
        if(typeof json_data.redirect!=='undefined')
        {
          console.log('redict=true');
          window.location.replace(json_data.redirect);
        }

        if(typeof json_data.user_name!=='undefined')
        {
          document.getElementById('user_advanced').value=json_data.user_advanced;
        }
      })
      .catch(error => 
      {
        console.error('Error:', error);
      })
    }
    else
    {
      window.location.replace("https://exch.com.ua/logging/login.php");
    }

    //-----------------------------------------------------------------------------------------------
    get_devices_primary();
  });

  function get_devices_primary()
  {
    <? session_start(); ?>
    <?
    if(isset($_SESSION['user_authorized_name']) && isset($_SESSION['user_authorized']))
    {
      if($_SESSION['user_authorized'])
      {?>
        console.log('user is authorized -- ok');
        <?
      }
      else
      {?>
        console.log('user is not authorized');
        window.location.replace("https://exch.com.ua/logging/login.php");
        <?
      }
    }
    else
    {?>
      console.log('user is not authorized');
      window.location.replace("https://exch.com.ua/logging/login.php");
      <?
    }
    ?>

    <?
    if(!isset($_SESSION['user_authorized_name']) || !isset($_SESSION['user_authorized']) || !$_SESSION['user_authorized'])
    {?>
      window.location.replace("https://exch.com.ua/logging/login.php");
    <?
    }?>

    var url='digisand_control.php';
    <? 
    if(isset($_SESSION['user_authorized_login'])) 
    {?>
      let user='<? echo $_SESSION['user_authorized_login']; ?>';
    <?}
    else
    {?>
      log_out();
    <?}
    ?>
    let send_build='get_devices=1&user_login='+user;
    console.log(send_build);

    fetch(url, 
    {
      method:'POST',
      headers:
      {
        'Content-Type':'application/x-www-form-urlencoded' //application/x-www-form-urlencoded
      },
      body:new URLSearchParams(send_build)
    })
    .then(response => response.text())
    .then(text => 
    {
      console.log('sent');
      console.log(text);
      let json_data=JSON.parse(text);

      const select=document.getElementById('device_select');
      select.innerHTML='';

      json_data.devices.forEach(device => 
      {
        const option=document.createElement('option');
        option.value=device.device_id;
        if(device.device_name.length>0) option.textContent=device.device_name;
        else option.textContent=device.device_id;
        select.appendChild(option);
      });

      const first_device_id=json_data.devices[0]?.device_id || '';
      let send_build;
      send_build='request=hey_you_give_me_the_data'+'&device_id='+first_device_id;
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
        document.getElementById("global_loading").style.display='none';
        setTimeout(device_state, 1000);
      })
      .catch(error => 
      {
        //console.error('Error:', error);
      })
    })
    .catch(error => 
    {
      console.error('Error:', error);
    })
  }

  function change_device()
  {
    let select=document.getElementById('device_select');
    let selected_device_id=select.value;
    console.log('Selected device ID:', selected_device_id);

    let send_build;
    send_build='request=hey_you_give_me_the_data'+'&device_id='+selected_device_id;
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
  }

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
      document.getElementById("submit").style.backgroundColor='';
      document.getElementById("submit").style.borderColor='';

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

    let current_device_id=document.getElementById('device_select').value;
    let send_build;
    send_build='apply=123'+'&device_id='+current_device_id+'&mode='+mode+'&brightness='+brightness+'&timer='+timer+'&angle_auto='+angle_auto+'&beep='+beep+'&time_zone='+time_zone+'&ntp_url='+ntp_url;
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

  
  function get_devices_input_data(table_id) 
  {
    let data=[];
    document.querySelectorAll('#' + table_id + ' tr').forEach(row => 
    {
      let device_id=row.querySelector('.id_field')?.value || '';
      let device_name=row.querySelector('.name_field')?.value || '';
      if(device_id) //skip empty rows
      {
        data.push({ device_id, device_name });
      }
    });
    return data;
  }
  document.getElementById("digisand_apply").addEventListener('click', function()  
  {
    let devices_fields_arr=get_devices_input_data('digisand_devices');
    console.log(devices_fields_arr);

    let digisand_info_timeout=setTimeout(function() 
    {
      document.getElementById('digisand_info').innerHTML='Timed out. Try again';
      setTimeout(function() 
      {
        document.getElementById('digisand_info').style.display='none';
      }, 1000);
    }, 2000);
    document.getElementById('digisand_info').style.display='block';
    document.getElementById('digisand_info').innerHTML='Processing...';

    <? 
    if(isset($_SESSION['user_authorized_login'])) 
    {?>
      let user='<? echo $_SESSION['user_authorized_login']; ?>';
  <?}
    else
    {?>
      log_out();
    <?}
    ?>

    let send_build;
    send_build='add_devices=2&user_login='+user+'&json=';
    send_build+=JSON.stringify
    ({
      devices_data_arr: devices_fields_arr
    });
    console.log(send_build);

    var url='/personal.php';

    fetch(url, 
    {
      method:'POST',
      headers:
      {
        'Content-Type':'application/x-www-form-urlencoded' //application/x-www-form-urlencoded
      },
      body:new URLSearchParams(send_build)
    })
    .then(response => response.text())
    .then(text => 
    {
      clearTimeout(digisand_info_timeout);
      document.getElementById('digisand_info').style.display='none';

      console.log('sent');
      console.log(text);
      let decoded_json=JSON.parse(text);
      if(decoded_json)
      {
        if(typeof decoded_json.redirect!=='undefined')
        {
          console.log('redict=true');
          window.location.replace(decoded_json.redirect);
        }
        if(typeof decoded_json.success!=='undefined')
        {
          console.log('success=true');
          document.getElementById('digisand_success').innerHTML=decoded_json.success;
          document.getElementById('digisand_success').style.display='block';

          setTimeout(function() //hide
          {
            document.getElementById('digisand_success').style.display='none';
          }, 5000);
        }
        if(typeof decoded_json.error!=='undefined')
        {
          console.log('error=true');
          document.getElementById('digisand_error').innerHTML=decoded_json.error;
          document.getElementById('digisand_error').style.display='block';

          setTimeout(function() //hide
          {
            document.getElementById('digisand_error').style.display='none';
          }, 8000);
        }
      }
    })
    .catch(error => 
    {
      console.error('Error:', error);
    })
  });

  function fill_devices_table(json_data) 
  {
    let stripDevices=json_data.devices.filter(device => device.device_type === 1);
    let digisandDevices=json_data.devices.filter(device => device.device_type === 2);

    function addRow(table, device) 
    {
      let newRow=document.createElement('tr');
      newRow.innerHTML= 
      `
        <td style="padding-right:0;"><input type="text" class="number_inp id_field" value="${device.device_id}" placeholder="ID"></td>
        <td>—</td>
        <td style="padding-left:3px;"><input type="text" class="number_inp name_field" value="${device.device_name}" placeholder="Device Name"></td>
        <td style="padding-right:5px;"><button class='square_main_button_red' onclick='delete_row_click(this)'>–</button></td>
      `;
      table.appendChild(newRow);
    }

    function create_and_fill_table(table, devices) 
    {
      if (!table) return;
      if (devices.length === 0) return;

      table.innerHTML=""; //clear existing rows
      devices.forEach(device => addRow(table, device));
    }

    create_and_fill_table(document.getElementById("strip_devices"), stripDevices);
    create_and_fill_table(document.getElementById("digisand_devices"), digisandDevices);
  }
  var row=null; //declare valiable globally

  function delete_row_click(button) 
  {
    row=button.closest('tr');

    if(document.getElementById('user_advanced').value==0)
    {
      document.getElementById('notification_delete_row').style.display='block';
      document.getElementById('opacity').style.display='block';
    }
    else 
    {
      if (row) 
      {
        row.remove();
        row=null;
      }
    }
  }

  function manage_devices_click()
  {
    let device_manager_tab=document.querySelectorAll('.tab')[1]; //device manager
    set_active_tool(device_manager_tab);
  }

  document.getElementById("cancel_delete_row").addEventListener('click', function () 
  {
    document.getElementById('notification_delete_row').style.display='none';
    document.getElementById('opacity').style.display='none';
    row=null;
  });

  document.getElementById("yes_delete_row").addEventListener('click', function () 
  {
    document.getElementById('notification_delete_row').style.display='none';
    document.getElementById('opacity').style.display='none';
    if (row) 
    {
      row.remove();
      row=null;
    }
  });

  document.getElementById("cancel_go_back").addEventListener('click', function () 
  {
    document.getElementById('notification_go_back').style.display='none';
    document.getElementById('opacity').style.display='none';
  });

  document.getElementById("yes_go_back").addEventListener('click', function () 
  {
    document.getElementById('notification_go_back').style.display='none';
    document.getElementById('opacity').style.display='none';

    let controls_tab=document.querySelectorAll('.tab')[0]; //controls
    console.log('go back');
    set_active_tool(controls_tab);
  });

  function back_to_controls() 
  {  
    if(document.getElementById('user_advanced').value==0)
    {
      document.getElementById('notification_go_back').style.display='block';
      document.getElementById('opacity').style.display='block';
    }
    else 
    {
      let controls_tab=document.querySelectorAll('.tab')[0]; //controls
      set_active_tool(controls_tab);
    }
  }


  function set_active_tool(element) 
  {
    document.querySelectorAll('.tab').forEach(tab => tab.classList.remove('active'));
    element.classList.add('active');

    selected_tab=element.textContent;
    console.log("Selected Tab:", selected_tab);

    document.getElementById("controls").style.display="none";
    document.getElementById("devices").style.display="none";

    if(selected_tab.toLocaleLowerCase()=="controls") document.getElementById("controls").style.display="block";
    else if(selected_tab.toLocaleLowerCase()=="device manager") document.getElementById("devices").style.display="block";

    //set proper width ->
    let width=window.innerWidth;
    if(selected_tab.toLocaleLowerCase()=="controls")
    {
      if(width>500) width=500;
      document.getElementById("main_div").style.width=width-25+"px";

      get_devices_primary();
    }
    else if(selected_tab.toLocaleLowerCase()=="device manager")
    {
      if(width>500) 
      {
        document.getElementById("main_div").style.width=100+"%";
      }
      else document.getElementById("main_div").style.width=width-25+"px";

      document.getElementById('devices_loading').style.display='block';

      var url='/personal.php';
      <? 
      if(isset($_SESSION['user_authorized_login'])) 
      {?>
        let user='<? echo $_SESSION['user_authorized_login']; ?>';
    <?}
      else
      {?>
        log_out();
    <?}
      ?>
      let send_build='get_devices=1&user_login='+user;
      console.log(send_build);

      fetch(url, 
      {
        method:'POST',
        headers:
        {
          'Content-Type':'application/x-www-form-urlencoded' //application/x-www-form-urlencoded
        },
        body:new URLSearchParams(send_build)
      })
      .then(response => response.text())
      .then(text => 
      {
        document.getElementById('devices_loading').style.display='none';
        console.log('sent');
        console.log(text);
        let json_data=JSON.parse(text);
        fill_devices_table(json_data);
      })
      .catch(error => 
      {
        console.error('Error:', error);
      })
    }
  }

  function add_field_digisand()
  {
    let table=document.getElementById('digisand_devices');
    let new_row=document.createElement('tr');
    
    new_row.innerHTML=
    `
      <td style="padding-right:0;"><input type="text" class="number_inp id_field" placeholder="ID"></td>
      <td>—</td>
      <td style="padding-left:3px;"><input type="text" class="number_inp name_field" placeholder="Device Name"></td>
      <td style="padding-right:5px;"><button class='square_main_button_red' onclick='delete_row_click(this)'>–</button></td>
    `;

    table.appendChild(new_row);
  }
</script>

<style>
  body 
  {
    font-family:-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
    /*background:linear-gradient(to bottom, #c7eaff, #ffd9a1);*/
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
    height:30px;
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

  .controls_flex
  {
    display:flex;
    flex-direction:row;
    gap:15px;
    align-items:stretch;
    justify-content:center;
    flex-wrap:wrap;
    width:100%;
    flex-grow:1;
  }
  #device_container, #mode_container 
  {
    flex-grow: 1;
    min-width: 270px;
  }
  #controls_container
  {
    flex-grow:2;
    flex-basis:100%;
  }

  @media (max-width:800px) 
  {
    .controls_flex 
    {
      flex-direction:column;
    }
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

  @media (max-width: 600px) 
  {
    .notification_container 
    {
      left: 15px;
      right: 15px;
      width: auto;
      max-width: calc(100% - 30px);
    }
  }



  .devices_table 
  {
    width:100%;
    border-collapse:collapse;
    margin:0;
    padding:0;
    table-layout: fixed;
    border-spacing:0;
  }

  .devices_table tr 
  {
    display:flex;
    align-items:center;
    gap:8px;
  }

  .devices_table td 
  {
    padding:5px 0px;
  }


  .devices_table td:nth-child(1) 
  { 
    flex-shrink:0;
  }

  .devices_table td:nth-child(2) 
  { 
    width:3%;
    text-align:left;
    margin:0;
    padding:0;
  }

  .devices_table td:nth-child(3) 
  { 
    flex:1;
  }

  .devices_table td:nth-child(4) 
  { 
    flex-shrink:0;
    width:auto;
  }

  .number_inp.id_field 
  {
    width:8ch; /* Exact width for 6 characters */
    min-width:8ch;
    max-width:8ch;
    flex-shrink:0;
    text-align:center;
    font-family:monospace;
    box-sizing:border-box;
    overflow:hidden;
    white-space:nowrap;
    margin-left:3px;
  }
  .number_inp.name_field 
  {
    width:100%;
    flex:1;
    min-width:120px;
    box-sizing:border-box;
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

  h1
  {
    display:inline-block;
    margin:0 auto;
    font-size:larger;
    font-weight:normal;
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

  

  .apply-button:hover
  {
    background-color:#005bb5;
  }

  .apply-button:focus
  {
    outline:none;
    background-color:#005bb5;
  }

</style>
</html>
