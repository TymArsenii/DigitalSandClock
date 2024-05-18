<!DOCTYPE html>
<html>
<head>
</head>

<style>
  body
  {
    font-family: arial, sans-serif;
  }
  #square
  {
    height: 300px;
    width: 300px;
    border-width:3px;
    border-color: black;
    border-style: solid;
    background-color: #FFF;
    rotate: 45deg;
    display: none;
  }
  table
  {
    rotate: 45deg;
    border-collapse: collapse;
    height: 300px;
    width: 300px;
  }
  td, th 
  {
    border: 2px solid #000;
  }

  span:hover
  {
    color:red;
  }
</style>

<body onload="clear_all()" style="margin-left: 80px; margin-top: 80px;">

  <div id="square">&nbsp;</div>
  <table id="table_id">
    <tr>
      <th style="border-color:red; border-bottom:#000;">&nbsp;</th>
      <th style="border-color:red; border-bottom:#000;">1</th>
      <th style="border-color:red; border-bottom:#000;">2</th>
      <th style="border-color:red; border-bottom:#000;">3</th>
      <th style="border-color:red; border-bottom:#000;">4</th>
      <th style="border-color:red; border-bottom:#000;">5</th>
      <th style="border-color:red; border-bottom:#000;">6</th>
      <th style="border-color:red; border-bottom:#000;">7</th>
      <th style="border-color:red; border-bottom:#000;">8</th>
    </tr>
    <tr>
      <th style="border-color:red; border-right:#000;">1</th>
      <th id="1;1">&nbsp;</th>
      <th id="2;1">&nbsp;</th>
      <th id="3;1">&nbsp;</th>
      <th id="4;1">&nbsp;</th>
      <th id="5;1">&nbsp;</th>
      <th id="6;1">&nbsp;</th> 
      <th id="7;1">&nbsp;</th>
      <th id="8;1">&nbsp;</th>
    </tr>
    <tr>  
      <th style="border-color:red; border-right:#000;">2</th>

      <th id="1;2">&nbsp;</th>
      <th id="2;2">&nbsp;</th>
      <th id="3;2">&nbsp;</th>
      <th id="4;2">&nbsp;</th>
      <th id="5;2">&nbsp;</th>
      <th id="6;2">&nbsp;</th>
      <th id="7;2">&nbsp;</th>
      <th id="8;2">&nbsp;</th>
    </tr>
    <tr>  
      <th style="border-color:red; border-right:#000;">3</th>

      <th id="1;3">&nbsp;</th>
      <th id="2;3">&nbsp;</th>
      <th id="3;3">&nbsp;</th>
      <th id="4;3">&nbsp;</th>
      <th id="5;3">&nbsp;</th>
      <th id="6;3">&nbsp;</th>
      <th id="7;3">&nbsp;</th>
      <th id="8;3">&nbsp;</th>
    </tr> 
    <tr>  
      <th style="border-color:red; border-right:#000;">4</th>

      <th id="1;4">&nbsp;</th>
      <th id="2;4">&nbsp;</th>
      <th id="3;4">&nbsp;</th>
      <th id="4;4">&nbsp;</th>
      <th id="5;4">&nbsp;</th>
      <th id="6;4">&nbsp;</th>
      <th id="7;4">&nbsp;</th>
      <th id="8;4">&nbsp;</th>
    </tr> 
    <tr>  
      <th style="border-color:red; border-right:#000;">5</th>

      <th id="1;5">&nbsp;</th>
      <th id="2;5">&nbsp;</th>
      <th id="3;5">&nbsp;</th>
      <th id="4;5">&nbsp;</th>
      <th id="5;5">&nbsp;</th>
      <th id="6;5">&nbsp;</th>
      <th id="7;5">&nbsp;</th>
      <th id="8;5">&nbsp;</th>
    </tr>
    <tr>  
      <th style="border-color:red; border-right:#000;">6</th>

      <th id="1;6">&nbsp;</th>
      <th id="2;6">&nbsp;</th>
      <th id="3;6">&nbsp;</th>
      <th id="4;6">&nbsp;</th>
      <th id="5;6">&nbsp;</th>
      <th id="6;6">&nbsp;</th>
      <th id="7;6">&nbsp;</th>
      <th id="8;6">&nbsp;</th>
    </tr> 
    <tr>  
      <th style="border-color:red; border-right:#000;">7</th>

      <th id="1;7">&nbsp;</th>
      <th id="2;7">&nbsp;</th>
      <th id="3;7">&nbsp;</th>
      <th id="4;7">&nbsp;</th>
      <th id="5;7">&nbsp;</th>
      <th id="6;7">&nbsp;</th>
      <th id="7;7">&nbsp;</th>
      <th id="8;7">&nbsp;</th>
    </tr> 
    <tr>  
      <th style="border-color:red; border-right:#000;">8</th>

      <th id="1;8">&nbsp;</th>
      <th id="2;8">&nbsp;</th>
      <th id="3;8">&nbsp;</th>
      <th id="4;8">&nbsp;</th>
      <th id="5;8">&nbsp;</th>
      <th id="6;8">&nbsp;</th>
      <th id="7;8">&nbsp;</th>
      <th id="8;8">&nbsp;</th>
    </tr>
  </table>

  <p id="pos" style="font-size: 50px; text-align: center;">-;-</p>

  <br>
  <input type="range" style="width: 400px; margin-top: 60px; margin-left:-25px !important;" id="inp" min="0" step="5" max="180" value="45" onchange="change_angle()">
  <p id="angle_print" style="font-size: 20px; display: inline-block; margin-left: 5px;">45deg</p>
  <br>
  <label>
    <span>Add</span>
    <input type="checkbox">
  </label>
  <label>
    <span>Remove</span>
    <input type="checkbox">
  </label>
  <br>
  <br>
  <button onclick="lightup_random_pixel_no_clear()">lightup multiple</button>
  <button onclick="lightup_random_pixel_clear()">lightup one</button>
  <button onclick="clear_all()">clear</button>
  <p id="save_angle" style="display:none;">0</p>
