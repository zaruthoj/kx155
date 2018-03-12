#include <LedControl.h>

#define SERIAL_BUF_SIZE 100

#define LED_COUNT 4
#define LED_DATA 16
#define LED_CLK 15
#define LED_LOAD 17

#define POWER 9

#define COM_S_A 6
#define COM_S_B 8
#define COM_L_A 4
#define COM_L_B 12
#define COM_TRANS 5
#define COM_STEP 10
#define COM_VOL 4
#define COM_PRIMARY_LED 0
#define COM_STANDBY_LED 1

#define NAV_S_A 3
#define NAV_S_B 11
#define NAV_L_A 0
#define NAV_L_B 2
#define NAV_TRANS 1
//#define NAV_ID 30 // Does not work since PD5 is assigned as LED TX in Arduino.
//#define NAV_VOL 5 // I built support for nav volume into the PCB but didn't expect to use it since no current sim supports it.  Re-assigning this plug as NAV ID.  Digital pin 23 = PF0 = analog pin 5.
#define NAV_ID 23
#define NAV_PRIMARY_LED 2
#define NAV_STANDBY_LED 3

LedControl led_control_g(LED_DATA, LED_CLK, LED_LOAD, LED_COUNT); 

class Display {
public:
  Display(int led_num, int low_freq, int high_freq) :
      led_num_(led_num),
      upper_(low_freq),
      lower_(0),
      low_freq_(low_freq),
      high_freq_(high_freq),
      step_(50),
      needs_update_(true) {
    led_control_g.shutdown(led_num_,true);
    led_control_g.setIntensity(led_num_,1);
    led_control_g.setScanLimit(led_num_, 5);
    led_control_g.clearDisplay(led_num_);
  }

  void render() {
    if (!needs_update_) return;
    int digits[5];
    convert_digits(upper_, 3, digits);
    convert_digits(lower_, 2, digits + 3);

    for (int i = 0; i < 5; ++i) {
      led_control_g.setDigit(led_num_, i, digits[i], i == 2);
    }

    send_frequency();
    needs_update_ = false;
  }

  void send_frequency() {
    Serial.print("FREQUENCY:");
    Serial.print(led_num_+1);
    Serial.print(":");
    if (upper_ < 110) {
      Serial.print("0");  
    }
    Serial.print(upper_ - 100);
    if (lower_ < 100) {
      Serial.print("0");  
    }
    Serial.println(lower_ / 10);
  }
  
  void step_upper(int dir) {
    upper_ = wrap(upper_ + dir, low_freq_, high_freq_);
    needs_update_ = true;
  }

  void step_lower(int dir) {
    lower_ = wrap(lower_ + dir * step_, 0, 1000);
    needs_update_ = true;
  }

  void set_fine_step(bool value) {
    step_ = value ? 25 : 50;
  }

  void set_frequency(int upper, int lower_2d) {
    upper_ = wrap(upper, low_freq_, high_freq_);
    lower_ = lower_2d * 10;
    if (lower_2d % 5 != 0) {
      lower_ += 5;
    }
    lower_ = wrap(lower_, 0, 1000);
    needs_update_ = true;
  }

  void swap(Display & other) {
    int temp_lower = lower_;
    int temp_upper = upper_;
    lower_ = other.lower_;
    upper_ = other.upper_;
    other.lower_ = temp_lower;
    other.upper_ = temp_upper;
    needs_update_ = true;
    other.needs_update_ = true;
  }
private:
  void convert_digits(int value, int num_digits, int* output) {
    char output_str[5];
    if (value < 100) {
      output_str[0] = '0';
      itoa(value, output_str+1, 10);
    } else {
      itoa(value, output_str, 10);
    }
      
    int len = strlen(output_str);
    for(int i = 0; i < len && i < num_digits; ++i) {
      output[i] = output_str[i] - 0x30;
    }
    
  }

  int wrap(int value, int low, int high) {
    if (value >= high) {
      return low;
    } else if (value < low) {
      return high - (low - value);
    }
    return value;
  }
  
  int led_num_;
  int upper_;
  int lower_;
  int low_freq_;
  int high_freq_;
  int step_;
  bool needs_update_;
};

class Encoder {
public:
  Encoder(int pin_a, int pin_b, Display& disp) :
      pin_a_(pin_a),
      pin_b_(pin_b),
      last_a_(HIGH),
      last_b_(HIGH),
      display_(disp) {
    pinMode(pin_a_, INPUT_PULLUP);
    pinMode(pin_b_, INPUT_PULLUP);
  }

