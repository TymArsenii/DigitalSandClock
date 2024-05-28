/*let matrix_arr = // 1 - particle; 2 - obstacle; 0 - empty
[
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
  [2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0], 
];*/

let matrix_arr = // 1 - particle; 2 - obstacle; 0 - empty
[
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
];
const matrix_width=16;
const matrix_height=16;
var id_build="";
var add_state, remove_state;

function draw_line(array, x0, y0, x1, y1) // Bresenham's algorithm
{
  let dx=Math.abs(x1-x0);
  let dy=-Math.abs(y1-y0);
  let sx=x0<x1?1:-1;
  let sy=y0<y1?1:-1;
  let err=dx+dy;
  let e2;

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      id_build=x+";"+y;
      if(document.getElementById(id_build).style.backgroundColor=='yellow')
      {
        document.getElementById(id_build).style.backgroundColor='white';
      }
    }
  }

  while(true) 
  {
    if(x0>=1 && y0>=1 && x0<=matrix_width && y0<=matrix_height && array[x0-1][y0-1]!=2) 
    {
      id_build=x0+";"+y0;
      //array[x0-1][y0-1]=3;
      document.getElementById(id_build).style.backgroundColor='yellow';
    }
    if(x0>=1 && y0>=1 && x0<=matrix_width && y0<=matrix_height && array[x0-1][y0-1]==1) return "stop!";
    
    if (x0===x1 && y0===y1) break;

    e2=2*err;
    if (e2>=dy) 
    {
      err+=dy;
      x0+=sx;
    }
    if (e2<=dx) 
    {
      err+=dx;
      y0+=sy;
    }
  }
}

function turn_off_text_processing() 
{
  let input=document.getElementById("turn_off_text").value;
  document.getElementById("turn_off_text").value="";
  
  const pairs = input.split(' ');
  const coordinates = pairs.map(pair => 
  {
      const [x, y] = pair.split(';').map(Number);
      return { x, y };
  });
  //console.log(coordinates);
  const x_values = coordinates.map(coordinate => coordinate.x);
  const y_values = coordinates.map(coordinate => coordinate.y);

  for(let x=0; x<x_values.length; x++)
  {
    if(matrix_arr[x_values[x]-1][y_values[x]-1]==0) 
    {
      matrix_arr[x_values[x]-1][y_values[x]-1]=0;

      id_build=x_values[x]+";"+y_values[x];
      document.getElementById(id_build).style.backgroundColor='white';
    }
  }

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      id_build="";
      id_build=x+";"+y;
      document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
    }
  }
}
function lightup_text_processing() 
{
  let input=document.getElementById("lightup_text").value;
  document.getElementById("lightup_text").value="";
  
  const pairs = input.split(' ');
  const coordinates = pairs.map(pair => 
  {
      const [x, y] = pair.split(';').map(Number);
      return { x, y };
  });
  //console.log(coordinates);
  const x_values = coordinates.map(coordinate => coordinate.x);
  const y_values = coordinates.map(coordinate => coordinate.y);

  console.log(x_values);
  console.log(y_values);

  for(let x=0; x<x_values.length; x++)
  {
    if(matrix_arr[x_values[x]-1][y_values[x]-1]==0) 
    {
      matrix_arr[x_values[x]-1][y_values[x]-1]=1;

      id_build=x_values[x]+";"+y_values[x];
      document.getElementById(id_build).style.backgroundColor='#b3b3b3';
    }
  }

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      id_build="";
      id_build=x+";"+y;
      document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
    }
  }
}
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

setTimeout(auto_add_remove, 20);
function auto_add_remove()
{
  setTimeout(auto_add_remove, 20);
  add_state=document.getElementById("add_ch").checked;
  remove_state=document.getElementById("remove_ch").checked;

  if(add_state) lightup_specific_pixel_no_clear();
  if(remove_state) remove_specific();
}

