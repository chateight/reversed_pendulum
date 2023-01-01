/*
code for the reversed pendulum basic function
using modules ; WiFi/UDP/nDNS/time server
*/

#include "common.h"
#include "image.h"

//ntp server and time info
const char* ntpServer =  "ntp.nict.jp";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;
struct tm timeinfo;

// UDP library
WiFiUDP udp;
// UDP send data
String string_buf;

// PID variables
float P_val = 1;
float I_val = 10;
float D_val = 0.05;

float power=0, I=0, preP=0, preTime;
int dir;  // 1:fwd, -1:rv, 0:stop
float MOTOR_POWER_MIN = 100;
float MOTOR_POWER_MAX = 250;
float roll_data;

// Pendulum data
float TARGET = 83.0;     // balanced angle

void setup() {
	M5.begin();
  Serial.begin(115200);
	// setup wifi
	setup_wifi();
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  imu_setup();
  dc_setup();
  M5.Lcd.drawJpg(panda, 10126, 60, 20);
  preTime = micros();
}

void loop(){
  //
  // PID parameter receive via UDP as a string & store these data
  //
	char packetBuffer[N];
	int packetSize = udp.parsePacket();
 
	if (packetSize){
		int len = udp.read(packetBuffer, packetSize);

    String pid_data = String(packetBuffer);
    int index = pid_data.indexOf(",");
    P_val = (pid_data.substring(0, index)).toFloat();     // P
    pid_data = pid_data.substring(index + 1, pid_data.length());
    index = pid_data.indexOf(",");
    I_val = (pid_data.substring(0, index)).toFloat();     // I
    pid_data = pid_data.substring(index + 1, pid_data.length());
    D_val = pid_data.toFloat();                           // D
  }
  // read IMU data
  string_buf = String(imu_loop());  

  // calc motor power
  float Duty, P, D, now, dt, Time;
  now = TARGET - roll_data;    // calc delta
  if (-25 < now && now < 25) { 
    if (abs(now) >= 0){
      Time = micros();
      dt = (Time - preTime)/1000000;
      preTime = Time;
      P = now/90; // (-90~90) → (-1.0~1.0)
      I += P*dt;
      D = (P - preP)/dt;
      preP = P;
      power = P_val * P + I_val * I + D_val * D;
      //Serial.println(power);
      if (power < -1) power = -1;    // limit the max value
      if (1 < power)  power = 1; 
      if (power < 0){
        dir = 1;
      }else{
        dir = -1;
        }               // set forward/reverse
    }
    // calc motor power
    Duty = (int)((MOTOR_POWER_MAX - MOTOR_POWER_MIN)* abs(power) + MOTOR_POWER_MIN); 
    dc_loop(dir, Duty);
  } else {
    dir = 0;
    dc_loop(dir, 0);
    power = 0;
    I = 0;
  }

  //udp send
  const char *ipadr = ip_addr.c_str();
  udp.beginPacket(ipadr, port);

  int i = 0;

  while( string_buf.length() > i){
    char tmp = string_buf.charAt(i);
    udp.write(tmp);
    i++;
  }
  udp.endPacket();
}
