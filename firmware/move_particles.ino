void move_particles()
{
  // ============================================================== drop timers ==============================================================>
  

  // loop_timer:
  /*
  water=13ms;
  normal=140ms;
  more_thick=300ms;
  more_liquid=100ms;
  */
/*
  float time_addend;
  

  if(sand_type=="water") time_addend=(13*61)/1000;
  else if(sand_type=="normal") time_addend=4;
  else if(sand_type=="more_liquid") time_addend=(100*61)/1000;
  else if(sand_type=="more_thick") time_addend=((300*61)-9000)/1000;
  
  //time_addend+=1;
  //Serial.println(time_addend);

  float drop_timer_value=(float)(((minute*60)+second-time_addend)*1000/61);
  Serial.println(drop_timer_value);
*/
  if(!allow_drop)
  {
    if(angle>=180 && angle<=360)
    {
      //Serial.println(matrix_arr[8-1][8-1]);
      if(matrix_arr[8-1][8-1]==0) matrix_arr[8-1][8-1]=2;
    }
    if(angle>=0 && angle<180)
    {
      if(matrix_arr[9-1][9-1]==0) matrix_arr[9-1][9-1]=2;
    }
  }

  // <============================================================== drop timers ==============================================================


  // ============================================================== moving!!! that WORKS!!! ==============================================================>
  if(angle>=0 && angle<=90) //WORKS!
  {
    if(matrix_arr[8-1][1-1]==1) forse_lightup[1]=true;
    else forse_lightup[1]=false;

    if(matrix_arr[8-1][3-1]==1) forse_lightup[2]=true;
    else forse_lightup[2]=false;

    if(matrix_arr[8-1][5-1]==1) forse_lightup[3]=true;
    else forse_lightup[3]=false;

    if(matrix_arr[8-1][7-1]==1) forse_lightup[4]=true;
    else forse_lightup[4]=false;

    for(uint8_t x=1; x<=matrix_width; x++)
    {
      for(uint8_t y=1; y<=matrix_height; y++)
      {
        delayMicroseconds(rebuild_delay_time);
        move_timer=micros();
        if(matrix_arr[x-1][y-1]==1)
        {
          matrix_arr[x-1][y-1]=0;
  
          if(angle<=45)
          {
            bool diagonal=false;
            if(angle<23) diagonal=false;
            else diagonal=true;
            if (x<matrix_width && y<matrix_height && matrix_arr[x][y]==0)
            {
              matrix_arr[x][y]=1;
              matrix_arr[x-1][y-1]=0;

              redraw(1);
            }
            else if(y<matrix_height && matrix_arr[x-1][y]==0)
            {
              matrix_arr[x-1][y]=1;
              matrix_arr[x-1][y-1]=0;    
            }
            else if(x<matrix_width && matrix_arr[x][y-1]==0)
            {
              matrix_arr[x][y-1]=1;
              matrix_arr[x-1][y-1]=0;
            }
            else
            {
              matrix_arr[x-1][y-1]=1;
            }
  
            if(angle>23)
            {
              if(x<matrix_width && y<=matrix_height && y>1 && matrix_arr[x][y-2]==0 && matrix_arr[x-1][y-1]==1) // +x -y
              {
                matrix_arr[x][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
              if(x<=matrix_width && y<matrix_height && x>1 && matrix_arr[x-2][y]==0 && matrix_arr[x-1][y-1]==1) // -x +y
              {
                matrix_arr[x-2][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            else if(angle<=23)
            {
              if(x>1 && matrix_arr[x-2][y-1]==0 && matrix_arr[x-1][y-1]==1)
              {
                matrix_arr[x-2][y-1]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
          } //if(angle<=45)
          else if(angle>45 && angle<=90)
          {
            angle=90-angle;
  
            if (x<matrix_width && y<matrix_height && matrix_arr[x][y]==0)
            {
              matrix_arr[x][y]=1;
              matrix_arr[x-1][y-1]=0;

              redraw(1);
            }
            else if(x<matrix_width && matrix_arr[x][y-1]==0)
            {
              matrix_arr[x][y-1]=1;
              matrix_arr[x-1][y-1]=0;
            }
            else if(y<matrix_height && matrix_arr[x-1][y]==0)
            {
              matrix_arr[x-1][y]=1;
              matrix_arr[x-1][y-1]=0;
            }
            else
            {
              matrix_arr[x-1][y-1]=1;
            }
            
  
            if(angle>23)
            {
              
              if(x<matrix_width && y<=matrix_height && y>1 && matrix_arr[x][y-2]==0 && matrix_arr[x-1][y-1]==1) // +x -y
              {
                matrix_arr[x][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
              if(x<=matrix_width && y<matrix_height && x>1 && matrix_arr[x-2][y]==0 && matrix_arr[x-1][y-1]==1) // -x +y
              {
                matrix_arr[x-2][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            else if(angle<=23)
            {
              if(y>1 && matrix_arr[x-1][y-2]==0 && matrix_arr[x-1][y-1]==1)
              {
                matrix_arr[x-1][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
  
            angle=90-angle;
          } //else if(angle>45 && angle<=90)
        } //if(matrix_arr[x-1][y-1]==1)
        
      } //for(uint8_t y=1; y<=matrix_height; y++)
    } //for(uint8_t x=1; x<=matrix_width; x++)
  } //if(angle>=0 && angle<=90)
  else if(angle>90 && angle<=180) //WORKS!
  {
    for(uint8_t y=matrix_height; y>=1; y--)
    {
      for(uint8_t x=1; x<=matrix_width; x++)
      {
        delayMicroseconds(rebuild_delay_time);
        move_timer=micros();
        if(matrix_arr[x-1][y-1]==1)
        {
          matrix_arr[x-1][y-1]=0;
          if (x<matrix_width && y>1 && matrix_arr[x][y-2]==0) //diagonal
          {
            matrix_arr[x][y-2]=1;
            matrix_arr[x-1][y-1]=0;

            redraw();
          }
          else if(x<matrix_width && matrix_arr[x][y-1]==0) //down
          {
            matrix_arr[x][y-1]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else if(y>1 && matrix_arr[x-1][y-2]==0) //right
          {
            matrix_arr[x-1][y-2]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else
          {
            matrix_arr[x-1][y-1]=1;
          }

          
          int mid_angle=145;
          int max_angle=180;
          int min_angle=90; 

          static uint8_t last_elements_id=0;
          if(angle<=mid_angle)
          {
            angle=angle-min_angle;
            if(angle>23)
            {
              
              if(x>1 && y>1 && matrix_arr[x-2][y-2]==0 && matrix_arr[x-1][y-1]==1) //right
              {
                matrix_arr[x-2][y-2]=1;
                matrix_arr[x-1][y-1]=0;

                //last_positions_arr[last_elements_id][0]=x-1;
                //last_positions_arr[last_elements_id][1]=y-1;
                //if(last_elements_id<16) last_elements_id++;

                //Serial.print(x);
                //Serial.print(';');
                //Serial.print(y);
                //Serial.print(" -> ");
                //Serial.print(x-1);
                //Serial.print(';');
                //Serial.print(y-1);
              }
              if(x<matrix_width && y<matrix_height && matrix_arr[x][y]==0 && matrix_arr[x-1][y-1]==1) //left
              {
                matrix_arr[x][y]=1;
                matrix_arr[x-1][y-1]=0;

                //last_positions_arr[last_elements_id][0]=x-1;
                //last_positions_arr[last_elements_id][1]=y-1;
                //if(last_elements_id<16) last_elements_id++;

                //Serial.print("   ");
                //Serial.print(x);
                //Serial.print(';');
                //Serial.print(y);
                //Serial.print(" -> ");
                //Serial.print(x+1);
                //Serial.print(';');
                //Serial.print(y+1);
              }
            }
            else if(angle<=23)
            {
              if(y<matrix_height && matrix_arr[x-1][y]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x-1][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=angle+min_angle;
          }
          else if(angle>mid_angle)
          {
            angle=max_angle-angle;
            if(angle<=23)
            {
              if(x>1 && matrix_arr[x-2][y-1]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x-2][y-1]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=max_angle-angle;
          }
        } //if(matrix_arr[x-1][y-1]==1)
      } //for
    } //for
    for(int y=1; y<=2; y++)
    {
      for(int x=1; x<=16; x++)
      {
        //Serial.print(last_positions_arr[y-1][x-1]);
        //Serial.print(" ");
      }
      //Serial.println();
    }
  } //else if(angle>270 && angle<=360) 
  else if(angle>180 && angle<=270) //WORKS!
  {
    if(matrix_arr[9-1][10-1]==1) forse_lightup[1]=true;
    else forse_lightup[1]=false;

    if(matrix_arr[9-1][12-1]==1) forse_lightup[2]=true;
    else forse_lightup[2]=false;

    if(matrix_arr[9-1][14-1]==1) forse_lightup[3]=true;
    else forse_lightup[3]=false;

    if(matrix_arr[9-1][16-1]==1) forse_lightup[4]=true;
    else forse_lightup[4]=false;

    for(uint8_t x=matrix_width; x>=1; x--)
    {
      for(uint8_t y=matrix_height; y>=1; y--)
      {
        delayMicroseconds(rebuild_delay_time);
        move_timer=micros();
        if(matrix_arr[x-1][y-1]==1)
        {
          matrix_arr[x-1][y-1]=0;
          if (x>1 && y>1 && matrix_arr[x-2][y-2]==0) //diagonal
          {
            matrix_arr[x-2][y-2]=1;
            matrix_arr[x-1][y-1]=0;

            redraw(2);
          }
          else if(x>1 && matrix_arr[x-2][y-1]==0) //right
          {
            matrix_arr[x-2][y-1]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else if(y>1 && matrix_arr[x-1][y-2]==0) //down
          {
            matrix_arr[x-1][y-2]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else
          {
            matrix_arr[x-1][y-1]=1;
          }


          int mid_angle=225;
          int max_angle=270;
          int min_angle=180;
          if(angle<=mid_angle+22)
          {
            angle=angle-min_angle;
            if(angle>23)
            {
              if(x>1 && y<matrix_height && matrix_arr[x-2][y]==0 && matrix_arr[x-1][y-1]==1) //right
              {
                matrix_arr[x-2][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
              if(x<matrix_width && y>1 && matrix_arr[x][y-2]==0 && matrix_arr[x-1][y-1]==1) //left
              {
                matrix_arr[x][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            else if(angle<=23)
            {
              if(x<matrix_width && matrix_arr[x][y-1]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x][y-1]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=angle+min_angle;
          }
          else if(angle>mid_angle)
          {
            angle=max_angle-angle;
            if(angle<=23)
            {
              if(y<matrix_height && matrix_arr[x-1][y]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x-1][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=max_angle-angle;
          }
        } //if(matrix_arr[x-1][y-1]==1)
        
      } //for
    } //for
  } //else if(angle>180 && angle<=270)
  else if(angle>270 && angle<=360) //WORKS!
  {
    for(uint8_t y=1; y<=matrix_height; y++)
    {
      for(uint8_t x=matrix_width; x>=1; x--)
      {
        delayMicroseconds(rebuild_delay_time);
        move_timer=micros();
        if(matrix_arr[x-1][y-1]==1)
        {
          matrix_arr[x-1][y-1]=0;
          if (x>1 && y<matrix_height && matrix_arr[x-2][y]==0) //diagonal
          {
            matrix_arr[x-2][y]=1;
            matrix_arr[x-1][y-1]=0;

            redraw();
          }
          else if(y<matrix_height && matrix_arr[x-1][y]==0) //right
          {
            matrix_arr[x-1][y]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else if(x>1 && matrix_arr[x-2][y-1]==0) //down
          {
            matrix_arr[x-2][y-1]=1;
            matrix_arr[x-1][y-1]=0;
          }
          else
          {
            matrix_arr[x-1][y-1]=1;
          }


          int mid_angle=315;
          int max_angle=360;
          int min_angle=270;         
          if(angle<=mid_angle+22)
          {
            angle=angle-min_angle;
            if(angle>23)
            {
              if(x<matrix_width && y<matrix_height && matrix_arr[x][y]==0 && matrix_arr[x-1][y-1]==1) //right
              {
                matrix_arr[x][y]=1;
                matrix_arr[x-1][y-1]=0;
              }
              if(x>1 && y>1 && matrix_arr[x-2][y-2]==0 && matrix_arr[x-1][y-1]==1) //left
              {
                matrix_arr[x-2][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            else if(angle<=23)
            {
              if(y>1 && matrix_arr[x-1][y-2]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x-1][y-2]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=angle+min_angle;
          }
          else if(angle>mid_angle)
          {
            angle=max_angle-angle;
            if(angle<=23)
            {
              if(x<matrix_width && matrix_arr[x][y-1]==0 && matrix_arr[x-1][y-1]==1) //down
              {
                matrix_arr[x][y-1]=1;
                matrix_arr[x-1][y-1]=0;
              }
            }
            angle=max_angle-angle;
          }
        } //if(matrix_arr[x-1][y-1]==1)
        
      } //for
    } //for
  } //else if(angle>90 && angle<=180)
  // <============================================================== moving!!! that WORKS!!! ==============================================================

  allow_drop=false;
}