let rebuild_timeout=setTimeout(auto_rebuild, 100);
function auto_rebuild()
{
  let rebuildup_checkbox_check;
  rebuildup_checkbox_check=document.getElementById("rebuildup_ch").checked;
  if(rebuildup_checkbox_check) 
  {
    move_particles(1);
    line_height_adjust();
  }

  let rebuilddown_checkbox_check;
  rebuilddown_checkbox_check=document.getElementById("rebuilddown_ch").checked;
  if(rebuilddown_checkbox_check) 
  {
    move_particles(2);
    line_height_adjust();
  }

  clearTimeout(rebuild_timeout);
  rebuild_timeout=setTimeout(auto_rebuild, 100);
}

let main_timeout=setTimeout(move_particles, 1);
function move_particles(button=0)
{
  clearTimeout(main_timeout);
  main_timeout=setTimeout(move_particles, 1);
  let angle_inp;
  angle_inp=document.getElementById("inp").value;
  add_state=document.getElementById("add_ch").checked;
  remove_state=document.getElementById("remove_ch").checked;
  let rebuild_button_state=0;
  if(button==1) rebuild_button_state=1;
  else if(button==2) rebuild_button_state=2;

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
    {
      if(matrix_arr[x-1][y-1]==1)
      {
        let angle_map;
        matrix_arr[x-1][y-1]=0;

        if(angle_inp>45) angle_map=90-angle_inp;
        else angle_map=angle_inp;
        
        let percent_chance=map(angle_map, 0, 45, 0, 100)/100;
        console.log(angle_inp)
        if(angle_inp<=45)
        {
          if (Math.random()<percent_chance && x<matrix_width && y<matrix_height && matrix_arr[x][y]==0)
          {
            matrix_arr[x][y]=1;
            id_build=(x+1)+";"+(y+1);
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';

            matrix_arr[x-1][y-1]=0;
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';

          }
          else if(y<matrix_height && matrix_arr[x-1][y]==0)
          {
            matrix_arr[x-1][y]=1;
            id_build=x+";"+(y+1);
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            
            matrix_arr[x-1][y-1]=0;
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
          }
          else if(x<matrix_width && matrix_arr[x][y-1]==0)
          {
            matrix_arr[x][y-1]=1;
            id_build=(x+1)+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            
            matrix_arr[x-1][y-1]=0;
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
          }
          else
          {
            matrix_arr[x-1][y-1]=1;
            id_build=x+";"+y;
            document.getElementById(id_build).style.backgroundColor='red';
          }

          if(angle_inp>23)
          {
            if(rebuild_button_state==1 && x<matrix_width && y<=matrix_height && y>1 && matrix_arr[x][y-2]==0 && matrix_arr[x-1][y-1]==1) // +x -y
            {
              matrix_arr[x][y-2]=1;
              id_build=(x+1)+";"+(y-1);
              //document.getElementById(id_build).style.backgroundColor='#575757';
              
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#4e57d9';
              console.log("rebuild up");
            }
            else if(rebuild_button_state==2 && x<=matrix_width && y<matrix_height && x>1 && matrix_arr[x-2][y]==0 && matrix_arr[x-1][y-1]==1) // -x +y
            {
              matrix_arr[x-2][y]=1;
              id_build=(x-1)+";"+(y+1);
              console.log(id_build);
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              console.log("rebuild down");
            }
          }
          else if(angle_inp<=23)
          {
            if(rebuild_button_state==2 && x>1 && matrix_arr[x-2][y-1]==0 && matrix_arr[x-1][y-1]==1)
            {
              matrix_arr[x-2][y-1]=1;
              id_build=(x-1)+";"+(y);
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
  
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              console.log("rebuild down <=23 45");
            }
          }
        }
        else if(angle_inp>45)
        {
          angle_inp=90-angle_inp;

          if (Math.random()<percent_chance && x<matrix_width && y<matrix_height && matrix_arr[x][y]==0)
          {
            matrix_arr[x][y]=1;
            id_build=(x+1)+";"+(y+1);
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            
            matrix_arr[x-1][y-1]=0;
          }
          else if(x<matrix_width && matrix_arr[x][y-1]==0)
          {
            matrix_arr[x][y-1]=1;
            id_build=(x+1)+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            
            matrix_arr[x-1][y-1]=0;
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
          }
          else if(y<matrix_height && matrix_arr[x-1][y]==0)
          {
            matrix_arr[x-1][y]=1;
            id_build=x+";"+(y+1);
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
            
            matrix_arr[x-1][y-1]=0;
            id_build=x+";"+y;
            //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
          }
          else
          {
            matrix_arr[x-1][y-1]=1;
            id_build=x+";"+y;
            document.getElementById(id_build).style.backgroundColor='red';
          }
          line_height_adjust();

          if(angle_inp>23)
          {
            if(rebuild_button_state==1 && x<matrix_width && y<=matrix_height && y>1 && matrix_arr[x][y-2]==0 && matrix_arr[x-1][y-1]==1) // +x -y
            {
              matrix_arr[x][y-2]=1;
              id_build=(x+1)+";"+(y-1);
              //document.getElementById(id_build).style.backgroundColor='#575757';
              
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#4e57d9';
              console.log("rebuild up");
            }
            else if(rebuild_button_state==2 && x<=matrix_width && y<matrix_height && x>1 && matrix_arr[x-2][y]==0 && matrix_arr[x-1][y-1]==1) // -x +y
            {
              matrix_arr[x-2][y]=1;
              id_build=(x-1)+";"+(y+1);
              console.log(id_build);
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              console.log("rebuild down");
            }
          }
          else if(angle_inp<=23)
          {
            if(rebuild_button_state==2 && y>1 && matrix_arr[x-1][y-2]==0 && matrix_arr[x-1][y-1]==1)
            {
              matrix_arr[x-1][y-2]=1;
              id_build=(x)+";"+(y-1);
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
  
              matrix_arr[x-1][y-1]=0;
              id_build=x+";"+y;
              //document.getElementById(id_build).style.backgroundColor='#b3b3b3';
              console.log("rebuild down <=23");
            }
          }

          angle_inp=90-angle_inp;
        }
      }
    }
  }

  document.getElementById("pos").innerHTML=id_build;

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      id_build="";
      id_build=x+";"+y;
      document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
      if(matrix_arr[x-1][y-1]==0 && document.getElementById(id_build).style.backgroundColor!='yellow')
      {
        document.getElementById(id_build).style.backgroundColor='white';
      }
      else if(matrix_arr[x-1][y-1]==1)
      {
        document.getElementById(id_build).style.backgroundColor='red';
      }
      else if(matrix_arr[x-1][y-1]==2)
      {
        document.getElementById(id_build).style.backgroundColor='green';
      }
      /*
      else if(matrix_arr[x-1][y-1]==3)
      {
        document.getElementById(id_build).style.backgroundColor='yellow';
        matrix_arr[x-1][y-1]=0;
      }
      */
    }
  }
  delete id_build;
}