</body>
<script>
  let matrix_arr = // 1 - particle; 2 - obstacle; 0 - empty
  [
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
    [0, 0, 0, 0, 0, 0, 0, 0], 
  ];
  let id_build="";
  /* games
  setTimeout(plus_angle, 500);
  function plus_angle()
  {
    let angle_change;
    angle_change=document.getElementById("save_angle").textContent;
    console.log(angle_change);
    setTimeout(plus_angle, 500);
    angle_change++;
    angle_change++;
    angle_change++;
    angle_change++;
    angle_change++;
    if(angle_change>180)
    {
      angle_change=0;
    }
    angle_str=angle_change+'deg';
    document.getElementById("square").style.rotate=angle_str; 
    document.getElementById("table_id").style.rotate=angle_str; 
    document.getElementById("angle_print").innerHTML=angle_str;
    document.getElementById("save_angle").innerHTML=angle_change;
    document.getElementById("inp").value=angle_change;
  }
  */
  function change_angle()
  {
    let angle_str;
    let angle_inp;
    angle_inp=document.getElementById("inp").value;

    angle_str=angle_inp+'deg';
    document.getElementById("square").style.rotate=angle_str; 
    document.getElementById("table_id").style.rotate=angle_str; 
    document.getElementById("angle_print").innerHTML=angle_str;
    document.getElementById("save_angle").innerHTML=angle_inp;
  }
  function lightup_random_pixel_no_clear()
  {
    let rand_x, rand_y;
    rand_x=Math.floor(Math.random()*8)+1;
    rand_y=Math.floor(Math.random()*8)+1;
    if(matrix_arr[rand_x-1][rand_y-1]!=0)
    {
      for(;;)
      {
        if(matrix_arr[rand_x-1][rand_y-1]==0)
        {
          break;
        }
        else
        {
          rand_x=Math.floor(Math.random()*8)+1;
          rand_y=Math.floor(Math.random()*8)+1;
        }
      }
    }
    matrix_arr[rand_x-1][rand_y-1]=1;
    for(let x=1; x<=8; x++)
    {
      for(let y=1; y<=8; y++)
      {
        id_build="";
        id_build=x+";"+y;
        document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
      }
    }
    id_build=rand_x+";"+rand_y;
    document.getElementById(id_build).style.backgroundColor='red';

    document.getElementById("pos").innerHTML=id_build;
  }
  //setTimeout(lightup_random_pixel_clear, 300);
  function lightup_random_pixel_clear()
  {
    //setTimeout(lightup_random_pixel_clear, 300);
    for(let clr_x=1; clr_x<=8; clr_x++)
    {
      for(let clr_y=1; clr_y<=8; clr_y++)
      {
        matrix_arr[clr_x-1][clr_y-1]=0;
        id_build="";
        id_build=clr_x+";"+clr_y;
        document.getElementById(id_build).style.backgroundColor='white';
        document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
      }
    }
    
    let rand_x, rand_y;
    rand_x=Math.floor(Math.random()*8)+1;
    rand_y=Math.floor(Math.random()*8)+1;
    matrix_arr[rand_x-1][rand_y-1]=1;
    for(let x=1; x<=8; x++)
    {
      for(let y=1; y<=8; y++)
      {
        id_build="";
        id_build=x+";"+y;
        document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
      }
    }
    id_build="";
    id_build=rand_x+";"+rand_y;
    document.getElementById(id_build).style.backgroundColor='red';

    document.getElementById("pos").innerHTML=id_build;
  }

  function clear_all()
  {
    for(let clr_x=1; clr_x<=8; clr_x++)
    {
      for(let clr_y=1; clr_y<=8; clr_y++)
      {
        matrix_arr[clr_x-1][clr_y-1]=0;
        id_build="";
        id_build=clr_x+";"+clr_y;
        document.getElementById(id_build).style.backgroundColor='white';
        document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
      }
    }

    document.getElementById("pos").innerHTML="-;-";
  }
</script>
</html>