  void scan(unsigned long now) {
    int val_a = digitalRead(pin_a_);
    int val_b = digitalRead(pin_b_);
    int pin = -1;
    int val = HIGH;
    if (val_a != last_a_) {
      pin = pin_a_;
      val = val_a;
    } else if (val_b != last_b_) {
      pin = pin_b_;
      val = val_b;
    }
    last_a_ = val_a;
    last_b_ = val_b;

    if (pin == -1) {
      return;
    }

    if (val_a == val_b) return;
    if (pin == pin_a_) {
      //Serial.println("left");
      update_display(-1);
    } else {
      //Serial.println("right");
      update_display(1);
    }
  }

protected:
  virtual void update_display(int dir) = 0;

  int pin_a_;
  int pin_b_;
  int last_a_;
  int last_b_;
  Display &display_;
};

class LargeEncoder : public Encoder {
public:
  LargeEncoder(int pin_a, int pin_b, Display& disp) :
      Encoder(pin_a, pin_b, disp) {}
protected:
  virtual void update_display(int dir) {
    display_.step_upper(dir);
  }
};

class SmallEncoder : public Encoder {
public:
  SmallEncoder(int pin_a, int pin_b, Display& disp) :
      Encoder(pin_a, pin_b, disp) {}
protected:
  virtual void update_display(int dir) {
    display_.step_lower(dir);
  }
};

class Button {
public:
  Button(int pin) :
      pin_(pin),
      last_(LOW),
      high_edge_time_(0) {
    pinMode(pin, INPUT_PULLUP);
  }

  bool scan(unsigned long now) {
    int val = digitalRead(pin_);
    if (val == last_) return false;
    last_ = val;
    if (val == LOW && now - high_edge_time_ > 10) {
      return true;
    }
    if (val == HIGH) {
      high_edge_time_ = now;
    }
    return false;
  }
private:
  int pin_;
  int last_;
  unsigned long high_edge_time_;
};

class Toggle {
public:
  Toggle(int pin) :
      pin_(pin),
      last_(LOW),
      last_edge_time_(0),
      emitted_(false) {
    pinMode(pin, INPUT_PULLUP);
  }

  bool scan(unsigned long now) {
    int val = digitalRead(pin_);
    int old_last = last_;
    last_ = val;
    if (val == old_last) {
      if (now - last_edge_time_ > 2 && !emitted_) {
        emitted_ = true;
        return true;
      }
      return false;
    }
    emitted_ = false;
    last_edge_time_ = now;
    return false;
  }

  int value(unsigned long now) {
    if (now - last_edge_time_ > 2) {
      return last_;
    }
    return (last_ == LOW) ? HIGH : LOW;
  }
private:
  int pin_;
  int last_;
  unsigned long last_edge_time_;
  bool emitted_;
};

class Radio {
public:
  Radio(String id, int small_enc_a, int small_enc_b, int large_enc_a, int large_enc_b, int trans, int primary_disp, int standby_disp, int low_freq, int high_freq) :
      id_(id),
      primary_display_(primary_disp, low_freq, high_freq),
      standby_display_(standby_disp, low_freq, high_freq),
      small_enc_(small_enc_a, small_enc_b, standby_display_),
      large_enc_(large_enc_a, large_enc_b, standby_display_),
      transfer_(trans) {}

  virtual void scan(unsigned long now) {
    large_enc_.scan(now);
    small_enc_.scan(now);
    if (transfer_.scan(now)) {
      Serial.print(id_.c_str());
      Serial.println("_TRANSFER");
      primary_display_.swap(standby_display_);
    }
  }

  void render() {
    primary_display_.render();
    standby_display_.render();
  }

  void set_primary_frequency(int upper, int lower) {
    primary_display_.set_frequency(upper, lower);
  }

  void set_standby_frequency(int upper, int lower) {
    standby_display_.set_frequency(upper, lower);
  }

  void send_primary_frequency(unsigned long now) {
    primary_display_.send_frequency();
  }

  void send_standby_frequency(unsigned long now) {
    standby_display_.send_frequency();
  }
protected:
  String id_;
  Display primary_display_;
  Display standby_display_;
  SmallEncoder small_enc_;
  LargeEncoder large_enc_;
  Button transfer_;
};

class ComRadio : public Radio {
public:
  ComRadio(String id, int small_enc_a, int small_enc_b, int large_enc_a, int large_enc_b, int trans, int freq_step, int power, int primary_disp, int standby_disp) :
      Radio(id, small_enc_a, small_enc_b, large_enc_a, large_enc_b, trans, primary_disp, standby_disp, 118, 137),
      step_toggle_(freq_step),
      power_toggle_(power) {}

  virtual void scan(unsigned long now) {
    if (power_toggle_.scan(now)) {
      bool power_on = power_toggle_.value(now) == LOW;
      for (int i = 0; i < LED_COUNT; ++i) {
        led_control_g.shutdown(i, !power_on);
      }
      send_power_on(now);
    }
    if (step_toggle_.scan(now)) {
      bool fine_step = step_toggle_.value(now) == HIGH;
      standby_display_.set_fine_step(fine_step);
      send_50k_step(!fine_step);
    }
    Radio::scan(now);
  }

