// convert IP address to 4 octet style
String ipToString(uint32_t ip){
  String result = "";

  result += String((ip & 0xFF), 10);    // base number : 10
  result += ".";
  result += String((ip & 0xFF00) >> 8, 10);
  result += ".";
  result += String((ip & 0xFF0000) >> 16, 10);
  result += ".";
  result += String((ip & 0xFF000000) >> 24, 10);

  return result;
}

void print_wifi_state(){
	M5.Lcd.clear(BLACK);  // clear LCD
  M5.Lcd.setTextColor(YELLOW);
  M5.Lcd.setCursor(3, 3);
	M5.Lcd.println("");
	M5.Lcd.println("WiFi connected.");
	M5.Lcd.print("IP address: ");
	M5.Lcd.println(WiFi.localIP());
	M5.Lcd.print("Port: ");
	M5.Lcd.println(port);
}


void mdns(){
  mdns_init();
  ip = MDNS.queryHost(target_dev);
  // target dev IP
  Serial.println("");
  Serial.print(target_dev + " : ");
  Serial.println(ip);
  // M5 self IP
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  ip_addr = ipToString(ip);
  // register mDNS name
  if (MDNS.begin(mdns_name)) {
    Serial.println("MDNS responder started");
  }
}


void setup_wifi(){
	M5.Lcd.setTextColor(RED);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(3, 10);
  M5.Lcd.print("Connecting to ");
  M5.Lcd.println(ssid);

	// setup wifi
  WiFi.mode(WIFI_STA);  // WIFI_AP, WIFI_STA, WIFI_AP_STA or WIFI_OFF
  WiFi.begin(ssid, password);
	// WiFi.begin();

	// Connecting ..
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    M5.Lcd.print(".");
  }
  	// print state
  print_wifi_state();
  udp.begin(port);
  
  // mDNS
  mdns();
}

