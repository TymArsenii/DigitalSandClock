void angle_pocessing()
{
  uint16_t prd=255-mpu.getMag();
  y_angle=constrain(prd, 0, 255);
  prd=constrain(prd, 15, 90);
  if(mpu.update(prd))
  {
    
    if(1==1) //1==2 for angle manually
    {
      if(ee_data.angle_auto && curr_action==1) {}
      else
      {
        int angle_tmp=mpu.getAngle()+45;
        if(angle_tmp>=0 || 1==1) angle=mpu.getAngle()+45;

        if (angle<0) angle+=360;
        if (angle>=360) angle-=360;

        angle+=180;
        if(angle>360) angle=angle-360;
      }
    }

    if(y_angle>=150)
    {
      if(sand_type=="water") rebuild_delay_time=10+10;
      else if(sand_type=="normal") rebuild_delay_time=500+300;
      else if(sand_type=="more_liquid") rebuild_delay_time=350+500;
      else if(sand_type=="more_thick") rebuild_delay_time=1100+500;
    }
    else
    {
      if(sand_type=="water") rebuild_delay_time=10;
      else if(sand_type=="normal") rebuild_delay_time=500;
      else if(sand_type=="more_liquid") rebuild_delay_time=350;
      else if(sand_type=="more_thick") rebuild_delay_time=1100;
    }

    
    if(Serial.available())
    {
      if(Serial.read()=='a')
      {
        Serial.print("angle: ");
        //if(view_log) Serial.println(prd);
        Serial.println(angle);
      }
    }
  }
}
