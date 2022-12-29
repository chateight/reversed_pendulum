//
const uint32_t PWM_Hz = 2000; // PWM freq.
const uint8_t PWM_level = 8;  // PWM resolution 8bit(1～256)
const uint8_t PWM_CH = 1;     // PWM channel

int pwm_a = 26;
int fw_a = 5;
int rv_a = 25;
int pwm_b = 16;
int fw_b = 17;
int rv_b = 2;

void dc_setup() {
  M5.begin();
  
  M5.Power.begin();

  pinMode(pwm_a, OUTPUT);
  pinMode(fw_a, OUTPUT);
  pinMode(rv_a, OUTPUT);
  pinMode(pwm_b, OUTPUT);
  pinMode(fw_b, OUTPUT);
  pinMode(rv_b, OUTPUT);

  // set PWM_CH & resolution
  ledcSetup(PWM_CH, PWM_Hz, PWM_level);
  // combine PWM control pin to PWM_CH
  ledcAttachPin(pwm_a, PWM_CH);
  ledcAttachPin(pwm_b, PWM_CH);
}

void dc_loop(int dir, int pow) {    // dir 1 : fwd, -1 : rv, 0 : stop
  // PWM duty
  ledcWrite(PWM_CH, pow);
  if(dir == 1){
    digitalWrite(fw_a, HIGH);
    digitalWrite(rv_a, LOW);  
    digitalWrite(fw_b, HIGH);
    digitalWrite(rv_b, LOW);
  } else {
    if(dir == -1){
      digitalWrite(fw_a, LOW);
      digitalWrite(rv_a, HIGH);
      digitalWrite(fw_b, LOW);
      digitalWrite(rv_b, HIGH);    
    } else{
    digitalWrite(fw_a, LOW);
    digitalWrite(rv_a, LOW);   
    digitalWrite(fw_b, LOW);
    digitalWrite(rv_b, LOW);   
    }
  }
}