  void send_power_on(unsigned long now) {
    Serial.print("POWER_ON:");
    Serial.println(power_toggle_.value(now) == LOW);
  }

  void send_50k_step(unsigned long now) {
    Serial.print("COM_50K_STEP:");
    Serial.println(step_toggle_.value(now) == LOW);
  }
private:
  Toggle step_toggle_;
  Toggle power_toggle_;
};

class NavRadio : public Radio {
public:
  NavRadio(String id, int small_enc_a, int small_enc_b, int large_enc_a, int large_enc_b, int trans, int nav_id, int primary_disp, int standby_disp) :
      Radio(id, small_enc_a, small_enc_b, large_enc_a, large_enc_b, trans, primary_disp, standby_disp, 108, 118),
      id_toggle_(nav_id) {}

  virtual void scan(unsigned long now) {
    if (id_toggle_.scan(now)) {
      send_nav_id(now);
    }
    Radio::scan(now);
  }

  virtual void send_nav_id(unsigned long now) {
    Serial.print("NAV_ID:");
    Serial.println(id_toggle_.value(now) == LOW);
  }
private:
  Toggle id_toggle_;
};

class SerialController {
 public:
  SerialController(ComRadio* com_radio, NavRadio* nav_radio) :
      com_radio_(com_radio),
      nav_radio_(nav_radio),
      pos_(0),
      device_id_(0) {
    Serial.begin(9600);
  }

  void scan(unsigned long now) {
    if (Serial.available() > 0) {
      if (pos_ >= SERIAL_BUF_SIZE) {
        pos_ = 0;
      }
      buffer[pos_] = Serial.read();

      switch(buffer[pos_]) {
        case ':':
          buffer[pos_] = '\0';
          device_id_ = String(buffer).toInt();
          pos_ = 0;
          break;
        case '\n': {
          buffer[pos_] = '\0';
          pos_ = 0;
          if (strncmp(buffer, "ID", 2) == 0) {
            Serial.println("KX155:2")
            device_id_ = 0;
            break;
          }
          if (strncmp(buffer, "INIT", 4) == 0) {
	    send_switches(now);
            device_id_ = 0;
            break;
          }
          int frequency = String(buffer).toInt();
          int upper = frequency / 100 + 100;
          int lower = frequency % 100;
  
          if (device_id_ == 0) {
            device_id_ = 0;
            return;
          }
  
          switch(device_id_) {
            case 1:
              com_radio_->set_primary_frequency(upper, lower);
              break;
            case 2:
              com_radio_->set_standby_frequency(upper, lower);
              break;
            case 3:
              nav_radio_->set_primary_frequency(upper, lower);
              break;
            case 4:
              nav_radio_->set_standby_frequency(upper, lower);
              break;
            default:
              break;
          }
          device_id_ = 0;
          break;
        }
        default: {
          ++pos_;
        }
      }
    }
  }
  
 private:
  void send_switches(unsigned long now) {
    com_radio_->send_power_on(now);
    com_radio_->send_50k_step(now);
    nav_radio_->send_nav_id(now);
  }
 
  ComRadio* com_radio_;
  NavRadio* nav_radio_;
  char buffer[SERIAL_BUF_SIZE];
  int pos_;
  int device_id_;
};

ComRadio* com_radio;
NavRadio* nav_radio;
SerialController *serial_controller;

void setup() {
  com_radio = new ComRadio("COM", COM_S_A, COM_S_B, COM_L_A, COM_L_B, COM_TRANS, COM_STEP, POWER, COM_PRIMARY_LED, COM_STANDBY_LED);
  nav_radio = new NavRadio("NAV", NAV_S_A, NAV_S_B, NAV_L_A, NAV_L_B, NAV_TRANS, NAV_ID, NAV_PRIMARY_LED, NAV_STANDBY_LED);
  serial_controller = new SerialController(com_radio, nav_radio);
}


unsigned int last_render_g = 0;
unsigned int loop_count_g = 0;
void loop() {
  ++loop_count_g;
  com_radio->scan(loop_count_g);
  nav_radio->scan(loop_count_g);
  serial_controller->scan(loop_count_g);

  if (loop_count_g - last_render_g > 40) {
    com_radio->render();
    nav_radio->render();
  }
  
  /*

  int com = digitalRead(COM_TRANS);
  if(com == LOW) {
    lc.setDigit(0, 0, 1, false);
  }
  int nav = digitalRead(NAV_TRANS);
  if(nav == LOW) {
    lc.setDigit(3, 0, 1, false);
  }*/

  delay(1);
}
