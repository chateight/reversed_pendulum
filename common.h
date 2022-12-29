#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>

#define N 1024

// Wi-Fi connection info. & state
const char* ssid     = "your ssid";
const char* password = "your pw";
const int port = 3002;
String ipToString(uint32_t ip);
void print_wifi_state();

// mDNS target & M5stack
// const String target_dev = "raspberrypi";
const String target_dev = "MacBook-AirM1";
IPAddress ip;         // IPAdress of the target device
String ip_addr = "";  // 4 octet style target address
const char *mdns_name = "m5stick";  //M5stack mDNS name

// pose info.
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