function line_height_adjust()
{
  let draw_line_feedback;
  let line_height=-15;
  angle_inp=document.getElementById("inp").value; 
  while(true)
  {
    if(angle_inp<=45)
    {
      let a_y_tmp=(Math.round(map(angle_inp, 0, 45, 8, 1)))+line_height;
      let b_y_tmp=(Math.round(map(angle_inp, 0, 45, 8, 16)))+line_height;
      let a_x_tmp=(Math.round(map(angle_inp, 0, 45, 16, 16)));
      let b_x_tmp=(Math.round(map(angle_inp, 0, 45, 1, 1)));

      draw_line_feedback=draw_line(matrix_arr, a_x_tmp, a_y_tmp, b_x_tmp, b_y_tmp);
    }
    else if(angle_inp>45)
    {
      let a_y_tmp=(Math.round(map(angle_inp, 46, 90, 16, 16)));
      let b_y_tmp=(Math.round(map(angle_inp, 46, 90, 1, 1)));
      let a_x_tmp=(Math.round(map(angle_inp, 46, 90, 1, 8)));
      let b_x_tmp=(Math.round(map(angle_inp, 46, 90, 16, 8)));
      a_x_tmp+=line_height;
      b_x_tmp+=line_height;

      
      draw_line_feedback=draw_line(matrix_arr, a_x_tmp, a_y_tmp, b_x_tmp, b_y_tmp);
    }
    if(draw_line_feedback=="stop!" || line_height>50)
    {
      if(draw_line_feedback=="stop!")
      {
        line_height--;
        if(angle_inp<=45)
        {
          let a_y_tmp=(Math.round(map(angle_inp, 0, 45, 8, 1)))+line_height;
          let b_y_tmp=(Math.round(map(angle_inp, 0, 45, 8, 16)))+line_height;
          let a_x_tmp=(Math.round(map(angle_inp, 0, 45, 16, 16)));
          let b_x_tmp=(Math.round(map(angle_inp, 0, 45, 1, 1)));
    
          draw_line_feedback=draw_line(matrix_arr, a_x_tmp, a_y_tmp, b_x_tmp, b_y_tmp);
        }
        else if(angle_inp>45)
        {
          let a_y_tmp=(Math.round(map(angle_inp, 46, 90, 16, 16)));
          let b_y_tmp=(Math.round(map(angle_inp, 46, 90, 1, 1)));
          let a_x_tmp=(Math.round(map(angle_inp, 46, 90, 1, 8)))+line_height;
          let b_x_tmp=(Math.round(map(angle_inp, 46, 90, 16, 8)))+line_height;
          
          draw_line_feedback=draw_line(matrix_arr, a_x_tmp, a_y_tmp, b_x_tmp, b_y_tmp);
        }
        //change_angle();
      }
      break;
    }
    line_height++;
  }
} 
function map(x, in_min, in_max, out_min, out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
function constrain(x, min_val, max_val)
{
  if(x>=min_val && x<=max_val) {;}
  else if(x<min_val) {x=min_val;}
  else if(x>max_val) {x=max_val;}

  return x;
}
function change_angle()
{
  let angle_str;
  let angle_inp;
  let height_inp=0;

  angle_inp=document.getElementById("inp").value; 
  height_inp=Number(document.getElementById("inp_height").value)-13;
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      if(matrix_arr[x-1][y-1]==3)
      {
        matrix_arr[x-1][y-1]=0;
      }
    }
  }
  
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
    {
      id_build="";
      id_build=x+";"+y;
      document.getElementById(id_build).innerHTML=matrix_arr[x-1][y-1];
      if(matrix_arr[x-1][y-1]==0)
      {
        document.getElementById(id_build).style.backgroundColor='white';
      }
      else if(matrix_arr[x-1][y-1]==1)
      {
        document.getElementById(id_build).style.backgroundColor='red';
      }
      else if(matrix_arr[x-1][y-1]==2)
      {
        document.getElementById(id_build).style.backgroundColor='green';
      }
      /*
      else if(matrix_arr[x-1][y-1]==3)
      {
        document.getElementById(id_build).style.backgroundColor='yellow';
        matrix_arr[x-1][y-1]=0;
      }
      */
    }
  }

  angle_str=angle_inp+'deg';
  document.getElementById("square").style.rotate=angle_str; 
  document.getElementById("table_id").style.rotate=angle_str; 
  document.getElementById("angle_print").innerHTML=angle_str;
  document.getElementById("save_angle").innerHTML=angle_inp;
}
function lightup_random_pixel_no_clear()
{
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
    {
      id_build=x+";"+y;
      let b_color=document.getElementById(id_build).style.backgroundColor;
      if(document.getElementById(id_build).style.backgroundColor=='rgb(179, 179, 179)')
      {
        document.getElementById(id_build).style.backgroundColor='white';
      }
    }
  }
  let rand_x=1, rand_y=1;
  let is_empty_exist;
  is_empty_exist=false;
  rand_x=Math.floor(Math.random()*matrix_width)+1;
  rand_y=Math.floor(Math.random()*matrix_height)+1;
  if(matrix_arr[rand_x-1][rand_y-1]!=0)
  {
    for(let x=1; x<=matrix_width; x++)
    {
      for(let y=1; y<=matrix_height; y++)
      {
        if(matrix_arr[x-1][y-1]==0)
        {
          is_empty_exist=true;
          break;
        }
      }
    }
    
    if(is_empty_exist==true)
    {
      for(;;)
      {
        if(matrix_arr[rand_x-1][rand_y-1]==0)
        {
          break;
        }
        else
        {
          rand_x=Math.floor(Math.random()*matrix_width)+1;
          rand_y=Math.floor(Math.random()*matrix_height)+1;
        }
      }
    }
    else
    {
      rand_x=2;
      rand_y=2;
    }
  }
  matrix_arr[rand_x-1][rand_y-1]=1;

  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_width; y++)
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
  for(let clr_x=1; clr_x<=matrix_width; clr_x++)
  {
    for(let clr_y=1; clr_y<=matrix_height; clr_y++)
    {
      matrix_arr[clr_x-1][clr_y-1]=0;
      id_build="";
      id_build=clr_x+";"+clr_y;
      document.getElementById(id_build).style.backgroundColor='white';
      document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
    }
  }
  
  let rand_x, rand_y;
  rand_x=Math.floor(Math.random()*matrix_width)+1;
  rand_y=Math.floor(Math.random()*matrix_height)+1;
  matrix_arr[rand_x-1][rand_y-1]=1;
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
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
function lightup_specific_pixel_clear()
{
  //setTimeout(lightup_random_pixel_clear, 300);
  for(let clr_x=1; clr_x<=matrix_width; clr_x++)
  {
    for(let clr_y=1; clr_y<=matrix_height; clr_y++)
    {
      matrix_arr[clr_x-1][clr_y-1]=0;
      id_build="";
      id_build=clr_x+";"+clr_y;
      document.getElementById(id_build).style.backgroundColor='white';
      document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
    }
  }
  
  let rand_x, rand_y;
  rand_x=1;
  rand_y=1;
  matrix_arr[rand_x-1][rand_y-1]=1;
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
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

function lightup_specific_pixel_no_clear()
{
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
    {
      id_build=x+";"+y;
      let b_color=document.getElementById(id_build).style.backgroundColor;
      if(document.getElementById(id_build).style.backgroundColor=='rgb(179, 179, 179)')
      {
        document.getElementById(id_build).style.backgroundColor='white';
      }
    }
  }
  //setTimeout(lightup_random_pixel_clear, 300);
  let rand_x, rand_y;
  rand_x=1;
  rand_y=1;
  matrix_arr[rand_x-1][rand_y-1]=1;
  for(let x=1; x<=matrix_width; x++)
  {
    for(let y=1; y<=matrix_height; y++)
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

function remove_specific()
{
  matrix_arr[matrix_width-1][matrix_height-1]=0;
  id_build=matrix_width+';'+matrix_height;
  document.getElementById(id_build).style.backgroundColor='white';
  document.getElementById(id_build).innerHTML=matrix_arr[matrix_width-1][matrix_height-1];
}

function clear_all()
{
  for(let clr_x=1; clr_x<=matrix_width; clr_x++)
  {
    for(let clr_y=1; clr_y<=matrix_height; clr_y++)
    {
      if(matrix_arr[clr_x-1][clr_y-1]!=2)
      {
        matrix_arr[clr_x-1][clr_y-1]=0;
        id_build="";
        id_build=clr_x+";"+clr_y;
        document.getElementById(id_build).style.backgroundColor='white';
        document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
      }
      else
      {
        id_build="";
        id_build=clr_x+";"+clr_y;
        
        document.getElementById(id_build).style.backgroundColor='green';
        document.getElementById(id_build).style.color='black';
        document.getElementById(id_build).innerHTML=matrix_arr[clr_x-1][clr_y-1];
      }
    }
  }

  document.getElementById("pos").innerHTML="-;-";
  change_angle();
}
