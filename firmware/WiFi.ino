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
      if (millis()-wifi_connection_timer>=15000) //30 sec before trying to connect
      {
        wifi_connection_timer=millis();
        wifi_connected=false;
        WiFi.begin(wifi_credentials.ssid, wifi_credentials.pass);
        wifi_check_timer=millis();
      }    
    } 
  }
  if(wifi_connected)
    {
      if(!client.connected() && !ee_data.ap_mode && WiFi.status()==WL_CONNECTED)
      {
        reconnect();
      }
      client.loop();
      if(millis()-wifi_request_timer>=1500 && client.connected())
      {
        wifi_request_timer=millis();
        
        //Text post_data="request=hey_you_give_me_the_data_a&device_id=1";
        //Text headers="Content-Type: application/x-www-form-urlencoded\r\n";
        //http.request("/e-sand_clock/digisand_control.php", "POST", headers, post_data);
        //if(view_log) Serial.println("Request: Ars_top;");

        

        
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

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    if(String(topic)=="ars-top-rx-digisand-esp-alc")
    {
      gson::Parser p(20);
    if (p.parse(message_tmp))
    {
      ee_data.brightness=p["br"];  

      if(p["a"]=="0") ee_data.angle_auto=false;
      else if(p["a"]=="1") ee_data.angle_auto=true;

      if(p["b"]=="0") ee_data.beep=false;
      else if(p["b"]=="1") ee_data.beep=true;

      int total_seconds=p["t"];
      ee_data.minute=total_seconds/60;
      ee_data.second=total_seconds%60;

      //apply ->
      if (ee_data.brightness==0) led_off=true;
      else led_off=false;

      ee_data.brightness=map(ee_data.brightness, 0, 16, 1, 16);

      ee_data.brightness=map(ee_data.brightness, 0, 16, 1, 16);
      if(!led_off) mtrx.setBright(ee_data.brightness-1);

      uint16_t to_seconds=(ee_data.minute*60)+ee_data.second; //total timer's seconds 
      if(to_seconds<=15) sand_type="water";
      else if(to_seconds>15 && to_seconds<=40) sand_type="more_liquid";
      else if(to_seconds>40 && to_seconds<=120) sand_type="normal";
      else if(to_seconds>120) sand_type="more_thick";

      uint16_t drop_timer_value= to_seconds*1000/61;
      ticker.detach();
      ticker.attach_ms(drop_timer_value, drop_timer_isr);
      // <- apply
    }
  }
}

void reconnect()
{
  // Loop until we're reconnected
  if(millis()-mqtt_reconnect_timer>=5000 && !ee_data.ap_mode && WiFi.status()==WL_CONNECTED && wifi_connected)
  {
    mqtt_reconnect_timer=millis();
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect("arstopout"))
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("ars-top-rx-digisand-esp-alc");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
    }
  }
}