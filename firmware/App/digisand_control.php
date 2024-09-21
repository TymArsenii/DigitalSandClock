<!DOCTYPE html>
<html xmlns="//www.w3.org/1999/xhtml">
<head>
	<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
	<meta name="viewport" content="width=device-width, initial-scale=1" />
  <meta charset="Shift_JIS">
	<title>DigiSand control</title>
	<link rel="Website Icon" type="png" href="hourglass.png">
</head>
<body onload="check_cookie()">
  <div class="back" style="height:30px;">
    <a style="text-align: left;" href="/">&nbsp; ←Menu</a>
    <button id="log_out" class="main_button" style="width:auto; padding: 3px; margin-left:50px; margin-bottom:0;">Log out</button>
    <p class="center-text">DigiSand control</p>
  </div>
  <div style="padding-bottom:30px;"></div>
<div>

<div id="main_div" style="width:50px;">
  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Timer &nbsp;&nbsp;&nbsp;</p>
    <input type="time" value="00:01" id="timer" style="scale:1.1; float:right;">
  </div>

  <div style="padding:10px; margin-bottom:15px; background-color:rgb(255, 255, 255, 0.6); border-radius: 15px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);">
    <p class="label_for_checkbox">Angle auto</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Angle auto</span>-->
        <input type="checkbox" id="ch_angle_auto" class="checkbox-custom">
        <span class="slider"></span>
      </label>
    </div>
    <br>
    <hr style="margin-left:0px; border: solid #b5b5b5 0.3px;">
    <p class="label_for_checkbox">Beep</p>
    <div style="margin-bottom:8px; display:inline; float:right;">
      <label class="apple-switch">
        <!--<span class="label_for_checkbox">Beep</span>-->
        <input type="checkbox" id="ch_beep" class="checkbox-custom">
        <span class="slider"></span>
      </label>
    </div>
  </div>

  <div class="slider-container">
    <div class="horizontal-slider">
      <label style="flex-direction: column !important; color:#007aff; font-size: 20px; font-weight:normal;">Brightness</label>
      <input type="range" id="brightness" style="width:100%;" min="0" max="16" step="1" style="display:inline-flex;" name="vertical-range" value="<?php echo $rows_ms['brightness']; ?>" orient="vertical">
    </div>
  </div>

  <button id="submit" class="main_button">Apply</button>
</div>

  <div class="footer">
    <a href="https://exch.com.ua/Bio.php" style="text-decoration: none; color: #007aff;">Arsenii’s Technologies</a>
  </div>
</div>
</body> 

<script>
  var user=get_cookie("device_id");

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

    //-----------------------------------------------------------------------------------------------

    let send_build;
    send_build='request=hey_you_give_me_the_data'+'&device_id='+user;
    //console.log(send_build);

    var url='digisand_control.php';
    fetch(url, 
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
      text = text.trim();

      let decoded_text_tmp;
      decoded_text_tmp=JSON.parse(text);

      // {"id":"1","device_id":"1","selected":"1","importance":"0","mode":"3","brightness":"255","hue":"84","sat":"255","smooth":"14","br1":"0","br2":"255","speed":"9","freq":"297"}

      let brightness=decoded_text_tmp.br;
      let timer=decoded_text_tmp.t;
      let angle_auto=decoded_text_tmp.a ? true : false;
      let beep=decoded_text_tmp.b;

      if(angle_auto==0) angle_auto=false;
      else if(angle_auto==1) angle_auto=true;

      if(beep==0) beep=false;
      else if(beep==1) beep=true;
      
      document.getElementById('brightness').value=brightness;
      document.getElementById('timer').value=timer;
      document.getElementById('ch_angle_auto').checked=angle_auto;
      document.getElementById('ch_beep').checked=beep;
    })
    .catch(error => 
    {
      //console.error('Error:', error);
    })
  });

  document.getElementById('submit').addEventListener('click', function() // apply
  {
    var url='digisand_control.php';

    let brightness=document.getElementById('brightness').value;
    let timer=document.getElementById('timer').value;
    let angle_auto=document.getElementById('ch_angle_auto').checked;
    let beep=document.getElementById('ch_beep').checked;

    timer=timer.split(':').slice(0, 2).join(':');

    if(angle_auto) angle_auto=1;
    else if(!angle_auto) angle_auto=0;
    if(beep) beep=1;
    else if(!beep) beep=0;

    let send_build;
    send_build='apply=123'+'&device_id='+user+'&brightness='+brightness+'&timer='+timer+'&angle_auto='+angle_auto+'&beep='+beep;
    console.log(send_build);

    fetch(url, 
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
    let expires = "expires=" + d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
  }

  function get_cookie(cname) 
  {
    let name = cname+"=";
    let decodedCookie = decodeURIComponent(document.cookie);
    let ca = decodedCookie.split(';');
    for(let i = 0; i < ca.length; i++) 
    {
      let c = ca[i];
      while (c.charAt(0) == ' ')
      {
        c = c.substring(1);
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
