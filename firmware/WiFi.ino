void wifi_stuff()
{
  //if(view_log) Serial.println(millis()-wifi_freq_timer);
  wifi_freq_timer=millis();

  if(WiFi.status()==WL_CONNECTED)
  {
    if (!wifi_connected)
    {
      if(millis()-wifi_check_timer>=2000)
      {
        if(view_log) Serial.print("Local IP: ");
        if(view_log) Serial.println(WiFi.localIP());

        wifi_connected=true;
      }
    }
  }
  else
  {
    if (millis()-wifi_connection_timer>=15000) //30 sec before trying to connect
    {
      wifi_connection_timer=millis();
      wifi_connected=false;
      WiFi.begin(SSID, PASS);
      wifi_check_timer=millis();
    }    
  } 
  if(wifi_connected)
  {
    if(millis()-wifi_request_timer>=1500)
    {
      wifi_request_timer=millis();
      
      Text post_data="request=hey_you_give_me_the_data_a&device_id=1";
      Text headers="Content-Type: application/x-www-form-urlencoded\r\n";
      http.request("/e-sand_clock/digisand_control.php", "POST", headers, post_data);
      if(view_log) Serial.println("Request: Ars_top;");
    }
  }
}