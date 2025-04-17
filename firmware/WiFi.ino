void wifi_stuff()
{
  //if(view_log) Serial.println(millis()-wifi_freq_timer);
  wifi_freq_timer=millis();
  if(!ee_data.ap_mode)
  {
    if(WiFi.status()==WL_CONNECTED)
    {
      if (!wifi_connected)
      {
        if(millis()-wifi_check_timer>=2000)
        {
          Serial.print("Local IP: ");
          Serial.println(WiFi.localIP());

          wifi_connected=true;
        }
      }
    }
    else
    {
      Serial.println("wifi disconnected");
      if (millis()-wifi_connection_timer>=15000) //30 sec before trying to connect
      {
        wifi_connection_timer=millis();
        wifi_connected=false;
        WiFi.begin(wifi_credentials.ssid, wifi_credentials.pass);
        wifi_check_timer=millis();
      }    
    } 
  
    if(wifi_connected)
    {
      if(!mqtt.connected())
      {
        Serial.println("MQTT fail. Reconnecting...");
        reconnect();
      }
      mqtt.loop();
      if(millis()-wifi_request_timer>=700 && mqtt.connected())
      {
        wifi_request_timer=millis();
        
        char send_build[35]="device_id=1b1768&status=online-ok";
        mqtt.publish("digi_sand_local_Ars", send_build);
      }

      
    }
  }
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String message_tmp;

  for(int i=0; i<length; i++)
  {
    Serial.print((char)message[i]);
    message_tmp+=(char)message[i];
  }
  Serial.println();

  if(String(topic)=="digi_sand_server_Ars")
  {
    gson::Parser p(20);
    if (p.parse(message_tmp))
    {
      if(mqtt.connected() && WiFi.status()==WL_CONNECTED && wifi_connected)
      {
        char send_build[35]="device_id=1b1768&status=received";
        mqtt.publish("digi_sand_local_Ars", send_build);
      }

      ee_data.mode=p["m"];
      ee_data.time_zone=p["tz"];
      time_client.setTimeOffset(3600*ee_data.time_zone);
      ee_data.brightness=p["br"];  

      if(p["a"]=="0") ee_data.angle_auto=false;
      else if(p["a"]=="1") ee_data.angle_auto=true;

      if(p["b"]=="0") ee_data.beep=false;
      else if(p["b"]=="1") ee_data.beep=true;

      int total_seconds=p["t"];
      ee_data.minute=total_seconds/60;
      ee_data.second=total_seconds%60;

      //apply ->
      if (ee_data.brightness==-1) led_off=true;
      else led_off=false;

      if(!led_off) mtrx.setBright(ee_data.brightness);

      uint16_t to_seconds=(ee_data.minute*60)+ee_data.second; //total timer's seconds 
      if(to_seconds<=15) sand_type="water";
      else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
      else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
      else if(to_seconds>120) sand_type="more_thick";

      uint16_t drop_timer_value= to_seconds*1000/61;
      ticker.detach();
      ticker.attach_ms(drop_timer_value, drop_timer_isr);
      // <- apply

      EEPROM.put(2, ee_data);
      EEPROM.commit();
    }
  }
}

void reconnect()
{
  if(millis()-mqtt_reconnect_timer>=5000 && !ee_data.ap_mode && WiFi.status()==WL_CONNECTED && wifi_connected)
  {
    mqtt_reconnect_timer=millis();
    Serial.print("Attempting MQTT connection...");
    if(mqtt.connect("digi_sand_local_Ars")) //send to
    {
      Serial.println("connected");
      // Subscribe
      mqtt.subscribe("digi_sand_server_Ars"); //receive from
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
    }
  }
}