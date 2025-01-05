void stand_clock_mode()
{
  time_client.update();

  if((angle>=180 && angle<=270) || (angle>=115 && angle<=155))
  {
    print_num(time_client.getHours(), 2);
    print_num(time_client.getMinutes(), 1);
  }
  else
  {
    print_num(time_client.getHours(), 1);
    print_num(time_client.getMinutes(), 2);
  }
  
  if(Serial.available())
  {
    if(Serial.read()=='t')
    {
      Serial.print("time: ");
      //if(view_log) Serial.println(prd);
      Serial.println(time_client.getFormattedTime());
    }
  }
}